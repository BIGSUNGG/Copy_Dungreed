#include "framework.h"
#include "Camera.h"

Camera* Camera::_instance = nullptr;

Camera::Camera()
{
	_transform = make_shared<Transform>();
	_moveTransform = make_shared<Transform>();
	_projectionBuffer = make_shared<MatrixBuffer>();
	_uiCameraBuffer = make_shared<MatrixBuffer>();

	SetProjectionBuffer(2);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (_target != nullptr)
		FollowMode();
	else if (_freeMode == true)
		FreeMode();

	Shake();

	_transform->UpdateWorld();
	_moveTransform->UpdateWorld();
	_moveTransform->GetPos().x = -_transform->GetPos().x;
	_moveTransform->GetPos().y = -_transform->GetPos().y;

	_velocity = (_transform->GetPos() - _beforeMove) / (float)DELTA_TIME * -1;
	_beforeMove = _transform->GetPos();
}

void Camera::ImGuiRender()
{
	ImGui::Text("Pos : %0.1f, %0.1f", _moveTransform->GetPos().x + CENTER.x, _moveTransform->GetPos().y + CENTER.y);
	ImGui::Text("Velocity : %0.1f , %0.1f", _velocity.x, _velocity.y);
}

void Camera::ShakeStart(float magnitude, float duration, float reduceDamping)
{
	_magnitude = magnitude;
	_duration = duration;
	_reduceDamping = reduceDamping;

	_originPos = _transform->GetPos();
}

void Camera::SetViewPort(UINT width, UINT height)
{
	D3D11_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	DEVICE_CONTEXT->RSSetViewports(1, &vp);
}

void Camera::SetProjectionBuffer(UINT width, UINT height)
{
	XMMATRIX projectionM = XMMatrixOrthographicOffCenterLH(0, width, 0, height, -1.0f, 1.0f);

	_projectionBuffer->Set(projectionM);

	_projectionBuffer->SetVSBuffer(2);
}

Vector2 Camera::GetMouseWorldPos()
{
	XMMATRIX inverseView = DirectX::XMMatrixInverse(nullptr, _transform->GetMatrix());

	return Vector2::TransformCoord(MOUSE_POS, inverseView);
}

void Camera::Shake()
{
	if (_duration <= 0.0f)
		return;

	_duration -= DELTA_TIME;
	_magnitude -= DELTA_TIME * _reduceDamping;

	if (_magnitude <= 0.0f)
	{
		_magnitude = 0.0f;
		_duration = 0.0f;
	}

	_transform->GetPos().x = _originPos.x + MathUtility::RandomFloat(-_magnitude, _magnitude);
	_transform->GetPos().y = _originPos.y + MathUtility::RandomFloat(-_magnitude, _magnitude);

	if (_duration <= 0.0f)
		_transform->GetPos() = _originPos;
}

void Camera::FreeMode()
{
	if (KEY_PRESS('W'))
		_transform->GetPos().y -= _controlSpeed * DELTA_TIME;

	if (KEY_PRESS('S'))
		_transform->GetPos().y += _controlSpeed * DELTA_TIME;

	if (KEY_PRESS('A'))
		_transform->GetPos().x += _controlSpeed * DELTA_TIME;

	if (KEY_PRESS('D'))
		_transform->GetPos().x -= _controlSpeed * DELTA_TIME;
}

void Camera::FollowMode()
{
	Vector2 targetPos = _target->GetPos() - _offset;

	if (targetPos.x < _leftBottom.x)
		targetPos.x = _leftBottom.x;

	if (targetPos.x > _rightTop.x - WIN_WIDTH)
		targetPos.x = _rightTop.x - WIN_WIDTH;

	if (targetPos.y < _leftBottom.y)
		targetPos.y = _leftBottom.y;

	if (targetPos.y > _rightTop.y - WIN_HEIGHT)
		targetPos.y = _rightTop.y - WIN_HEIGHT;	

	_transform->GetPos() = targetPos * -1;
}
