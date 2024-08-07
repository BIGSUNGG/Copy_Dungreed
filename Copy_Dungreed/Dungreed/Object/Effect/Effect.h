#pragma once
class Effect : public Object
{
public:
	Effect(int level, int num);
	
	virtual void Update()override;

};

