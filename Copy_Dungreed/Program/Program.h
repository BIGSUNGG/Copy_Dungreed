#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();
	void Render();

private:
	shared_ptr<GameMode> _game;
};

