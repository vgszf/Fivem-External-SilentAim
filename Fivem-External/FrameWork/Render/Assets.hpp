#pragma once

#include <FrameWork/FrameWork.hpp>
#include <FrameWork/Dependencies/ImGui/imgui.h>

#include "Assets/FontInter.hpp"
#include "Assets/FontAwesome.hpp"

#include <d3d11.h>
#include <d3dx11.h>

namespace FrameWork
{
	namespace Assets
	{
		inline ImFont* FontAwesomeRegular = nullptr;
		inline ImFont* FontAwesomeSolid = nullptr;
		inline ImFont* FontAwesomeSolid18 = nullptr;
		inline ImFont* FontAwesomeSolidBig = nullptr;

		inline ImFont* InterExtraLight = nullptr;
		inline ImFont* InterLight = nullptr;
		inline ImFont* InterThin = nullptr;
		inline ImFont* InterRegular = nullptr;
		inline ImFont* InterRegular14 = nullptr;
		inline ImFont* InterMedium = nullptr;
		inline ImFont* InterSemiBold = nullptr;
		inline ImFont* InterBold = nullptr;
		inline ImFont* InterBold12 = nullptr;
		inline ImFont* InterExtraBold = nullptr;
		inline ImFont* InterBlack = nullptr;

		inline ID3D11ShaderResourceView* Logo;

		void Initialize(ID3D11Device* Device);
	}
}