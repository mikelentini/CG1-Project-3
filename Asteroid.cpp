#include "Asteroid.h"

Asteroid::Asteroid(bool isSmall) {
	int min = -1;
	int max = 1;
	
	int xDir = min + (rand() % (int)(max - min + 1));
	int yDir = min + (rand() % (int)(max - min + 1));
	int zDir = min + (rand() % (int)(max - min + 1));
	
	// just in case
	if (xDir == 0 && yDir == 0 && zDir == 0) {
		xDir = 1;
	}
	
	int xDecider = min + (rand() % (int)(max - min + 1));
	
	min = -10;
	max = 10;
	
	int y = min + (rand() % (int)(max - min + 1));
	int z = min + (rand() % (int)(max - min + 1));
	
	if (xDecider > 0) {
		this->position = Vector3(10, y, z);
	} else {
		this->position = Vector3(-10, y, z);
	}
	
	this->direction = Vector3(xDir, yDir, zDir);
	this->isSmall = isSmall;
	this->rotate = 0;
}