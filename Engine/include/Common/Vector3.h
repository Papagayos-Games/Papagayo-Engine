#include <iostream>
#include <math.h>

class Vector3
{
public:
	 float x; //Guarda el valor en el eje X
	 float y; //Guarda el valor en el eje X
	 float z; //Guarda el valor en el eje X

public:
	//Constructor por defecto(todos los valores a cero
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	//Constructor
	Vector3(const float x1, const float y1, const float z1): x(x1),y(y1),z(z1){}

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

	//producto vectorial
	Vector3 operator%(const Vector3& v);

	//setter 
	void set(Vector3 pos);
	void setX(float n);
	void setY(float n);
	void setZ(float n);



};