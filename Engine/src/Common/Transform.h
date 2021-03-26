
#include "Vector3.h"
#include "Component.h"

class Transform : public Component {
private:
	Vector3 position;
	Vector3 velocity;
	Vector3 dimensions;
	double rotation;
public:
	Transform(Vector3 pos, Vector3 vel, Vector3 dim,double rotation);
	Transform();
	virtual ~Transform();

	// position
	const Vector3& getPos() const {
		return position;
	}
	void setPos(const Vector3& pos) {
		position.set(pos);
	}

	void setPosX(double x) {
		position.setX(x);
	}
	void setPosY(double y) {
		position.setY(y);
	}
	void setPosZ(double z) {
		position.setZ(z);
	}

	// rotation
	double getRot() const {
		return rotation;
	}
	void setRot(double angle) {
		rotation = angle;
	}

	// velocity
	const Vector3& getVel() const {
		return velocity;
	}
	void setVel(const Vector3& vel) {
		velocity.set(vel);
	}
	
	void setVelX(double x) {
		velocity.setX(x);
	}
	void setVelY(double y) {
		velocity.setY(y);
	}
	void setVelZ(double z) {
		velocity.setZ(z);
	}

	Vector3 getDimensieons() {
		return dimensions;
	}

	void setDimensions(const Vector3 dim) {
		dimensions.set(dim);
	}
	void setDimX(double x) {
		dimensions.setX(x);
	}
	void setDimY(double y) {
		dimensions.setY(y);
	}
	void setDimZ(double z) {
		dimensions.setZ(z);
	}




};
