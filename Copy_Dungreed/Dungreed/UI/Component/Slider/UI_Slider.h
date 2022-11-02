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
	shared_ptr<UI_Button> _base;
	shared_ptr<Quad> _thumb;	
	float _ratio = 0.5f;
	bool _hold = false;

};
