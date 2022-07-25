#include "framework.h"
#include "Program.h"

Program::Program()
{
	_game = make_shared<GameMode>();
}

Program::~Program()
{
}

void Program::Update()
{
	_game->Update();
	EffectManager::GetInstance()->Update();
	Camera::GetInstance()->Update();
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

	_game->PreRender();

	_game->Render();
	EffectManager::GetInstance()->Render();

	DirectWrite::GetInstance()->GetDC()->BeginDraw();
	_game->PostRender();
	_game->ImGuiRender();
	Camera::GetInstance()->PostRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	DirectWrite::GetInstance()->GetDC()->EndDraw();
	Device::GetInstance()->Present();
}
