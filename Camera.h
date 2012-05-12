#include "vecmath.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Camera {
private:
	Vector3 rightVector;	
	Vector3 upVector;

	float rotatedX, rotatedY, rotatedZ;	
	
public:
	Camera();
	
	Vector3 viewDir;
	Vector3 position;
	
	void render();

	void move(Vector3 direction);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);

	void moveForward(float distance);
	void moveUpward(float distance);
	void strafeRight(float distance);
};