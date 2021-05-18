#pragma once

#ifndef _PHYSICS_RIGIDBODY_H
#define _PHYSICS_RIGIDBODY_H

#include "Component.h"
#include <iostream>

class btCollisionShape;
class Vector3;
class Entity;
class btRigidBody;
class Transform;

enum class Forces {
	NORMAL = 0,
	IMPULSE = 1
};

class RigidBody : public Component
{
private:
	//Masa del Rigidbody
	float mass = 1.0f;
	//Rigidbody principal
	btRigidBody* rb;
	Transform* tr_ = nullptr;
	bool trigger = false;

	bool collidesWithEntity(Entity* other) const;
public:
	/// <summary>
	/// Constructora por defecto Rigibody
	/// </summary>
	RigidBody();
	virtual ~RigidBody();


	virtual void setUp();
	virtual void init();
	virtual void update();
	/// <summary>
	/// Carga datos a partir de un json
	/// </summary>
	virtual void load(const nlohmann::json& params);
#pragma region Setters

	//metodo que setea la posicion del rb
	void setPosition(const Vector3& newPos);

	//Asigna una nueva gravedad al componente
	void setGravity(const Vector3& newGrav);

	//metodo que si recibe true hara que el rigidbody active sus flags de colision para que estos actuen como trigger,
	//si es false desactivara sus flags de colision para que este deje de ser un trigger.
	void setTrigger(bool trigger_);

	//metodo que si recibe true hara que el rigidbody active sus flags de colision para que estos actuen como kinematic,
	//si es false desactivara sus flags de colision para que este deje de ser un kinematic.
	void setKinematic(bool kinematic_);

	//metodo que si recibe true hara que el rigidbody active sus flags de colision para que estos actuen como static,
	//si es false desactivara sus flags de colision para que este deje de ser un static.
	void setStatic(bool _static);

	//metodo que setea el coeficiente de restitucion del rb
	//a mayor restitucion, mayor conservacion de la energia y,
	//a menor restitucion, menor conservacion de la energia.
	//Su valor oscila entre 0 y 1.
	void setRestitution(float restitution);

	//metodo que setea la velocidad lineal del rb
	void setLinearVelocity(const Vector3& vel);

	//metodo que setea el rozamiento del rb
	void setFriction(float friction);

	//Cambia el la forma del rigidbody (ShapeCollision)
	void setCollisionShape(btCollisionShape* newShape);
#pragma endregion

#pragma region Getters
	//metodo que devuelve la velocidad lineal del rb
	//const Vector3& getLinearVelocity();
	const Vector3& getLinearVelocity() const;

	//metodo que nos dice si el rigidbody es trigger o no
	bool isTrigger() const;

	//metodo que nos dice si el rigidbody es kinematic
	bool isKinematic() const;

	//metodo que nos dice si el rigidbody es estatico
	bool isStatic() const;

	//btCollisionShape* getShape();
	btCollisionShape* getShape() const;

	//btRigidBody* getBtRb();
	btRigidBody* getBtRb() const;
#pragma endregion

#pragma region Adders
	//Aplica fuerza al rigidbody de tipo Forces
	//a una posicion relativa del objeto, es decir,
	//la parte del cuerpo donde se aplica la fuerza
	void addForce(const Vector3& force, Vector3& relativePos, int type =(int)Forces::NORMAL);


	//Aplica una fuerza de giro al objeto de tipo Forces
	void addTorque(const Vector3& torque, Forces type = Forces::NORMAL);
#pragma endregion

#pragma region Colisiones
	//Comprueba la colision con otro objeto de la escena
	bool onCollisionEnter(const std::string& id) const;

	//Comprueba la colisiones con otros objetos con un tag
	//dentro de la escena especifica
	Entity* collidesWithTag(const std::string& tag) const;
#pragma endregion
};

#endif