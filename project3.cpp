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
#include "Bullet.h"
#include <list>

Camera camera;
bool fillShapes = false;
list<Asteroid> asteroids;
list<Bullet> bullets;

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
			camera.moveUp(0.2);
			break;
		// 'z' key
		case 122:
			camera.moveUp(-0.2);
			break;
		// 'w' key
		case 119:
			camera.moveForward(-0.2);
			break;
		// 'a' key
		case 97:
			camera.strafe(-0.2);
			break;
		// 's' key
		case 115:
			camera.moveForward(0.2);
			break;
		// 'd' key
		case 100:
			camera.strafe(0.2);
			break;
		// 'r' key
		case 114:
			camera = Camera();
			fillShapes = false;

			asteroids.clear();

			for (int i = 0; i < 49; i++) {
				asteroids.push_back(Asteroid(false));
			}

			bullets.clear();
			break;
	}
}

/*
 * Called when the mouse button is pressed.
 */
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		bullets.push_back(Bullet(camera.position,
								 Vector3(camera.viewDirection.x,
										 camera.viewDirection.y,
										 camera.viewDirection.z)
								));
	}
}

/*
 * Called when mouse moves without button pressed.
 */
void passiveMotion(int x, int y) {
	float rotateY = ((lastX - x) / glutGet(GLUT_WINDOW_WIDTH)) * 1000;
	camera.rotateY(rotateY);
	
	float rotateX = ((lastY - y) / glutGet(GLUT_WINDOW_HEIGHT)) * 1000;
	camera.rotateX(rotateX);
	
	lastX = x;
	lastY = y;
}

void drawScene() {
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	
	if (fillShapes) {
		glColor4ub(0, 0, 255, 125);
		glutSolidCube(20);
	} else {
		glColor4ub(0, 0, 255, 255);
		glutWireCube(20);
	}
	
	glColor3f(1, 1, 1);
	
	for (list<Asteroid>::iterator iter(asteroids.begin()); iter != asteroids.end(); iter++) {
		GLUquadric *asteroid = gluNewQuadric();

		if (!fillShapes) {
			gluQuadricDrawStyle(asteroid, GLU_LINE);
		} else {
			gluQuadricDrawStyle(asteroid, GLU_FILL);
		}

		glPushMatrix();
		glTranslatef(iter->position.x, iter->position.y, iter->position.z);
		glRotatef(iter->rotate, iter->position.x, iter->position.y, iter->position.z);

		if (iter->isSmall) {
			glScalef(0.5f, 0.5f, 0.5f);
		}

		gluSphere(asteroid, 0.25f, 10, 10);
		glPopMatrix();

		gluDeleteQuadric(asteroid);
	}
	
	glColor3f(1, 0, 0);
	
	for (list<Bullet>::iterator iter(bullets.begin()); iter != bullets.end(); ) {
		bool hitAsteroid = false;
		
		GLUquadric *bullet = gluNewQuadric();
		
		if (!fillShapes) {
			gluQuadricDrawStyle(bullet, GLU_LINE);
		} else {
			gluQuadricDrawStyle(bullet, GLU_FILL);
		}
		
		glPushMatrix();
			glTranslatef(iter->position.x, iter->position.y, iter->position.z);
			
			gluSphere(bullet, 0.05f, 10, 10);
		glPopMatrix();
		
		gluDeleteQuadric(bullet);
		
		for (list<Asteroid>::iterator asteroid(asteroids.begin()); asteroid != asteroids.end(); ) {
			if (iter->overlaps(asteroid->position.x, asteroid->position.y, asteroid->position.z, asteroid->isSmall)) {
				if (!asteroid->isSmall) {
					Asteroid new1(true);
					Asteroid new2(true);

					new1.position = asteroid->position;
					new2.position = new1.position;
					
					new2.direction = new1.direction * -1;

					asteroids.push_back(new1);
					asteroids.push_back(new2);
				}
				
				asteroid = asteroids.erase(asteroid);
				
				hitAsteroid = true;
			} else {
				asteroid++;
			}
		}
		
		if (hitAsteroid) {
			iter = bullets.erase(iter);
		} else {
			iter++;
		}
	}
	
	glutPostRedisplay();
}

void setMainViewport(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(60, w / h, 0.5f, 40);
	glMatrixMode(GL_MODELVIEW);
}

void setSecondaryViewport(int width, int height) {
	glScissor(width - 210, height - 210, 200, 200);
	
	glEnable(GL_SCISSOR_TEST);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glViewport(width - 210, height - 210, 200, 200);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(-10.1f, 10.1f, -10.1f, 10.1f, 0.5f, 25);
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void reshape(int w, int h) {
	
}

void idle() {
	
}

void animateTimer(int value) {
	for (list<Asteroid>::iterator iter(asteroids.begin()); iter != asteroids.end(); ) {
		if (iter->position.x > 10 || iter->position.x < -10 || 
			iter->position.y > 10 || iter->position.y < -10 || 
			iter->position.z > 10 || iter->position.z < -10) {
			iter = asteroids.erase(iter);
			
			asteroids.push_back(Asteroid(false));
		} else {
			iter->rotate += 1;
			
			if (iter->direction.x > 0) {
				iter->position.x += 0.01f;
			} else {
				iter->position.x -= 0.01f;
			}
			
			if (iter->direction.y > 0) {
				iter->position.y += 0.01f;
			} else {
				iter->position.y -= 0.01f;
			}
			
			if (iter->direction.z > 0) {
				iter->position.z += 0.01f;
			} else {
				iter->position.z -= 0.01f;
			}
			
			iter++;
		}
	}
	
	for (list<Bullet>::iterator iter(bullets.begin()); iter != bullets.end(); ) {
		if (iter->position.x > 10 || iter->position.x < -10 || 
			iter->position.y > 10 || iter->position.y < -10 || 
			iter->position.z > 10 || iter->position.z < -10) {
			iter = bullets.erase(iter);
		} else {
			iter->move();
			
			iter++;
		}
	}
	
	glutTimerFunc(10, animateTimer, 0);
}

int main( int argc, char** argv ) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	glutReshapeFunc(reshape);
	
	glutCreateWindow("CG1 Project 3 (Mike Lentini)");
	glutFullScreen();
	
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(passiveMotion);
	glutMotionFunc(passiveMotion);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	
	glutTimerFunc(10, animateTimer, 0);
	
	initGL();
	
	for (int i = 0; i < 49; i++) {
		asteroids.push_back(Asteroid(false));
	}

	glutMainLoop();

	return 0;
}
