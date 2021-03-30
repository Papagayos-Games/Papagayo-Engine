#include "Transform.h"
#include "ecs.h"



Transform::Transform() :
	Component(ecs::Transform), position(),
	velocity(),
	dimensions(),
	rotation() 
{
}

Transform::Transform(Vector3 pos, Vector3 vel,Vector3 dim, double rotation = 0.0) :
	Component(ecs::Transform), position(pos), //
	velocity(vel), //
	dimensions(dim),
	rotation(rotation) //
{
}

Transform::~Transform() {
}

const Vector3& Transform::getPos() const
{
	return position;
}

void Transform::setPos(const Vector3& pos)
{
	position.set(pos);
}

void Transform::setPosX(double x)
{
	position.setX(x);
}

void Transform::setPosY(double y)
{
	position.setY(y);
}

void Transform::setPosZ(double z)
{
	position.setZ(z);
}

double Transform::getRot() const
{
	return rotation;
}

void Transform::setRot(double angle)
{
	rotation = angle;
}

const Vector3& Transform::getVel() const
{
	return velocity;
}

void Transform::setVel(const Vector3& vel)
{
	velocity.set(vel);
}

void Transform::setVelX(double x)
{
	velocity.setX(x);
}

void Transform::setVelY(double y)
{
	velocity.setY(y);
}

void Transform::setVelZ(double z)
{
	velocity.setZ(z);
}

Vector3 Transform::getDimensieons()
{
	return dimensions;
}

void Transform::setDimensions(const Vector3 dim)
{
	dimensions.set(dim);
}

void Transform::setDimX(double x)
{
	dimensions.setX(x);
}

void Transform::setDimY(double y)
{
	dimensions.setY(y);
}

void Transform::setDimZ(double z)
{
	dimensions.setZ(z);
}

