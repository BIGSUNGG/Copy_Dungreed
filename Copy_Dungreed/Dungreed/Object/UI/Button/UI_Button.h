#pragma once
class UI_Button : public UI
{
public:
	UI_Button();

	virtual void Update() override;
	virtual void Render() override;

	bool GetHover() { return _hover; }

	void SetHoverTexture(shared_ptr<Quad> hoverTexture);

protected:
	bool _hover = false;
	shared_ptr<Quad> _hoverTexture;

};

