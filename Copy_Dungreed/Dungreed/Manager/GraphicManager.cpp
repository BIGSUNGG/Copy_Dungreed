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

	if (ImGui::TreeNode("Window Mode"))
	{
		ImGui::RadioButton("Border", &_winMode, 0);
		ImGui::SameLine();
		ImGui::RadioButton("Borderless", &_winMode, 1);

		ImGui::TreePop();
	}

	if (ImGui::TreeNode("FPS Limit"))
	{
		ImGui::SliderInt("FRAME Limit", &_fpsLimit, 0, 1000);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Mouse Cursur"))
	{
		if (ImGui::Button("On"))
			CursurOn();

		ImGui::SameLine();
		if (ImGui::Button("Off"))
			CursurOff();

		ImGui::TreePop();
	}

	if (ImGui::Button("Apply Settings"))
	{
		Timer::GetInstance()->SetLockFPS(_fpsLimit);

		int temp;
		{
			BinaryReader Reader(L"Save/Graphic_Setting/Setting.txt");

			UINT size = Reader.Uint();

			vector<int> graphicInfo;
			graphicInfo.resize(1);
			void* ptr = graphicInfo.data();
			Reader.Byte(&ptr, size * sizeof(int));

			temp = graphicInfo[0];
		}

		if (_winMode != temp)
		{
			_applied = true;
			BinaryWriter basicWriter(L"Save/Graphic_Setting/Setting.txt");

			vector<int> basicInfo;

			basicInfo.push_back(_winMode);

			basicWriter.Uint(basicInfo.size());
			basicWriter.Byte(basicInfo.data(), basicInfo.size() * sizeof(int));
		}
	}

	if (_applied)
	{
		ImGui::SameLine();
		ImGui::Text("Restart Program");
	}
}
