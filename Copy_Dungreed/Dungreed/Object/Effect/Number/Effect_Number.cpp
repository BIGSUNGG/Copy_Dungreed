#include "framework.h"
#include "Effect_Number.h"

Effect_Number::Effect_Number()
	: Effect(0,0)
{
	_buffer->_data.selected = 1;
	_buffer->_data.value1 = 1;
	_buffer->_data.value2 = 1;
	_buffer->_data.value3 = 1;
	_buffer->_data.value4 = 1;
}

void Effect_Number::Update()
{	
	_runTime += DELTA_TIME;
	if (_runTime >= _alphaStartTime) 
	{
		// 문자 텍스쳐를 점점 사라지게함
		_buffer->_data.value4 -= _alphaSpeed * DELTA_TIME;

		// 완전히 사라질 경우 오브젝트 비활성화
		if (_buffer->_data.value4 <= 0)
			_isActive = false;
	}

	// 오브젝트에 중력 적용
	_velocity.y -= _gravity * DELTA_TIME;
	for (int i = 0; i < _text.size(); i++)
	{
		_text[i]->GetTransform()->GetPos() += _velocity * DELTA_TIME;
		_text[i]->Update();
	}
}

void Effect_Number::Render()
{
	_buffer->SetPSBuffer(0);

	for (int i = 0; i < _text.size(); i++)
	{
		_text[i]->Render();
	}
}

void Effect_Number::SetColor(const XMFLOAT4& color)
{
	_buffer->_data.value1 = color.x;
	_buffer->_data.value2 = color.y;
	_buffer->_data.value3 = color.z;
	_buffer->_data.value4 = color.w;
}

void Effect_Number::SetPos(const Vector2& pos)
{
	_text.front()->GetTransform()->GetPos() = pos;
	for (int i = 1; i < _text.size(); i++)
	{
		_text[i]->SetLeft(_text[i - 1]->Right() + _term);
		_text[i]->GetTransform()->GetPos().y = _text[i - 1]->GetTransform()->GetPos().y;
	}
}

void Effect_Number::SetNumber(const int& damage)
{
	_text.clear();
	wstring number = to_wstring(damage);

	for (int i = 0; i < number.size(); i++)
	{
		int t = (int)number[i] - 48;
		wstring image = OBJ_MANAGER->GetNumberImage(t);
		_text.emplace_back(make_shared<Quad>(image));
		_text.back()->SetPS(L"Shader/ObjectShader/ObjectPixelShader.hlsl");
	}
}
