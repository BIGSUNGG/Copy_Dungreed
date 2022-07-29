#pragma once
class Creature : public Object
{
public:
	Creature();
	virtual ~Creature();

	virtual void Update() override;
	virtual void Render() override;
};

