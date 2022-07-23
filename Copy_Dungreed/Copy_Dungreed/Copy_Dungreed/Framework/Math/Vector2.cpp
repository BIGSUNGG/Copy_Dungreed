#include "framework.h"
#include "Vector2.h"

Vector2::Vector2()
: XMFLOAT2()
{
}

Vector2::Vector2(float x, float y)
: XMFLOAT2(x,y)
{
}

Vector2::Vector2(int x, int y)
: XMFLOAT2(float(x), float(y))
{
}

Vector2::~Vector2()
{
}

Vector2 Vector2::operator+(const Vector2& value) const
{
    return Vector2(x + value.x, y+value.y);
}

Vector2 Vector2::operator-(const Vector2& value) const
{
    return Vector2(x - value.x, y - value.y);
}

Vector2 Vector2::operator*(const float& value) const
{
    return Vector2(x * value, y * value);
}

Vector2& Vector2::operator+=(const Vector2& value)
{
    x += value.x;
    y += value.y;

    return *this;
}

Vector2& Vector2::operator-=(const Vector2& value)
{
    x -= value.x;
    y -= value.y;

    return *this;
}

Vector2& Vector2::operator*=(const float& value)
{
    x *= value;
    y *= value;

    return *this;
}

bool Vector2::operator==(const Vector2& value) const
{
    if (x == value.x && y == value.y)
        return true;

    return false;
}

bool Vector2::operator!=(const Vector2& value) const
{
    return !(*this == value);
}

bool Vector2::operator<(const Vector2& value) const
{
    if (y != value.y)
        return y < value.y;

    return x < value.x;
}

Vector2& Vector2::operator=(const Vector2& value)
{
    x = value.x;
    y = value.y;

    return *this;
}

void Vector2::Normalize()
{
    float length = Length();
    x = x / length;
    y = y / length;
}

float Vector2::Distance(const Vector2& value) const
{
    float tempX = value.x - x;
    float tempY = value.y - y;
    return sqrtf(tempX * tempX + tempY * tempY);
}

float Vector2::Length() const
{
    return sqrtf(x * x + y * y);
}

float Vector2::Dot(const Vector2& value)
{
    return x* value.x + y*value.y;
}

float Vector2::Cross(const Vector2& value)
{
    return x * value.y - y*value.x;
}

bool Vector2::IsBetween(const Vector2& value1, const Vector2& value2)
{
    Vector2 temp1 = value1;
    Vector2 temp2 = value2;

    Vector2 line1ToEnd = temp1 - *this;
    Vector2 line1ToStart = temp2 - *this;

    float between = line1ToEnd.Cross(*this) * line1ToStart.Cross(*this);

    return between < 0.0f;
}

int Vector2::Manhattan(const Vector2 value) const
{
    return (value.x - x) + (value.y - y);
}

float Vector2::Angle(const Vector2& value)
{
    float dot = this->Dot(value);
    float aDis = abs(this->Length());
    float bDis = abs(value.Length());

    float cos = dot / (aDis * bDis);

    return acos(cos);
}

Vector2 Vector2::TransformCoord(const Vector2& vector, const XMMATRIX& matrix)
{
    XMVECTOR temp = XMLoadFloat2(&vector);

    temp = XMVector2TransformCoord(temp, matrix);

    Vector2 result;
    XMStoreFloat2(&result, temp);

    return result;
}
