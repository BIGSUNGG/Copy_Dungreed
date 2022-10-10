#pragma once
class Effect_Trail : public Effect
{
public:
	Effect_Trail(int level = 0, int num = 0);

	virtual void Update() override;

protected:
	float _fadeRatio = 1.5f;

};

