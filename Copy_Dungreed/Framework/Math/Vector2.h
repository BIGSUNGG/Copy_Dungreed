#pragma once
class Vector2 : public XMFLOAT2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(int x, int y);
	~Vector2();

	Vector2 operator+(const Vector2& value) const;
	Vector2 operator-(const Vector2& value) const;
	Vector2 operator*(const float& value) const;

	Vector2& operator+=(const Vector2& value);
	Vector2& operator-=(const Vector2& value);
	Vector2& operator*=(const float& value);

	bool operator==(const Vector2& value) const;
	bool operator!=(const Vector2& value) const;
	bool operator<(const Vector2& value) const;

	Vector2& operator=(const Vector2& value);

	void Normalize();

	float Distance(const Vector2& value) const;
	float Length() const;

	// ³»Àû
	float Dot(const Vector2& value);
	float Cross(const Vector2& value);

	bool IsBetween(const Vector2& value1, const Vector2& value2);
	int Manhattan(const Vector2 value) const;

	float Angle() { return atan2(y, x); }
	float Angle(const Vector2& value);

	static Vector2 TransformCoord(const Vector2& vector, const XMMATRIX& matrix);
};

