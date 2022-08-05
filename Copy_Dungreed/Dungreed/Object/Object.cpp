#include "framework.h"
#include "Object.h"

Object::Object(int level, int num)
	: _level(level)
	, _num(num)
{
}


void Object::Update()
{
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
