#include "framework.h"
#include "Aim.h"

Aim::Aim()
{
	_quad = make_shared<Quad>(L"Resource/Aim.png");
	_quad->GetTransform()->GetScale() *= 0.1f;
}

Aim::~Aim()
{
}

void Aim::Update()
{
	_quad->GetTransform()->GetPos() = MOUSE_POS;

	_quad->Update();
}

void Aim::Render()
{
	_quad->Render();
}
