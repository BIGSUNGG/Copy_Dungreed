#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void ImGuiRender();
	void RenderEnd();

protected:
	void DebugMapFromEditor();
	void EditMapFromDebug();

private:
	shared_ptr<GameMode> _gameMode;
	float _runTime = 0.0f;

};

