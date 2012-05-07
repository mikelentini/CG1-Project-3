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

void keyboard( unsigned char key, int x, int y ) {
	switch (key) {
		case 27:
			exit(0);
			break;
	}
}

/*
 * Called when the mouse button is pressed.
 */
void mouse( int button, int state, int x, int y ) {
    
}


/*
 * Called when mouse is moved with button pressed.
 */
void motion( int x, int y ) {
    
}

void display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glBegin(GL_TRIANGLES);
		glVertex2f(1, 1);
		glVertex2f(0.5f, 0);
		glVertex2f(0, 0.5f);
	glEnd();
}

void init() {
	glEnable(GL_DEPTH_TEST);
}

int main( int argc, char** argv ) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowPosition(50, 50);
   glutInitWindowSize(512, 512);
   glutCreateWindow("CG1 Project 3 (Mike Lentini)");

   // Callback functions
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutMotionFunc(motion);
   glutMouseFunc(mouse);

   // Initializations
   init();

   glutMainLoop();

   return 0;
}