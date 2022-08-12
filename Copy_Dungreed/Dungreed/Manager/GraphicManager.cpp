#include "framework.h"
#include "GraphicManager.h"
GraphicManager* GraphicManager::_instance = nullptr;

GraphicManager::GraphicManager()
{
	{
		BinaryReader Reader(L"Save/Graphic_Setting/Setting.txt");

		UINT size = Reader.Uint();

		vector<int> graphicInfo;
		graphicInfo.resize(1);
		void* ptr = graphicInfo.data();
		Reader.Byte(&ptr, size * sizeof(int));

		_winMode = graphicInfo[0];
	}
}

GraphicManager::~GraphicManager()
{
}

void GraphicManager::Save()
{
}

void GraphicManager::Load()
{
}

void GraphicManager::ImguiRender()
{
	if (ImGui::CollapsingHeader("Graphic"))
	{
		ImGui::SliderInt("WinMode", &_winMode, 0, 1);
		switch (_winMode)
		{
		case 0:
			ImGui::Text("Window");
			break;
		case 1:
			ImGui::Text("Borderless Window");
			break;
		default:
			break;
		}

		if (ImGui::Button("Apply"))
		{
			BinaryWriter basicWriter(L"Save/Graphic_Setting/Setting.txt");

			vector<int> basicInfo;

			basicInfo.emplace_back(_winMode);

			basicWriter.Uint(basicInfo.size());
			basicWriter.Byte(basicInfo.data(), basicInfo.size() * sizeof(int));
		}
	}
}
