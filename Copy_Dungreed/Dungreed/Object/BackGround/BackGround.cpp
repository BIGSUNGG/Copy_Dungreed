#include "framework.h"
#include "BackGround.h"

BackGround::BackGround(int level, int num)
{
	_texture = TEXTURE_MANAGER->GetBackGroundTexture(level, num);
}

BackGround::~BackGround()
{
}

void BackGround::Update()
{
	_texture->Update();
}

void BackGround::Render()
{
	_texture->Render();
}

void BackGround::PostRender()
{
}
