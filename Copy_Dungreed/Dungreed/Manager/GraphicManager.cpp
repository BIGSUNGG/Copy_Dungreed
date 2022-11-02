#include "framework.h"
#include "GraphicManager.h"
GraphicManager* GraphicManager::_instance = nullptr;

GraphicManager::GraphicManager()
{
	Load();
}

GraphicManager::~GraphicManager()
{
}

void GraphicManager::Save()
{
	Timer::GetInstance()->SetLockFPS(_fpsLimit);

	_restart = true;
	BinaryWriter basicWriter(L"Save/Graphic_Setting/Setting.bin");

	vector<int> basicInfo;

	basicInfo.push_back(_winMode);
	basicInfo.push_back(_fpsLimit);

	basicWriter.Uint(basicInfo.size());
	basicWriter.Byte(basicInfo.data(), basicInfo.size() * sizeof(int));
}

void GraphicManager::Load()
{
	{
		BinaryReader Reader(L"Save/Graphic_Setting/Setting.bin");

		UINT size = Reader.Uint();

		vector<int> graphicInfo;
		graphicInfo.resize(2);
		void* ptr = graphicInfo.data();
		Reader.Byte(&ptr, size * sizeof(int));

		_winMode = graphicInfo[0];
		_fpsLimit = graphicInfo[1];
	}

	Timer::GetInstance()->SetLockFPS(_fpsLimit);
}

void GraphicManager::ImGuiRender()
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
			MOUSE_CURSUR->CursurOn();

		ImGui::SameLine();
		if (ImGui::Button("Off"))
			MOUSE_CURSUR->CursurOff();

		ImGui::TreePop();
	}

	if (ImGui::Button("Apply Settings"))
		Save();

	if (_restart)
	{
		ImGui::SameLine();
		ImGui::Text("Restart Program");
	}
}

void GraphicManager::SetWinMode(const int& mode)
{
	if (mode > 1 || mode < 0)
		return;

	_winMode = mode;
}

void GraphicManager::SetFpsLimit(const int& mode)
{
	_fpsLimit = mode;
	Timer::GetInstance()->SetLockFPS(_fpsLimit);
}
