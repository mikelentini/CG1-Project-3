/*
* project3.cpp
* CG1 Project 3
*
* Author: Mike Lentini <mjl1445@rit.edu>
* Created: May 7, 2012
*/

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Camera.h"

Camera camera;
bool fillShapes = false;

float lastX = 0;
float lastY = 0;

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		// escape key
		case 27:
			exit(0);
			break;
		// 'q' key
		case 113:
			exit(0);
			break;
		// 1 key
		case 49:
			fillShapes = false;
			break;
		// 2 key
		case 50:
			fillShapes = true;
			break;
		// space key
		case 32:
			camera.moveUpward(0.1);
			break;
		// 'z' key
		case 122:
			camera.moveUpward(-0.1);
			break;
		// 'w' key
		case 119:
			camera.moveForward(-0.1);
			break;
		// 'a' key
		case 97:
			camera.strafeRight(-0.1);
			break;
		// 's' key
		case 115:
			camera.moveForward(0.1);
			break;
		// 'd' key
		case 100:
			camera.strafeRight(0.1);
			break;
		// 'r' key
		case 114:
			
			break;
	}
}

/*
 * Called when the mouse button is pressed.
 */
void mouse(int button, int state, int x, int y) {
	
}


/*
 * Called when mouse is moved with button pressed.
 */
void motion(int x, int y) {

}

/*
 * Called when mouse moves without button pressed.
 */
void passiveMotion(int x, int y) {
	y = glutGet(GLUT_WINDOW_HEIGHT) - y;
	
	if (x > lastX) {
		camera.rotateY(-1.0);
	} else if (x < lastX) {
		camera.rotateY(1.0);
	}
	
	if (y > lastY) {
		camera.rotateX(1.0);
	} else if (y < lastY) {
		camera.rotateX(-1.0);
	}
	
	lastX = x;
	lastY = y;
}

void drawScene() {
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	
	glColor3f(1, 1, 1);
	
	GLUquadric *quadric = gluNewQuadric();
	GLUquadric *quadric2 = gluNewQuadric();
	
	if (!fillShapes) {
		gluQuadricDrawStyle(quadric, GLU_LINE);
		gluQuadricDrawStyle(quadric2, GLU_LINE);
	} else {
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricDrawStyle(quadric2, GLU_FILL);
	}
	
	glPushMatrix();
		glTranslatef(-0.5f, 0, -2);
	
		gluSphere(quadric, 0.25f, 10, 10);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.5f, 0, -2);
		
		gluSphere(quadric2, 0.25f, 10, 10);
	glPopMatrix();
	
	gluDeleteQuadric(quadric);
	gluDeleteQuadric(quadric2);
	
	glutPostRedisplay();
}

void setMainViewport(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(60, w / h, 0.5f, 20);
	glMatrixMode(GL_MODELVIEW);
}

void setSecondaryViewport(int width, int height) {
	glScissor(width - 210, height - 210, 200, 200);
	
	glEnable(GL_SCISSOR_TEST);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glViewport(width - 210, height - 210, 200, 200);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(-10, 10, -10, 10, 0.5f, 20);
	glMatrixMode(GL_MODELVIEW);
	
	glDisable(GL_SCISSOR_TEST);
}

void display() {
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	setMainViewport(width, height);
	glPushMatrix();
		camera.render();
		drawScene();
	glPopMatrix();
	
	setSecondaryViewport(width, height);
	drawScene();
	
	glutSwapBuffers();
}

void initGL() {
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h) {
	
}

int main( int argc, char** argv ) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	
	glutReshapeFunc(reshape);
	
	glutCreateWindow("CG1 Project 3 (Mike Lentini)");
	glutFullScreen();
	
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMotionFunc(motion);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(passiveMotion);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	
	initGL();

	glutMainLoop();

	return 0;
}