#pragma once
class UI_Slider : UI_Component
{
public:
	UI_Slider();

	virtual void Update() override;
	virtual void Render() override;

	const float& GetRatio() { return _ratio; }
	virtual const Vector2& GetPos() override { return _base->GetPos(); }

	virtual void SetPos(const Vector2& pos) override;
	virtual void SetButton(shared_ptr<UI_Button> button);
	virtual void SetThumb(shared_ptr<Quad> texture) { _thumb = texture; }
	virtual void SetRatio(const float& ratio);

protected:
	shared_ptr<UI_Button> _base; // 슬라이더 베이스 
	shared_ptr<Quad> _thumb; // 슬라이더 바 
	float _ratio = 0.5f; // 슬라이더 왼쪽 끝이 0, 오른쪽 끝이 1라 했을 때 비율
	bool _hold = false; // 슬라이더 바를 누르고 있는지
	
};
