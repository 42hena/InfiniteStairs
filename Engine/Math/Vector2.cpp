#include "Vector2.h"

#include <iostream>

#pragma region STATIC_맴버
Vector2 Vector2::Zero = Vector2(0, 0);
Vector2 Vector2::One = Vector2(1, 1);
Vector2 Vector2::Up = Vector2(0, 1);
Vector2 Vector2::Left = Vector2(-1, 0);
Vector2 Vector2::Right = Vector2(1, 0);
Vector2 Vector2::Down = Vector2(0, -1);
#pragma endregion

#pragma region 특수_맴버_함수
Vector2::Vector2(int x, int y)
	:_x(x), _y(y)
{

}
#pragma endregion

#pragma region 연산자 오버로딩
Vector2 Vector2::operator+(const Vector2& rhs) const	{
	return Vector2(_x + rhs._x, _y+ rhs._y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const	{
	return Vector2(_x - rhs._x, _y - rhs._y);
}

Vector2 Vector2::operator*(const Vector2& rhs) const	{
	return Vector2(_x * rhs._x, _y * rhs._y);
}

Vector2 Vector2::operator/(const Vector2& rhs) const	{
	return Vector2(_x / rhs._x, _y / rhs._y);
}

bool Vector2::operator==(const Vector2& rhs) const
{
	if ((_x - rhs._x) | _y - rhs._y)
		return false;
	return true;
}

bool Vector2::operator!=(const Vector2& rhs) const
{
	return !operator==(rhs);
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	_x += rhs._x;
	_y += rhs._y;
	return *this;
}
Vector2& Vector2::operator-=(const Vector2& rhs)
{
	_x -= rhs._x;
	_y -= rhs._y;
	return *this;
}
Vector2& Vector2::operator*=(const Vector2& rhs)
{
	_x *= rhs._x;
	_y *= rhs._y;
	return *this;
}
Vector2& Vector2::operator/=(const Vector2& rhs)
{
	_x /= rhs._x;
	_y /= rhs._y;
	return *this;
}
#pragma endregion

#pragma region 공개 함수
const char* Vector2::ToString()
{
	static char buffer[256];
	sprintf_s(buffer, 256, "(%d, %d)", _x, _y);
	
	return buffer;
}
Vector2 Vector2::Add(const Vector2& rhs) const
{
	return Vector2(_x + rhs._x, _y + rhs._y);
}
Vector2 Vector2::Substract(const Vector2& rhs) const
{
	return Vector2(_x - rhs._x, _y - rhs._y);
}
Vector2 Vector2::Multiply(const Vector2& rhs) const
{
	return (*this) * rhs;
}
Vector2 Vector2::Divide(const Vector2& rhs) const
{
	return (*this) / rhs;
}

/* 형 변환 연산자 */
Vector2::operator COORD()
{
	COORD coord;

	coord.X = static_cast<short>(_x);
	coord.Y = static_cast<short>(_y);

	return coord;
}

Vector2::operator COORD() const
{
	COORD coord;

	coord.X = static_cast<short>(_x);
	coord.Y = static_cast<short>(_y);

	return coord;
}

#pragma endregion
