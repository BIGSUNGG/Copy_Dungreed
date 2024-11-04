#pragma once
struct Dash_Info
{
public:
	Dash_Info();
	~Dash_Info();
	
	void Update();

	void Reset();

public:
	int _dashCount = 3;
	const int _dashCountMax = 3;
	float _dashChargeTime = 0.0f;
	const float _dashChargeDelay = 1.0f;

	int _trailCount = 0;
	float _trailTime = 0.0f;
	const int _trailCountMax = 4;
	const float _trailDelay = 0.025f;
};

