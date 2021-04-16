#pragma once

#ifndef _COMMON_VECTOR3_H
#define _COMMON_VECTOR3_H

#include <string>

class Vector3
{
public:
	 float x; //Guarda el valor en el eje X
	 float y; //Guarda el valor en el eje X
	 float z; //Guarda el valor en el eje X

	//Constructor por defecto(todos los valores a cero
	Vector3();
	//Constructor
	Vector3(const float x1, const float y1, const float z1);
	Vector3(std::string s);
	//Invertir todos los valores del vector
	void invert();
	// Optener la magnitud del vector
	float magnitude() const;
	
	//Obtener la magnitud del vector al cuadrado
	float squareMagnitude() const;
	
	// Multiplicar el vector por un escalar
	void operator*=(const float k);

	//Devuelve la copia de un vector multiplicado por un escalar
	Vector3 operator*(const float k);

	//normalizar el vector
	float normalize();

	//producto escalar de dos vectores
	float operator*(const Vector3& v) const;

	// Funcion para el producto escalar
	float dot(const Vector3& v) const;

	// sumar dos vectores
	Vector3 operator+(const Vector3& other);
	
	// Suma a tu vector otro
	void operator+=(const Vector3& other);

   // restar dos vectores
	Vector3 operator-(const Vector3& other);

	//restar a tu vector otro
	void operator-=(const Vector3& other);

	//comparar dos vectores
	bool operator==(const Vector3& other);

	//producto vectorial
	Vector3 operator%(const Vector3& v);

	//setter 
	void set(Vector3 pos);
	void setX(float n);
	void setY(float n);
	void setZ(float n);
};

#endif