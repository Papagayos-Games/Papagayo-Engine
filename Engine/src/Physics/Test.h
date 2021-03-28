#pragma once
#include "btBulletCollisionCommon.h"

#include <iostream>
using namespace std;
class Test
{
public:
	Test() {
		vec3 = btVector3(2, 1, 2);

		cout << "X: " << vec3.x() << " Y: " << vec3.y() << " Z: " << vec3.z() << "\n";
	}

private:
	btVector3 vec3;
};

