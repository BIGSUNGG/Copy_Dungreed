#pragma once
class Creature : public IObject
{
public:
	Creature();
	virtual ~Creature();

	virtual void Update() override;
	virtual void Render() override;
};

