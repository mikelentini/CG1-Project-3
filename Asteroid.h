#include "vecmath.h"

class Asteroid {
public:
	Asteroid(bool isSmall);
	
	Vector3 position;
	Vector3 direction;
	
	float rotate;
	
	bool isSmall;
};