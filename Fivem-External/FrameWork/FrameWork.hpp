#pragma once

// Windows Libraries
#include <Windows.h>
#include <iostream>
#include <dwmapi.h>
#include <TlHelp32.h>

// Security
#include "Security/XorStr.hpp"
#include "Security/LazyImporter.hpp"

// Math
#include "Math/Matrix4x4.hpp"
#include "Math/Vectors/Vector2D.hpp"
#include "Math/Vectors/Vector3D.hpp"
#include "Math/Vectors/Vector4D.hpp"

// Utilities
#include "Utilities/Misc.hpp"
#include "Utilities/Memory.hpp"

// Render
#include "Render/Overlay.hpp"
#include "Render/Interface.hpp"
#include "Render/Assets.hpp"
#include "Render/Assets/FontAwesome.hpp"
#include "Render/Assets/FontInter.hpp"

// ImGui
#include "Dependencies/ImGui/imgui.h"
#include "Dependencies/ImGui/imgui_impl_dx11.h"
#include "Dependencies/ImGui/imgui_impl_win32.h"
#include "Dependencies/ImGui/imgui_internal.h"

// Nlohmann
#include "Dependencies/NlohmannJson.hpp"

// DirectX Inlcude
#include <d3d11.h>
#include <d3dx11.h>


#define XorStr(str) jmXorStr(str)
#define SafeCall(str) lzimpLI_FN(str)