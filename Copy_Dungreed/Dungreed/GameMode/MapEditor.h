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

	// _curObject를 맵에 추가하는 함수
	// force : 추가할 위치에 오브젝트가 있어도 무시할지 여부
	void AddObject(bool force = false);
	// _curMousePos에 있는 오브젝트를 제거하는 함수
	void DeleteObject();

	void MouseEvenet();
	void InputEvent();
	void ApplyOffset();
	void ApplyChange();
	void ResetOffset();

public:
	shared_ptr<StageMap> GetCurMap() { return _curMap; }

private:
	shared_ptr<StageMap> _curMap; // 현재 수정중인 맵
	shared_ptr<StageMap> _copyMap; // 복사한 맵

	Vector2				_mouseOffset; // 마우스 오프셋
	Vector2				_mouseAppend; // 현재 마우스 오프셋에서 추가할 위치
	Vector2				_curMousePos; // 현재 오브젝트를 추가할 위치
	shared_ptr<Object>	_curObject; // 맵에 추가할 오브젝트

	bool _freeMode	= false; // true시 마우스 오프셋에 상관없이 오프젝트 위치 설정
	bool _autoSave	= true; // 오브젝트 수정 시 자동으로 저장할지 여부

	int _objectType		= Object::TILE; // 맵에 추가할 오브젝트 타입
	int _objectLevel	= 1; // 맵에 추가할 오브젝트의 레벨
	int _objectNum		= 0; // 맵에 추가할 오브젝트의 번호

	int _mapLevel	= 0; // 수정할 맵의 레벨
	int _mapNum		= 0; // 수정할 맵의 번호

	const Vector2 _verticalDoorHalfSize = { 60.0f, 198.0f }; // 좌 우 문의 크기
	const Vector2 _horizonialDoorHalfSize = { 198.0f, 60.0f }; // 위 아래 문의 크기
};

