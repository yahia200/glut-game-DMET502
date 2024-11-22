#pragma once
#include <math.h>
#include <string>

class Vector
{
public:
	float x, y, z;
	Vector(float x = 0, float y = 0, float z = 0);
	void set(float x, float y, float z);
	// Vector Addition
	Vector operator+(Vector v);
	Vector operator+=(Vector v);

	// Vector Subtraction
	Vector operator-(Vector v);
	Vector operator-=(Vector v);

	// Scalar Multiplication
	Vector operator*(float f);
	Vector operator*=(float f);

	// Scalar Division
	Vector operator/(float f);
	Vector operator/=(float f);

	// Vector Multiplication
	Vector operator*(Vector v);
	Vector operator*=(Vector v);

	// Vector Sign Inversion
	Vector operator-();

	// Vector Normalization
	Vector operator!();

	// Vector Length
	float operator~();

	// Dot Product
	float operator^(Vector v);

	// Vector Comparison
	bool operator==(Vector v);
	bool operator!=(Vector v);
	bool operator>(Vector v);
	bool operator<(Vector v);
	bool operator>=(Vector v);
	bool operator<=(Vector v);

	// Vector Reset
	void reset();

	// Vector Output
	std::string toString() const;




};

