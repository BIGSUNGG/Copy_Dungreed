#pragma once
class Program
{
public:
	Program();
	~Program();

	// �� ƽ���� ȣ��
	void Update(); 
	void PreRender();
	void Render();
	void PostRender();
	void ImGuiRender();
	void RenderEnd();

protected:
	// ���� ���� Debug Mode���� ����
	void DebugCurrentMap();
	// ���� ���� Map Editor���� ����
	void EditCurrentMap();

private:
	shared_ptr<GameMode> _gameMode;
	float _runTime = 0.0f;

};

