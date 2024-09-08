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

	void SetHoverStartEvent(function<void()> func) { _hoverStartFunc = func; }
	void SetHoverUpdateEvent(function<void()> func) { _hoverUpdateFunc = func; }
	void SetHoverEndEvent(function<void()> func) { _hoverEndFunc = func; }

	void SetKeyPressEvent(function<void()> func) { _keyPressFunc = func; }
	void SetKeyDownEvent(function<void()> func) { _keyDownFunc = func; }
	void SetKeyUpEvent(function<void()> func) { _keyUpFunc = func; }

protected:
	shared_ptr<Quad> _texture; // 버튼 텍스쳐
	shared_ptr<Quad> _hoverTexture; // 눌렸을 때 텍스쳐
	shared_ptr<Collider> _collider; // 눌렸는지 확인하는 텍스쳐

	bool _hover = false; // 마우스 커서가 위에 올려져 있는지
	bool _click = false; // 마우스가 눌렸는지

	function<void()> _hoverStartFunc; // 커서가 버튼 위로 처음 올라갔다면
	function<void()> _hoverUpdateFunc; // 커서가 버튼 위로 올라갔다면
	function<void()> _hoverEndFunc; // 커서가 버튼 밖으로 나갔다면

	function<void()> _keyDownFunc; // 마우스를 누르기 시작하면 호출
	function<void()> _keyPressFunc; // 마우스를 누르고 있을 때 호출
	function<void()> _keyUpFunc; // 마우스를 누르다 때면 호출

};

