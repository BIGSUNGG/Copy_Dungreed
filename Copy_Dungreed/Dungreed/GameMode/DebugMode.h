#pragma once
class DebugMode : public GameMode
{
public:
	DebugMode();

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void ImGuiRender() override;

	void Init();

private:
	shared_ptr<Player> _player;

	int _mapLevel = 0;
	int _mapNum = 0;
};

