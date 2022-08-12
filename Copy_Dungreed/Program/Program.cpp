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

	Camera::GetInstance()->Update();
	_gameMode->Update();
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
	ImGui::Text("FPS : %d", Timer::GetInstance()->GetFPS());
	ImGui::Text("RUN TIME : %0.1f", _runTime);

	Camera::GetInstance()->ImGuiRender();

	ImGui::Text("DELTA TIME : %fs", DELTA_TIME);

	switch (_gameMode->GetGameModeType())
	{
	case GameMode::NONE:
		break;
	case GameMode::DUNGREED:
		if (ImGui::Button("MapEditor"))
			_gameMode = make_shared<MapEditor>();
		break;
	case GameMode::MAP_EDITOR:
		if (ImGui::Button("Dungreed"))
			_gameMode = make_shared<Dungreed>();
		break;
	default:
		break;
	}

	GRAPHIC->ImguiRender();
	ImGui::End();

	ImGui::Begin("Game");
	_gameMode->ImGuiRender();
	ImGui::End();
}
