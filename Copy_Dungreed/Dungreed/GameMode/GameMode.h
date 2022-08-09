#pragma once

class GameMode
{
public:
	enum GameModeType
	{
		NONE,
		DUNGREED,
		MAP_EDITOR,
	};

public:
	GameMode();
	virtual ~GameMode();

	virtual void Update() abstract;

	virtual void PreRender() abstract;
	virtual void Render() abstract;
	virtual void PostRender() abstract;
	virtual void ImGuiRender() abstract;
};