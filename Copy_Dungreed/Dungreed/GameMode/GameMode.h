#pragma once

class GameMode
{
public:
	virtual void Update() abstract;

	virtual void PreRender() abstract;
	virtual void Render() abstract;
	virtual void PostRender() abstract;
	virtual void ImGuiRender() abstract;

};