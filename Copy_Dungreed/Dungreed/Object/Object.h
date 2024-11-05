#pragma once

class StageMap;

class Object : public enable_shared_from_this<Object>
{
public:
	static const int _objectTypeCount = 7;
	enum Object_Type : unsigned char
	{
		BACKGROUND,
		WALL,
		TILE,
		ETC,
		CREATURE,
		EFFECT,
		NONE,
	};

public:
	Object(int level = 0, int num = 0);
	virtual ~Object() {}

	virtual void Update();
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();
	virtual void ImGuiRender();

	virtual void ReverseTexture();
	virtual void CreateAnimation();

public:
	// Getter Setter
	virtual void SetSpawnPos(Vector2 pos);
	virtual void SetOwnerMap(shared_ptr<StageMap> map);
	virtual void SetTexture(shared_ptr<Quad> texture);
	virtual void SetCollider(shared_ptr<RectCollider> collider = nullptr);

	virtual void SetPos(const Vector2& pos) { _texture->GetTransform()->GetPos() = pos; }
	FORCEINLINE void SetIsCollision(bool value) { _enableCollison = value; }
	FORCEINLINE void SetIsRender(bool value) { _render = value; }

	FORCEINLINE const int& GetNum() { return _num; }
	FORCEINLINE const int& GetLevel() { return _level; }
	FORCEINLINE const Object_Type& GetType() { return _objectType; }

	FORCEINLINE bool IsActive() { return _isActive; }
	FORCEINLINE bool IsStatic() { return _staticObject; }
	FORCEINLINE bool IsCollision() { return _enableCollison; }
	FORCEINLINE bool IsRender() { return _render; }
	FORCEINLINE bool IsReversed() { return _reverseTexture; }

	FORCEINLINE const Vector2& GetSpawnPos() { return _spawnPos; }
	FORCEINLINE Vector2& GetPos() { return _texture->GetTransform()->GetPos(); }

	FORCEINLINE shared_ptr<Quad> GetObjectTexture() { return _texture; }
	FORCEINLINE shared_ptr<RectCollider> GetCollider() { return _collider; }
	FORCEINLINE shared_ptr<Animation> GetAnimation() { return _anim; }

protected:
	Object_Type _objectType = Object_Type::NONE;
	Vector2 _spawnPos = { 0,0 }; // ������Ʈ�� ������ ��ġ
	bool _staticObject = false; // ������ ������Ʈ���� (true �� �ؽ��ĸ� �ν��Ͻ��Ͽ� ������)
	bool _isActive = true; // Ȱ��ȭ�Ǿ� �ִ���
	bool _enableCollison = true; // �浹 Ȯ���� �� ��
	bool _reverseTexture = false; // �ؽ��İ� �����Ǿ�����
	bool _render = true; // �������� �� 

	weak_ptr<StageMap> _ownerMap; // ������Ʈ�� �����ϰ� �ִ� ��
	shared_ptr<Quad> _texture; // �������� �ؽ���
	shared_ptr<Animation> _anim; // �ؽ����� �ִϸ��̼�
	shared_ptr<ObjectBuffer> _buffer; // �ؽ����� ����
	shared_ptr<RectCollider> _collider; // �浹 ó���� �� �ݶ��̴�

	shared_ptr<ComponentCollector> _componentCollector;

	int _level = 0;
	int _num = 0;

};

