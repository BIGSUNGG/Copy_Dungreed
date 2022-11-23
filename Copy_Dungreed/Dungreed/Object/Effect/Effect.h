#pragma once
class Effect : public Object
{
public:
	enum Effect_Type
	{
		DESTROY,
		LOOP,
	};

public:
	Effect(int level, int num);
	
	virtual void Update()override;

	void SetRenderOrder(float order) { _renderOrder = order; }

	virtual Effect_Type& GetEffectType() { return _effectType; }

protected:
	Effect_Type _effectType = DESTROY;

};

