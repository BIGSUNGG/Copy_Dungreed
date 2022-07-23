#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();
	void Render();

private:
	shared_ptr<Game> _game;
};

