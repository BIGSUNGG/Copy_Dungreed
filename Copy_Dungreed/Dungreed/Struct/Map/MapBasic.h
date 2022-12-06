#pragma once
struct MapBasic
{
	MapBasic();
	~MapBasic();

	bool CanGoTop()		{ return (_topDoor != Vector2(0, 0)); }
	bool CanGoBottom()	{ return (_bottomDoor != Vector2(0, 0)); }
	bool CanGoLeft()	{ return (_leftDoor != Vector2(0, 0)); }
	bool CanGoRight()	{ return (_rightDoor != Vector2(0, 0)); }

	int _objectCount = 0;

	Vector2 _startPos	= { 5000,5000 };
	Vector2 _leftBottom = { 0,0 };
	Vector2 _rightTop	= { 0,0 };

	Vector2 _topDoor	= { 0,0 };
	Vector2 _bottomDoor = { 0,0 };
	Vector2 _leftDoor	= { 0,0 };
	Vector2 _rightDoor	= { 0,0 };
};

