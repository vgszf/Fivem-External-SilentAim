#pragma once

// ImGui
#include <FrameWork/Dependencies/ImGui/imgui.h>
#include <FrameWork/Dependencies/ImGui/imgui_impl_dx11.h>
#include <FrameWork/Dependencies/ImGui/imgui_impl_win32.h>
#include <FrameWork/Dependencies/ImGui/imgui_internal.h>

// FivemSDK
#include "FivemSDK/Fivem.hpp"

// Features
#include "Features/Visuals/PlayerESP.hpp"
#include "Features/Visuals/VehicleESP.hpp"
#include "Features/LegitBot/AimBot.hpp"
#include "Features/LegitBot/TriggerBot.hpp"
#include "Features/LegitBot/SilentAim.hpp"
#include "Features/Misc/Exploits.hpp"

#include "Options.hpp"

namespace Cheat
{
	void Initialize();
	void ShutDown();
}