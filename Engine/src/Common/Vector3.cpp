#include "Vector3.h"

#include <iostream>
#include <math.h>
#include <exception>

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) 
{
}

Vector3::Vector3(const float x1, const float y1, const float z1) :
	x(x1), y(y1), z(z1)
{
}

// Se puede tratar la excepcion en el load, si no se trata aqui
Vector3::Vector3(const std::vector<float>& pos)
{
	if (pos.size() >= 3) {
		x = pos[0]; y = pos[1]; z = pos[2];
	}
	else 
		x = y = z = 0.0f;
}

Vector3::Vector3(const Vector3& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

// string format"[0.0, 0.0, 0.0]"
/*Vector3::Vector3(std::string s)
{
	std::string delimiter = ",";
	size_t pos = 0;
	std::string value;
	float values[3];
	try {
		s.erase(0, pos + delimiter.length());
		s.erase(s.length() - 1, s.length());
	}
	catch (std::exception e) { throw std::exception("ERROR: Incorrect vector format\n"); }

	int i = 0;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		value = s.substr(0, pos);
		s.erase(0, pos + delimiter.length());
		try{ 
			values[i++] = std::stof(value); 
		}
		catch(std::exception e) {
			throw std::exception("ERROR: Incorrect vector format\n"); 
		}
		
	}
	x = values[0];
	y = values[1];
	z = std::stof(s);
}*/

void Vector3::invert()
{
	x = -x;
	y = -y;
	z = -z;
}

float Vector3::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

float Vector3::squareMagnitude() const
{
	return x * x + y * y + z * z;
}

void Vector3::operator*=(const float k)
{
	x *= k;
	y *= k;
	z *= k;
}

Vector3 Vector3::operator*(const float k)
{
	return Vector3(x*k, y*k, z*k);
}


float Vector3::normalize()
{
	float m = magnitude();
	*this *= 1.0f / m;
	return m;
}

float Vector3::operator*(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

float Vector3::dot(const Vector3& v) const
{
	return x*v.x + y*v.y + z* v.z;
}

Vector3 Vector3::operator+(const Vector3& other)
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

void Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}

Vector3 Vector3::operator-(const Vector3& other)
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

void Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

bool Vector3::operator==(const Vector3& other)
{
	return x == other.x && y == other.y && z == other.z;
}

Vector3 Vector3::operator%(const Vector3& v)
{
	return Vector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

bool Vector3::isZero() const
{
	return x == 0 && y == 0 && z == 0;
}

void Vector3::set(Vector3 v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

void Vector3::setX(float n)
{
	x = n;
}

void Vector3::setY(float n)
{
	y = n;
}

void Vector3::setZ(float n)
{
	z = n;
}