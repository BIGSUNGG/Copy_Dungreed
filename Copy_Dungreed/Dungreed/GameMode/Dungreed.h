#pragma once
class Dungreed : public GameMode
{
public:
	Dungreed();

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void ImGuiRender() override;

private:
	shared_ptr<Map> _map;
	shared_ptr<Creature> _player;
	shared_ptr<Quad> _cursur;
	float _gameRunTime = 0.0f;
};

