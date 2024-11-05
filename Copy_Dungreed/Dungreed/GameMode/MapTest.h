#pragma once
class MapTest : public GameMode
{
public:
	MapTest();
	MapTest(int level, int num);

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void ImGuiRender() override;

protected:
	void Init(shared_ptr<StageMap> testMap);

public:
	shared_ptr<StageMap> GetCurMap() { return _curMap; }

private:
	shared_ptr<StageMap> _curMap; // ���� �÷��� ���� ��
	shared_ptr<Player> _player; // �÷��̾� ĳ����

	int _mapLevel = 0;
	int _mapNum = 0;
};

