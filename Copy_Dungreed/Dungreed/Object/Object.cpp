#include "framework.h"
#include "Object.h"

Object::Object(int level, int num)
	: _level(level)
	, _num(num)
{
}


void Object::Update()
{
	if (_playingAnim == true)
	{
		_anim->_animRunTime += DELTA_TIME;
		if (_anim->_animRunTime >= _anim->_animSpeed[_anim->_index.first][_anim->_index.second])
		{
			_anim->_animRunTime = 0;
			_anim->_index.second++;
			if (_anim->_index.second < _anim->_animList.size())
			{
				_texture->SetTexture(_anim->_animList[_anim->_index.first][_anim->_index.second]);
			}
			else
			{
				switch (_anim->_state)
				{
				case Animation::State::END:
					_playingAnim = false;
					break;
				case Animation::State::LOOP:
					_anim->_index.second = 0;
					_texture->SetTexture(_anim->_animList[_anim->_index.first][_anim->_index.second]);
					break;
				case Animation::State::PINGPONG:
					_anim->_index.second = 1;
					reverse(_anim->_animList[_anim->_index.first].begin(), _anim->_animList[_anim->_index.first].end());
					_texture->SetTexture(_anim->_animList[_anim->_index.first][_anim->_index.second]);
					break;
				}
			}
		}
	}

	_texture->Update();
	_collider->Update();
}

void Object::Render()
{
	_texture->Render();
}

void Object::PostRender()
{
	_collider->Render();
}

void Object::SetCollider()
{
	_collider = make_shared<RectCollider>(_texture->GetHalfSize());
	_collider->SetParent(_texture->GetTransform());
}

bool Object::operator<(const Object& value)
{
	return (this->GetTexture()->GetTransform()->GetPos().x <
		value._texture->GetTransform()->GetPos().x);
}

bool Object::operator>(const Object& value)
{
	return (this->GetTexture()->GetTransform()->GetPos().x >
		value._texture->GetTransform()->GetPos().x);
}

bool Object::operator<=(const Object& value)
{
	return (this->GetTexture()->GetTransform()->GetPos().x <=
		value._texture->GetTransform()->GetPos().x);
}

bool Object::operator>=(const Object& value)
{
	return (this->GetTexture()->GetTransform()->GetPos().x >=
		value._texture->GetTransform()->GetPos().x);
}

