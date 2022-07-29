#pragma once
class BackGround : public Object
{
public:
	BackGround(int level,int num);
	~BackGround();

	void Update() override;
	void Render() override;
	void PostRender() override;
};

