#include "framework.h"
#include "Dash_Info.h"

Dash_Info::Dash_Info()
{
}

Dash_Info::~Dash_Info()
{
}

void Dash_Info::Update()
{
	_dashChargeTime += DELTA_TIME;

	if (_dashChargeTime >= _dashChargeDelay && _dashCount < _dashCountMax)
	{
		_dashChargeTime = 0.0f;
		++_dashCount;
	}
}

void Dash_Info::Reset()
{
	--_dashCount;
	_dashChargeTime = 0.0f;
	_dashSlow = false;
	_dashRunTime = 0.0f;
	_dashCurSpeed = _dashSpeedMax;
	_trailCount = 0;
	_trailTime = 0.0f;
}
