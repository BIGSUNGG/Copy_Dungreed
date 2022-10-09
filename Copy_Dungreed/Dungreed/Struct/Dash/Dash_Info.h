#pragma once
struct Dash_Info
{
public:
	Dash_Info();
	~Dash_Info();
	
	void Update();

public:
	Vector2 _dashDirection = { 0,0 };

	bool _dashSlow = false;

	float _dashCurSpeed = 0.0f;
	float _dashRunTime = 0.0f;
	const float _dashSlowSpeed = 10000.0f;
	const float _dashSpeedMax = 2500.0f;
	const float _dashRunTimeMax = 0.025f;

	int _dashCount = 3;
	const int _dashCountMax = 3;
	float _dashChargeTime = 0.0f;
	const float _dashChargeDelay = 1.0f;
};

