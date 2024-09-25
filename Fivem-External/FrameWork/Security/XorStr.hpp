#include <immintrin.h>
#include <cstdint>
#include <cstddef>
#include <utility>
#include <type_traits>

#define jmXorStr_(str) FrameWork::Security::XorStr::xor_string([]() { return str; }, std::integral_constant<std::size_t, sizeof(str) / sizeof(*str)>{}, std::make_index_sequence<FrameWork::Security::XorStr::Detail::_buffer_size<sizeof(str)>()>{})
#define jmXorStr(str) jmXorStr_(str).crypt_get()

namespace FrameWork
{
    namespace Security
    {
        namespace XorStr
        {
            namespace Detail
            {
                template<std::size_t Size>
                __forceinline constexpr std::size_t _buffer_size()
                {
                    return ((Size / 16) + (Size % 16 != 0)) * 2;
                }

                template<std::uint32_t Seed>
                __forceinline constexpr std::uint32_t key4() noexcept
                {
                    std::uint32_t value = Seed;
                    for (char c : __TIME__)
                        value = static_cast<std::uint32_t>((value ^ c) * 16777619ull);
                    return value;
                }

                template<std::size_t S>
                __forceinline constexpr std::uint64_t key8()
                {
                    constexpr auto first_part = key4<2166136261 + S>();
                    constexpr auto second_part = key4<first_part>();
                    return (static_cast<std::uint64_t>(first_part) << 32) | second_part;
                }

                // loads up to 8 characters of string into uint64 and xors it with the key
                template<std::size_t N, class CharT>
                __forceinline constexpr std::uint64_t load_xored_str8(std::uint64_t key, std::size_t idx, const CharT* str) noexcept
                {
                    using cast_type = typename std::make_unsigned<CharT>::type;
                    constexpr auto value_size = sizeof(CharT);
                    constexpr auto idx_offset = 8 / value_size;

                    std::uint64_t value = key;
                    for (std::size_t i = 0; i < idx_offset && i + idx * idx_offset < N; ++i)
                        value ^=
                        (std::uint64_t{ static_cast<cast_type>(str[i + idx * idx_offset]) }
                    << ((i % idx_offset) * 8 * value_size));

                    return value;
                }

                // forces compiler to use registers instead of stuffing constants in rdata
                __forceinline std::uint64_t load_from_reg(std::uint64_t value) noexcept
                {
                    volatile std::uint64_t reg = value;
                    return reg;
                }

            } // namespace detail

            template<class CharT, std::size_t Size, class Keys, class Indices>
            class xor_string;

            template<class CharT, std::size_t Size, std::uint64_t... Keys, std::size_t... Indices>
            class xor_string<CharT, Size, std::integer_sequence<std::uint64_t, Keys...>, std::index_sequence<Indices...>> {
                constexpr static inline std::uint64_t alignment = ((Size > 16) ? 32 : 16);

                alignas(alignment) std::uint64_t _storage[sizeof...(Keys)];

            public:
                using value_type = CharT;
                using size_type = std::size_t;
                using pointer = CharT*;
                using const_pointer = const CharT*;

                template<class L>
                __forceinline xor_string(L l, std::integral_constant<std::size_t, Size>, std::index_sequence<Indices...>) noexcept
                    : _storage{ FrameWork::Security::XorStr::Detail::load_from_reg((std::integral_constant<std::uint64_t, Detail::load_xored_str8<Size>(Keys, Indices, l())>::value))... }
                {}

                __forceinline constexpr size_type size() const noexcept
                {
                    return Size - 1;
                }

                __forceinline void crypt() noexcept
                {
                    // everything is inlined by hand because a certain compiler with a certain linker is _very_ slow
                    alignas(alignment) std::uint64_t keys[]{ FrameWork::Security::XorStr::Detail::load_from_reg(Keys)... };
                    ((Indices >= sizeof(_storage) / 32 ? static_cast<void>(0) : _mm256_store_si256(
                        reinterpret_cast<__m256i*>(_storage) + Indices,
                        _mm256_xor_si256(
                            _mm256_load_si256(reinterpret_cast<const __m256i*>(_storage) + Indices),
                            _mm256_load_si256(reinterpret_cast<const __m256i*>(keys) + Indices)))), ...);

                    if constexpr (sizeof(_storage) % 32 != 0)
                        _mm_store_si128(
                            reinterpret_cast<__m128i*>(_storage + sizeof...(Keys) - 2),
                            _mm_xor_si128(_mm_load_si128(reinterpret_cast<const __m128i*>(_storage + sizeof...(Keys) - 2)),
                                _mm_load_si128(reinterpret_cast<const __m128i*>(keys + sizeof...(Keys) - 2))));
                }

                __forceinline const_pointer get() const noexcept
                {
                    return reinterpret_cast<const_pointer>(_storage);
                }

                __forceinline pointer get() noexcept
                {
                    return reinterpret_cast<pointer>(_storage);
                }

                __forceinline pointer crypt_get() noexcept
                {
                    // crypt() is inlined by hand because a certain compiler with a certain linker is _very_ slow
                    alignas(alignment) std::uint64_t keys[]{ FrameWork::Security::XorStr::Detail::load_from_reg(Keys)... };

                    ((Indices >= sizeof(_storage) / 32 ? static_cast<void>(0) : _mm256_store_si256(
                        reinterpret_cast<__m256i*>(_storage) + Indices,
                        _mm256_xor_si256(
                            _mm256_load_si256(reinterpret_cast<const __m256i*>(_storage) + Indices),
                            _mm256_load_si256(reinterpret_cast<const __m256i*>(keys) + Indices)))), ...);

                    if constexpr (sizeof(_storage) % 32 != 0)
                        _mm_store_si128(
                            reinterpret_cast<__m128i*>(_storage + sizeof...(Keys) - 2),
                            _mm_xor_si128(_mm_load_si128(reinterpret_cast<const __m128i*>(_storage + sizeof...(Keys) - 2)),
                                _mm_load_si128(reinterpret_cast<const __m128i*>(keys + sizeof...(Keys) - 2))));

                    return (pointer)(_storage);
                }
            };

            template<class L, std::size_t Size, std::size_t... Indices>
            xor_string(L l, std::integral_constant<std::size_t, Size>, std::index_sequence<Indices...>) -> xor_string<
                std::remove_const_t<std::remove_reference_t<decltype(l()[0])>>,
                Size,
                std::integer_sequence<std::uint64_t, Detail::key8<Indices>()...>,
                std::index_sequence<Indices...>>;

        }
    }
}