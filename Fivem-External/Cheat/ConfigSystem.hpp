#pragma once

#include <string>
#include <vector>
#include <set>

#include <FrameWork/FrameWork.hpp>
#include <FrameWork/Utilities/Base64.hpp>

#include "Options.hpp"

namespace Cheat
{
	class ConfigManager
	{
	public:
		class C_ConfigItem
		{
		public:
			std::string Name;
			void* Pointer;
			std::string Type;

			C_ConfigItem(std::string Name, void* Pointer, std::string Type)
			{
				this->Name = Name;
				this->Pointer = Pointer;
				this->Type = Type;
			}
		};

		std::vector<C_ConfigItem*> Items;

		void AddItem(void* Pointer, const char* Name, const std::string& Type);

		void SetupItem(int* Pointer, float Value, const std::string& Name);

		void SetupItem(float* Pointer, float Value, const std::string& Name);

		void SetupItem(bool* Pointer, float Value, const std::string& Name);

		void Setup();

		ConfigManager()
		{
			Setup();
		};

		void ExportToClipboard();
		void ImportFromClipboard();

		void LoadConfig();
		void SaveConfig();
	};
}