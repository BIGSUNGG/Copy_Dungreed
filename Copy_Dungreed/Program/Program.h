#pragma once
class Program
{
public:
	Program();
	~Program();

	// 매 틱마다 호출
	void Update(); 
	void PreRender();
	void Render();
	void PostRender();
	void ImGuiRender();
	void RenderEnd();

protected:
	// 현재 맵을 Debug Mode에서 실행
	void DebugCurrentMap();
	// 현재 맵을 Map Editor에서 실행
	void EditCurrentMap();

private:
	shared_ptr<GameMode> _gameMode;
	float _runTime = 0.0f;

};

