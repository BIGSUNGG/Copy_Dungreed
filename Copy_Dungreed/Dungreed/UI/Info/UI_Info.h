#pragma once
class UI_Info : public UI
{
public:
	UI_Info();

	virtual void Update() override;
	virtual void Render() override;

protected:
	shared_ptr<Quad> _goldIcon; // 골드 아이콘 이미지
	shared_ptr<UI_Text> _goldText; // 골드 텍스트

	shared_ptr<Quad> _hungryIcon; // 허기 아이콘 이미지
	shared_ptr<Quad> _hungryBase; // 허기 베이스 이미지
	shared_ptr<Quad> _hungryGauge; // 허기 게이지 이미지
	shared_ptr<UI_Text> _hungryText; // 허기 텍스트

};

