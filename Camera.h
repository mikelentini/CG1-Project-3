#include "vecmath.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Camera {
private:
	Vector3 viewDir;
	Vector3 rightVector;	
	Vector3 upVector;
	Vector3 position;

	float rotatedX, rotatedY, rotatedZ;	
	
public:
	Camera();				//inits the values (Position: (0|0|0) Target: (0|0|-1) )
	void render();	//executes some glRotates and a glTranslate command
							//Note: You should call glLoadIdentity before using Render

	void move(Vector3 direction);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);

	void moveForward(float distance);
	void moveUpward(float distance);
	void strafeRight(float distance);
};