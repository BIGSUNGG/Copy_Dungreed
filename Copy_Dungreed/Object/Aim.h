#pragma once
class Aim
{
public:
	Aim();
	~Aim();

	void Update();
	void Render();

private:
	shared_ptr<Quad> _quad;
};