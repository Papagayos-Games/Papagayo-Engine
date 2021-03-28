#include "Test.h"

Test::Test()
{

	vec3 = btVector3(2, 1, 2);

	cout << "X: " << vec3.x() << " Y: " << vec3.y() << " Z: " << vec3.z() << "\n";
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
}
