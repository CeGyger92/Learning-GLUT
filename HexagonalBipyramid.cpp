//--------------------------------------------------------------------------
// Developer -- Eddie Gyger
// Course ----- CS3233
// Project ---- Lighted Hexagonal Bipyramid
// Due date --- Nov. 9 2020
// 
// Create a lighted hexangonal bipyramid through through the use of normal 
// vectors and Eck's camera API.
//--------------------------------------------------------------------------

#ifdef _WIN32
#include <GL/glut.h>
#elif __linux__
#include <GL/glut.h>
#elif __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#endif

#include <cmath>
#include <cstdio>
#include "camera.h"

void init()
{
	glEnable(GL_LIGHTING);    // Enable lighting.
	glEnable(GL_LIGHT0);      // Turn on a light. Use default light attributes.
	glEnable(GL_NORMALIZE);   // OpenGL will make all normal vectors into unit normals
	glutMouseFunc(trackballMouseFunction);//Register camera function with GLUT
	glutMotionFunc(trackballMotionFunction);
	return;
}

//Calculate Normal Vectors
void setNormal(float * a, float * o, float *b) {
	float w[3] = { 0,0,0 };
	float u[3] = { 0,0,0 };
	float v[3] = { 0,0,0 };

	//translate to origin
	for (int i = 0; i < 3; i++)
	{
		u[i] = a[i] - o[i];
		v[i] = b[i] - o[i];
	}
	//cross product
	w[0] = ((u[1] * v[2]) - (u[2] * v[1])); //Wow the error here in the last assignment was
	w[1] = ((u[2] * v[0]) - (u[0] * v[2]));//because I was using indexes 1,2,3 in a zero index world,
	w[2] = ((u[0] * v[1]) - (u[1] * v[0]));//I'm not sure why the complier didnt throw an out of bounds error
	//set normal vector
	glNormal3fv(w);
}

const double PI = 3.141592653589793;
float hexagonX[6];
float hexagonZ[6];

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	cameraSetLimits(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
	cameraApply();

	//Use trig to save coordinates of hexagon
	int i = 0;
	for (GLint degrees = 0; degrees <= 300; degrees += 60) {
		GLfloat radians;
		radians = degrees * PI / 180;
		hexagonX[i] = cos(radians);
		hexagonZ[i] = sin(radians);
		i++;
	}
	float face_color[] = { 0.77f, 0.70f, 0.35f, 1.0f };   // Gold!
	glMaterialfv(GL_FRONT, GL_DIFFUSE, face_color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, face_color);
	glMaterialfv(GL_FRONT, GL_AMBIENT, face_color);
	glMaterialf(GL_FRONT, GL_SHININESS, 75.0F);

	//Create Bottom Faces
	for (int i = 0; i < 6; i++) {
		float currentFace[3][3];
		glBegin(GL_TRIANGLES);
		currentFace[0][0] = hexagonX[i];
		currentFace[0][1] = 0.0f;
		currentFace[0][2] = hexagonZ[i];
		if (i < 5) {
			currentFace[1][0] = hexagonX[i + 1];
			currentFace[1][1] = 0.0f;
			currentFace[1][2] = hexagonZ[i + 1];
		}
		else {
			currentFace[1][0] = hexagonX[0];
			currentFace[1][1] = 0.0f;
			currentFace[1][2] = hexagonZ[0];
		}
		currentFace[2][0] = 0.0f;
		currentFace[2][1] = -1.5f;
		currentFace[2][2] = 0.0f;
		setNormal(currentFace[2], currentFace[1], currentFace[0]);
		glVertex3fv(currentFace[2]);
		glVertex3fv(currentFace[1]);
		glVertex3fv(currentFace[0]);
		glEnd();
	}

	//Create Top Faces
	for (int i = 0; i < 6; i++) {
		float currentFace[3][3];
		glBegin(GL_TRIANGLES);
		currentFace[0][0] = hexagonX[i];
		currentFace[0][1] = 0.0f;
		currentFace[0][2] = hexagonZ[i];
		if (i < 5) {
			currentFace[1][0] = hexagonX[i + 1];
			currentFace[1][1] = 0.0f;
			currentFace[1][2] = hexagonZ[i + 1];
		}
		else {
			currentFace[1][0] = hexagonX[0];
			currentFace[1][1] = 0.0f;
			currentFace[1][2] = hexagonZ[0];
		}
		currentFace[2][0] = 0.0f;
		currentFace[2][1] = 1.5f;
		currentFace[2][2] = 0.0f;
		setNormal(currentFace[0], currentFace[1], currentFace[2]);
		glVertex3fv(currentFace[2]);
		glVertex3fv(currentFace[1]);
		glVertex3fv(currentFace[0]);
		glEnd();
	}

	glFlush();  // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Hexagonal Bipyramid");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
