#include "framework.h"
#include "Program.h"

Program::Program()
{
	_gameMode = make_shared<MapEditor>();
}

Program::~Program()
{
}

void Program::Update()
{
	_runTime += DELTA_TIME;

	_gameMode->Update();

	// 게임 상태 변경
	if (KEY_DOWN(VK_F1))
		GAME->SetPause(!GAME->GetPause());
	if (KEY_DOWN(VK_F2))
		GAME->SetRenderTexture(!GAME->GetRenderTexture());
	if (KEY_DOWN(VK_F3))
		GAME->SetRenderCollider(!GAME->GetRenderCollider());
	if (KEY_DOWN(VK_F4))
		GAME->SetRenderUI(!GAME->GetRenderUI());

	// 게임모드 변경
	if (KEY_DOWN(VK_F6))
		_gameMode = make_shared<MapEditor>();
	if (KEY_DOWN(VK_F7))
		_gameMode = make_shared<MapTest>();
	if (KEY_DOWN(VK_F8))
		_gameMode = make_shared<Dungreed>();

}

void Program::PreRender()
{
	Camera::GetInstance()->SetProjectionBuffer(WIN_WIDTH, WIN_HEIGHT);
	Camera::GetInstance()->SetCameraWorldBuffer();

	_gameMode->PreRender();

	Device::GetInstance()->SetRTV();
	Device::GetInstance()->Clear();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Camera::GetInstance()->SetViewPort(WIN_WIDTH, WIN_HEIGHT);

	ALPHA_STATE->SetState();
}

void Program::Render()
{
	_gameMode->Render();
}

void Program::PostRender()
{
	_gameMode->PostRender();
}

void Program::ImGuiRender()
{
	ImGui::Begin("Program");
	if (ImGui::CollapsingHeader("Info"))
	{
		ImGui::Text("FPS : %d", Timer::GetInstance()->GetFPS());
		ImGui::Text("RUN TIME : %0.1f", _runTime);
		ImGui::Text("DELTA TIME : %fs", DELTA_TIME);
		ImGui::Text("MousePos : %f, %f", MOUSE_POS.x, MOUSE_POS.y);
		ImGui::SliderFloat("GAME SPEED", &GAME_SPEED, 0.1f, 5.0f, "%0.1f");
	}
	if (ImGui::CollapsingHeader("Audio"))
		SOUND->ImGuiRender();

	if (ImGui::CollapsingHeader("Camera"))
		Camera::GetInstance()->ImGuiRender();

	if (ImGui::CollapsingHeader("Graphic Options"))
		GRAPHIC->ImGuiRender();

	ImGui::End();

	ImGui::Begin("Game");
	switch (_gameMode->GetGameModeType())
	{
	case GameMode::DUNGREED:
		if (ImGui::Button("Map Editor"))
			_gameMode = make_shared<MapEditor>();
		if (ImGui::Button("Test"))
			_gameMode = make_shared<MapTest>();
		if (ImGui::Button("Edit Current Map"))
			EditCurrentMap();
		if (ImGui::Button("Test Current Map"))
			TestCurrentMap();

		break;
	case GameMode::MAP_EDITOR:
		if (ImGui::Button("Dungreed"))
			_gameMode = make_shared<Dungreed>();
		if (ImGui::Button("Test"))
			_gameMode = make_shared<MapTest>();
		if (ImGui::Button("Test Current Map"))
			TestCurrentMap();

		break;;
	case GameMode::MAP_TEST:
		if (ImGui::Button("Dungreed"))
			_gameMode = make_shared<Dungreed>();
		if (ImGui::Button("Map Editor"))
			_gameMode = make_shared<MapEditor>();
		if (ImGui::Button("Edit Current Map"))
			EditCurrentMap();

		break;
	default:
		break;
	}
	_gameMode->ImGuiRender();
}

void Program::RenderEnd()
{
	wstring fps = L"FPS : " + to_wstring((int)Timer::GetInstance()->GetFPS());
	RECT rect = { 0,0,100,100 };
	DirectWrite::GetInstance()->RenderText(fps, rect);

	ImGui::End();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	MOUSE_CURSUR->Render();

	Device::GetInstance()->Present();
}

void Program::TestCurrentMap()
{
	auto curMap = GAME->GetCurMap();
	int level = curMap->GetLevel();
	int num = curMap->GetNum();
	_gameMode = make_shared<MapTest>(level, num);
}

void Program::EditCurrentMap()
{
	auto curMap = GAME->GetCurMap();
	int level = curMap->GetLevel();
	int num = curMap->GetNum();
	_gameMode = make_shared<MapEditor>(level, num);
}
