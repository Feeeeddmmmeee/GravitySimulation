#include "Vector.h"

Vector::Vector()
{
	x = 0;
	y = 0;
}

Vector::Vector(double x, double y)
{
	this->x = x;
	this->y = y;
}

Vector& Vector::Add(const Vector& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector& Vector::Substract(const Vector& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector& Vector::Multiply(const Vector& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector& Vector::Divide(const Vector& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

Vector& operator+(Vector vec1, const Vector vec2)
{
	return vec1.Add(vec2);
}

Vector& operator-(Vector vec1, const Vector vec2)
{
	return vec1.Substract(vec2);
}

Vector& operator*(Vector vec1, const Vector vec2)
{
	return vec1.Multiply(vec2);
}

Vector& operator/(Vector vec1, const Vector vec2)
{
	return vec1.Divide(vec2);
}

Vector& Vector::operator+=(const Vector vec)
{
	return this->Add(vec);
}

Vector& Vector::operator-=(const Vector vec)
{
	return this->Substract(vec);
}

Vector& Vector::operator*=(const Vector vec)
{
	return this->Multiply(vec);
}

Vector& Vector::operator/=(const Vector vec)
{
	return this->Divide(vec);
}

Vector& Vector::operator/(const double& i)
{
	this->x /= i;
	this->y /= i;

	return *this;
}

Vector& Vector::operator*(const double& i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}

Vector& Vector::Zero()
{
	this->x = 0;
	this->y = 0;

	return *this;
}

double Vector::Lenght()
{
	return sqrt(this->x * this->x + this->y * this->y);
}

std::ostream& operator<<(std::ostream& stream, const Vector vec)
{
	stream << "Vector(" << vec.x << ", " << vec.y << ")";
	return stream;
}