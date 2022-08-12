#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();
	void Render();
	void ImGuiRender();

private:
	shared_ptr<GameMode> _gameMode;
	float _runTime = 0.0f;
};

