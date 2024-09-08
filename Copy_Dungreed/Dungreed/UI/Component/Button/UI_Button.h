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
	shared_ptr<Quad> _texture; // ��ư �ؽ���
	shared_ptr<Quad> _hoverTexture; // ������ �� �ؽ���
	shared_ptr<Collider> _collider; // ���ȴ��� Ȯ���ϴ� �ؽ���

	bool _hover = false; // ���콺 Ŀ���� ���� �÷��� �ִ���
	bool _click = false; // ���콺�� ���ȴ���

	function<void()> _hoverStartFunc; // Ŀ���� ��ư ���� ó�� �ö󰬴ٸ�
	function<void()> _hoverUpdateFunc; // Ŀ���� ��ư ���� �ö󰬴ٸ�
	function<void()> _hoverEndFunc; // Ŀ���� ��ư ������ �����ٸ�

	function<void()> _keyDownFunc; // ���콺�� ������ �����ϸ� ȣ��
	function<void()> _keyPressFunc; // ���콺�� ������ ���� �� ȣ��
	function<void()> _keyUpFunc; // ���콺�� ������ ���� ȣ��

};

