#pragma once

#ifndef _COMMON_TRANSFORM_H
#define _COMMON_TRANSFORM_H

#include "Component.h"
#include "Vector3.h"
#include <map>
#include <string>

//class Vector3;
class CommonManager;

class Transform : public Component {
private:
	Vector3 _position;
	Vector3 _velocity;
	Vector3 _dimensions;
	Vector3 _rotation;
public:
	Transform();
	Transform(const Vector3& pos, const Vector3& vel, const Vector3& dim, const Vector3& rotation);
	virtual ~Transform();

	virtual void init();
	virtual void load(const nlohmann::json& params);
	virtual void update();

	// position
	const Vector3& getPos();
	const Vector3& getPos() const;
	void setPos(const Vector3& pos);
	void setPosX(double x);
	void setPosY(double y);
	void setPosZ(double z);

	// rotation
	const Vector3& getRot();
	const Vector3& getRot() const;
	void setRot(Vector3 angle);
	void setRotX(double x);
	void setRotY(double y);
	void setRotZ(double z);

	// velocity
	const Vector3& getVel();
	const Vector3& getVel() const;
	void setVel(const Vector3& vel);
	void setVelX(double x);
	void setVelY(double y);
	void setVelZ(double z);

	//Dimensions
	const Vector3& getDimensions();
	const Vector3& getDimensions() const;
	void setDimensions(const Vector3 dim);
	void setDimX(double x);
	void setDimY(double y);
	void setDimZ(double z);
};

#endif