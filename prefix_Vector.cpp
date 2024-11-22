#include "prefix_Vector.h"

using namespace std;

Vector::Vector(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vector::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector Vector::operator-(Vector v)
{
	Vector result;
	result.x = this->x - v.x;
	result.y = this->y - v.y;
	result.z = this->z - v.z;
	return result;
}

Vector Vector::operator-=(Vector v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

Vector Vector::operator+(Vector v)
{
	Vector result;
	result.x = this->x + v.x;
	result.y = this->y + v.y;
	result.z = this->z + v.z;
	return result;
}

Vector Vector::operator+=(Vector v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}


Vector Vector::operator*(float f)
{
	Vector result;
	result.x = this->x * f;
	result.y = this->y * f;
	result.z = this->z * f;
	return result;
}

Vector Vector::operator*=(float f)
{
	this->x *= f;
	this->y *= f;
	this->z *= f;
	return *this;
}

float Vector::operator^(Vector v)
{
	return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vector Vector::operator/(float f)
{
	Vector result;
	result.x = this->x / f;
	result.y = this->y / f;
	result.z = this->z / f;
	return result;
}

Vector Vector::operator/=(float f)
{
	this->x /= f;
	this->y /= f;
	this->z /= f;
	return *this;
}

Vector Vector::operator*(Vector v)
{
	Vector result;
	result.x = this->y * v.z - this->z * v.y;
	result.y = this->z * v.x - this->x * v.z;
	result.z = this->x * v.y - this->y * v.x;
	return result;
}

Vector Vector::operator*=(Vector v)
{
	Vector result;
	result.x = this->y * v.z - this->z * v.y;
	result.y = this->z * v.x - this->x * v.z;
	result.z = this->x * v.y - this->y * v.x;
	return result;
}

Vector Vector::operator-()
{
	Vector result;
	result.x = -this->x;
	result.y = -this->y;
	result.z = -this->z;
	return result;

}

Vector Vector::operator!()
{
	Vector result;
	float length = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	result.x = this->x / length;
	result.y = this->y / length;
	result.z = this->z / length;
	return result;
}


float Vector::operator~()
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

bool Vector::operator==(Vector v)
{
	return this->x == v.x && this->y == v.y && this->z == v.z;
}

bool Vector::operator!=(Vector v)
{
	return this->x != v.x || this->y != v.y || this->z != v.z;
}

bool Vector::operator>(Vector v)
{
	return this->x > v.x && this->y > v.y && this->z > v.z;
}

bool Vector::operator<(Vector v)
{
	return this->x < v.x && this->y < v.y && this->z < v.z;
}

bool Vector::operator>=(Vector v)
{
	return this->x >= v.x && this->y >= v.y && this->z >= v.z;
}

bool Vector::operator<=(Vector v)
{
	return this->x <= v.x && this->y <= v.y && this->z <= v.z;
}

void Vector::reset()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

string Vector::toString() const
{
	return "( X: " + to_string(this->x) + " Y: " + to_string(this->y) + " Z: " + to_string(this->z) + " )";
}







