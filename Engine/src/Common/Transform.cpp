#include "Vector3.h"
#include "CommonManager.h"
#include "Transform.h"

Transform::Transform() : 
	Component(CommonManager::getInstance(), (int)CommonManager::CommonCmpId::TransId),
	_position(),
	_velocity(),
	_dimensions(),
	_rotation() 
{
}

Transform::Transform(Vector3 pos, Vector3 vel,Vector3 dim, Vector3 rotation) :
	Component(CommonManager::getInstance(), (int)CommonManager::CommonCmpId::TransId),
	_position(pos), //
	_velocity(vel), //
	_dimensions(dim),
	_rotation(rotation) //
{
}

// Si algun parametro no se especifica, se mantendra por defecto
void Transform::load(const nlohmann::json& params)
{
	auto it = params.find("position");
	if (it != params.end()) {
		std::vector<float> pos = it->get<std::vector<float>>();
		_position = Vector3(pos[0], pos[1], pos[2]);
	}
	it = params.find("velocity");
	if (it != params.end()) {
		std::vector<float> pos = it->get<std::vector<float>>();
		_velocity= Vector3(pos[0], pos[1], pos[2]);
	}
	it = params.find("dimensions");
	if (it != params.end()) {
		std::vector<float> pos = it->get<std::vector<float>>();
		_dimensions = Vector3(pos[0], pos[1], pos[2]);
	}
	it = params.find("rotation");
	if (it != params.end()) {
		std::vector<float> pos = it->get<std::vector<float>>();
		_rotation = Vector3(pos[0], pos[1], pos[2]);
	}
}
Transform::~Transform() {
}

void Transform::init() {
	_position = _velocity = _rotation = Vector3();
	_dimensions = Vector3(1.0f, 1.0f, 1.0f);
}



void Transform::update() {

}

 Vector3 Transform::getPos() 
{
	return _position;
}

void Transform::setPos(const Vector3& pos)
{
	_position.set(pos);
}

void Transform::setPosX(double x)
{
	_position.setX(x);
}

void Transform::setPosY(double y)
{
	_position.setY(y);
}

void Transform::setPosZ(double z)
{
	_position.setZ(z);
}

Vector3 Transform::getRot() const
{
	return _rotation;
}

void Transform::setRot(Vector3 angle)
{
	_rotation = angle;
}

void Transform::setRotX(double x)
{
	_rotation.setX(x);
}

void Transform::setRotY(double y)
{
	_rotation.setY(y);
}

void Transform::setRotZ(double z)
{
	_rotation.setZ(z);
}

const Vector3& Transform::getVel() const
{
	return _velocity;
}

void Transform::setVel(const Vector3& vel)
{
	_velocity.set(vel);
}

void Transform::setVelX(double x)
{
	_velocity.setX(x);
}

void Transform::setVelY(double y)
{
	_velocity.setY(y);
}

void Transform::setVelZ(double z)
{
	_velocity.setZ(z);
}

Vector3 Transform::getDimensions()
{
	return _dimensions;
}

void Transform::setDimensions(const Vector3 dim)
{
	_dimensions.set(dim);
}

void Transform::setDimX(double x)
{
	_dimensions.setX(x);
}

void Transform::setDimY(double y)
{
	_dimensions.setY(y);
}

void Transform::setDimZ(double z)
{
	_dimensions.setZ(z);
}

