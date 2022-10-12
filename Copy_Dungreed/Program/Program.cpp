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

	CAMERA->Update();
	SOUND->Update();

	_gameMode->Update();

	MOUSE_CURSUR->Update();

	if (KEY_DOWN(VK_F2))
		SwitchBool(GAME->GetRenderTexture());
	if (KEY_DOWN(VK_F3))
		SwitchBool(GAME->GetRenderCollider());
	if (KEY_DOWN(VK_F6))
		_gameMode = make_shared<MapEditor>();
	if (KEY_DOWN(VK_F7))
		_gameMode = make_shared<DebugMode>();
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
	wstring fps = L"FPS : " + to_wstring((int)Timer::GetInstance()->GetFPS());
	RECT rect = { 0,0,100,100 };

	DirectWrite::GetInstance()->GetDC()->BeginDraw();
	DirectWrite::GetInstance()->RenderText(fps, rect);

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
		if (ImGui::Button("MapEditor"))
			_gameMode = make_shared<MapEditor>();
		if (ImGui::Button("Debug"))
			_gameMode = make_shared<DebugMode>();
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
}

void Program::RenderEnd()
{
	DirectWrite::GetInstance()->GetDC()->EndDraw();

	ImGui::End();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	MOUSE_CURSUR->Render();

	Device::GetInstance()->Present();
}
