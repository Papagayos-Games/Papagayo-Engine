
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
	const Vector3& getPos() const;
	void setPos(const Vector3& pos);
	void setPosX(double x);
	void setPosY(double y);
	void setPosZ(double z);

	// rotation
	double getRot() const;
	void setRot(double angle);

	// velocity
	const Vector3& getVel() const;
	void setVel(const Vector3& vel);
	void setVelX(double x);
	void setVelY(double y);
	void setVelZ(double z);

	//Dimensions
	Vector3 getDimensieons();
	void setDimensions(const Vector3 dim);
	void setDimX(double x);
	void setDimY(double y);
	void setDimZ(double z);




};
