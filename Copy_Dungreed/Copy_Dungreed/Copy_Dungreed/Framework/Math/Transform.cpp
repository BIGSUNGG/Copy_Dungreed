#include "framework.h"
#include "Transform.h"

Transform::Transform()
{
	_worldBuffer = make_shared<MatrixBuffer>();
}

Transform::~Transform()
{
}

void Transform::UpdateWorld()
{
    // SRT Matrix ¼³Á¤
    _scaleM = XMMatrixScaling(_scale.x, _scale.y, 1);
    _rotationM = XMMatrixRotationZ(_angle);
    _translateM = XMMatrixTranslation(_pos.x, _pos.y, 0);

    _srtMatrix = _scaleM * _rotationM * _translateM;

    if (_parent != nullptr)
    {
        _srtMatrix *= (_parent->GetMatrix());
    }

    _worldBuffer->Set(_srtMatrix);
}

void Transform::SetBuffer(UINT slot)
{
    _worldBuffer->SetVSBuffer(slot);
}

Vector2 Transform::GetWorldPos()
{
    XMFLOAT4X4 matrix;
    XMStoreFloat4x4(&matrix, _srtMatrix);

    return Vector2(matrix._41,matrix._42);
}

Vector2 Transform::GetWorldScale()
{
    Vector2 result = _scale;
    if (_parent)
    {
        result.x *= _parent->GetWorldScale().x;
        result.y *= _parent->GetWorldScale().y;
    }

    return result;
}
