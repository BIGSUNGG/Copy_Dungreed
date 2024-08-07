#pragma once
class BackGround : public Object
{
public:
	enum BackGround_Type
	{
		STATIC,	// 맵에 고정
		WALLPAPER, // 카메라 위치와 같게
		PERSPECTIVE, // 카메라 이동에 따라 이동
	};

public:
	BackGround(int level,int num);

	virtual void Update() override;

public:
	// Getter Setter
	virtual BackGround_Type& GetBackGroundType() { return _backGroundType; }
	float& GetRatio() { return _perspectiveRatio; }

protected:
	BackGround_Type _backGroundType = STATIC;

	float _perspectiveRatio = 1.5f; // 원근법 느낌나는 비율
};

