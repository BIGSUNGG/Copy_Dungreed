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
	shared_ptr<Map> _curMap; // 현재 플레이 중인 맵
	shared_ptr<Player> _player; // 플레이어 캐릭터

	int _mapLevel = 0;
	int _mapNum = 0;
};

