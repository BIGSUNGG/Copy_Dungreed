#pragma once
class MapEditor : public GameMode
{
public:
	MapEditor();
	MapEditor(int level, int num);

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void ImGuiRender() override;

protected:
	void Init(shared_ptr<StageMap> editMap);

	// _curObject�� �ʿ� �߰��ϴ� �Լ�
	// force : �߰��� ��ġ�� ������Ʈ�� �־ �������� ����
	void AddObject(bool force = false);
	// _curMousePos�� �ִ� ������Ʈ�� �����ϴ� �Լ�
	void DeleteObject();

	void MouseEvenet();
	void InputEvent();
	void ApplyOffset();
	void ApplyChange();
	void ResetOffset();

public:
	shared_ptr<StageMap> GetCurMap() { return _curMap; }

private:
	shared_ptr<StageMap> _curMap; // ���� �������� ��
	shared_ptr<StageMap> _copyMap; // ������ ��

	Vector2				_mouseOffset; // ���콺 ������
	Vector2				_mouseAppend; // ���� ���콺 �����¿��� �߰��� ��ġ
	Vector2				_curMousePos; // ���� ������Ʈ�� �߰��� ��ġ
	shared_ptr<Object>	_curObject; // �ʿ� �߰��� ������Ʈ

	bool _freeMode	= false; // true�� ���콺 �����¿� ������� ������Ʈ ��ġ ����
	bool _autoSave	= true; // ������Ʈ ���� �� �ڵ����� �������� ����

	int _objectType		= Object::TILE; // �ʿ� �߰��� ������Ʈ Ÿ��
	int _objectLevel	= 1; // �ʿ� �߰��� ������Ʈ�� ����
	int _objectNum		= 0; // �ʿ� �߰��� ������Ʈ�� ��ȣ

	int _mapLevel	= 0; // ������ ���� ����
	int _mapNum		= 0; // ������ ���� ��ȣ

	const Vector2 _verticalDoorHalfSize = { 60.0f, 198.0f }; // �� �� ���� ũ��
	const Vector2 _horizonialDoorHalfSize = { 198.0f, 60.0f }; // �� �Ʒ� ���� ũ��
};

