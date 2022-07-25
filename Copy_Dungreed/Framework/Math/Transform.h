#pragma once
class MatrixBuffer;

class Transform
{
public:
	Transform();
	~Transform();

	void UpdateWorld();
	void SetBuffer(UINT slot);

	Vector2& GetScale() { return _scale; }
	float& GetAngle() { return _angle; }
	Vector2& GetPos() { return _pos; }
	Vector2 GetWorldPos();
	Vector2 GetWorldScale();

	void SetParent(shared_ptr<Transform> transform) { _parent = transform; }

	const XMMATRIX& GetMatrix() { return _srtMatrix; }
	XMMATRIX* GetSMatrix() { return &_scaleM; }
	XMMATRIX* GetRMatrix() { return &_rotationM; }
	XMMATRIX* GetTMatrix() { return &_translateM; }

private:
	Vector2 _scale = { 1.0f,1.0f };
	float _angle = { 0.0f };
	Vector2 _pos = { 0.0f, 0.0f };

	XMMATRIX _scaleM = XMMatrixIdentity();
	XMMATRIX _rotationM = XMMatrixIdentity();
	XMMATRIX _translateM = XMMatrixIdentity();

	XMMATRIX _srtMatrix = XMMatrixIdentity();
	shared_ptr<MatrixBuffer> _worldBuffer;

	shared_ptr<Transform> _parent = nullptr;
};

