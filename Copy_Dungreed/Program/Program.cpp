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
	if (KEY_DOWN(VK_F1))
		SwitchBool(GAME->GetPause());

	_runTime += DELTA_TIME;

	if (GAME->GetPause())
		return;

	Camera::GetInstance()->Update();

	_gameMode->Update();

	if (KEY_DOWN(VK_F2))
		SwitchBool(GAME->GetRenderTexture());
	if (KEY_DOWN(VK_F3))
		SwitchBool(GAME->GetRenderCollider());
	if (KEY_DOWN(VK_F4))
		_gameMode = make_shared<MapEditor>();
	if (KEY_DOWN(VK_F6))
		_gameMode = make_shared<Dungreed>();
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Camera::GetInstance()->SetProjectionBuffer(WIN_WIDTH, WIN_HEIGHT);
	Camera::GetInstance()->SetViewPort(WIN_WIDTH, WIN_HEIGHT);

	ALPHA_STATE->SetState();

	_gameMode->PreRender();

	_gameMode->Render();

	wstring fps = L"FPS : " + to_wstring((int)Timer::GetInstance()->GetFPS());
	RECT rect = { 0,0,100,100 };

	DirectWrite::GetInstance()->GetDC()->BeginDraw();
	DirectWrite::GetInstance()->RenderText(fps, rect);

	_gameMode->PostRender();

	ImGuiRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	DirectWrite::GetInstance()->GetDC()->EndDraw();
	Device::GetInstance()->Present();
}

void Program::ImGuiRender()
{
	ImGui::Begin("Program");
	if (ImGui::CollapsingHeader("Info"))
	{
		ImGui::Text("FPS : %d", Timer::GetInstance()->GetFPS());
		ImGui::Text("RUN TIME : %0.1f", _runTime);
		ImGui::Text("DELTA TIME : %fs", DELTA_TIME);
		ImGui::SliderFloat("GAME SPEED", &GAME_SPEED, 0.1f, 5.0f, "%0.1f");
	}

	if (ImGui::CollapsingHeader("Camera"))
		Camera::GetInstance()->ImGuiRender();

	if (ImGui::CollapsingHeader("Graphic Options"))
		GRAPHIC->ImguiRender();

	ImGui::End();

	ImGui::Begin("Game");
	switch (_gameMode->GetGameModeType())
	{
	case GameMode::DUNGREED:
		if (ImGui::Button("MapEditor"))
			_gameMode = make_shared<MapEditor>();
		break;
	case GameMode::MAP_EDITOR:
		if (ImGui::Button("Dungreed"))
			_gameMode = make_shared<Dungreed>();
		if (ImGui::Button("Debug"))
			_gameMode = make_shared<DebugMode>();
		break;;
	case GameMode::DEBUG:
		if (ImGui::Button("Dungreed"))
			_gameMode = make_shared<Dungreed>();
		if (ImGui::Button("MapEditor"))
			_gameMode = make_shared<MapEditor>();
		break;
	default:
		break;
	}
	_gameMode->ImGuiRender();
	ImGui::End();
}
