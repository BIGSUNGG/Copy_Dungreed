#pragma once
class BackGround : public Object
{
public:
	enum BackGround_Type
	{
		STATIC,
		FOLLOW_CAMERA,
		FOLLOW_PLAYER,
	};

public:
	BackGround(int level,int num);

	virtual void Update() override;

	virtual BackGround_Type& GetBackGroundType() { return _backGroundType; }

protected:
	BackGround_Type _backGroundType = STATIC;
};

