#pragma once
class DebugMode : public GameMode
{
public:
	DebugMode();
	DebugMode(int level, int num);

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void ImGuiRender() override;

protected:
	void Init(shared_ptr<Map> debugMap);

public:
	shared_ptr<Map> GetCurMap() { return _curMap; }

private:
	shared_ptr<Map> _curMap;
	shared_ptr<Player> _player;

	int _mapLevel = 0;
	int _mapNum = 0;
};

