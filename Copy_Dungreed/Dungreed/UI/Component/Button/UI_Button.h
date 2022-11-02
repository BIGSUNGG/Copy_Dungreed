#pragma once
class UI_Button : public UI_Component
{
public:
	UI_Button();

	virtual void Update() override;
	virtual void Render() override;

	bool GetHover() { return _hover; }
	shared_ptr<Quad> GetTexture() { return _texture; }
	virtual const Vector2& GetPos() override { return _texture->GetTransform()->GetPos(); }

	virtual void SetPos(const Vector2& pos) override;
	void SetTexture(shared_ptr<Quad> texture);
	void SetHoverTexture(shared_ptr<Quad> hoverTexture) { _hoverTexture = hoverTexture; }

	void SetKeyPressEvent(function<void()> func) { _keyPressFunc = func; }
	void SetKeyDownEvent(function<void()> func) { _keyDownFunc = func; }
	void SetKeyUpEvent(function<void()> func) { _keyUpFunc = func; }

protected:
	shared_ptr<Quad> _texture;
	shared_ptr<Quad> _hoverTexture;
	shared_ptr<Collider> _collider;

	bool _hover = false;
	bool _click = false;
	function<void()> _keyDownFunc;
	function<void()> _keyPressFunc;
	function<void()> _keyUpFunc;

};

