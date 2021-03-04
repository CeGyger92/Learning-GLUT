//--------------------------------------------------------------------------
// Developer -- Eddie Gyger
// Course ----- CS3233
// Project ---- The Great Pyramids of OpenGL
// Due date --- Nov. 18 2020
// 
// Create a lighted scene that depicts the Great Pyramids in OpenGL
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
	w[0] = ((u[1] * v[2]) - (u[2] * v[1])); //WOW! The error here in the last assignment was
	w[1] = ((u[2] * v[0]) - (u[0] * v[2]));//because I was using indexes 1,2,3 in a zero indexed world,
	w[2] = ((u[0] * v[1]) - (u[1] * v[0]));//I'm not sure why the complier didnt throw an out of bounds error.
	//set normal vector
	glNormal3fv(w);
}

//Build Pyramid
void buildPyramid(float scale, float posX, float posZ) {
	float pyramidBaseVertices [][3] = {
		{-1,0,1}, {-1,0,-1}, {1,0,-1}, {1,0,1} 
	};
	float pyramidTip [] = { 0, (2.0 * .636), 0 }; //.636 is the base length to height ratio of the Great Pyramid of Giza
	glPushMatrix();

	glTranslated(posX, 0.0, posZ);
	glScaled(scale, scale, scale); //uniform scaling

	for (int i = 0; i < 4; i++)
	{
		glBegin(GL_TRIANGLES);
		if (i < 3) {
			setNormal(pyramidBaseVertices[i+1], pyramidTip, pyramidBaseVertices[i]);
			glVertex3fv(pyramidBaseVertices[i]);
			glVertex3fv(pyramidTip);
			glVertex3fv(pyramidBaseVertices[i+1]);
		}
		else {
			setNormal(pyramidBaseVertices[0], pyramidTip, pyramidBaseVertices[i]);
			glVertex3fv(pyramidBaseVertices[i]);
			glVertex3fv(pyramidTip);
			glVertex3fv(pyramidBaseVertices[0]);
		}
		glEnd();
	}

	//***OPTIONAL BASE FOR STAND ALONE PYRAMIDS***

	/*glBegin(GL_QUADS);
	setNormal(pyramidBaseVertices[2], pyramidBaseVertices[1], pyramidBaseVertices[0]);//bottom reflective
	glVertex3fv(pyramidBaseVertices[0]);
	glVertex3fv(pyramidBaseVertices[1]);
	glVertex3fv(pyramidBaseVertices[2]);
	glVertex3fv(pyramidBaseVertices[3]);
	glEnd();*/

	glPopMatrix();
}

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	cameraSetLimits(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);
	cameraApply();

	float face_color[] = { 0.76f, 0.698f, 0.5f, 1.0f };   // Sand!
	float grey[] = { 0.1f, 0.1f, 0.1f, 1.0f };   // grey
	glMaterialfv(GL_FRONT, GL_DIFFUSE, face_color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grey); //dull the specular so not to turn faces completely white.
	glMaterialfv(GL_FRONT, GL_AMBIENT, face_color);
	glMaterialf(GL_FRONT, GL_SHININESS, 20.0F);

	//The Ground
	float ground[][3] = {
		{-10,0,10}, {-10,0,-10}, {10,0,-10}, {10,0,10}
	};
	glBegin(GL_QUADS);
	setNormal(ground[0], ground[1], ground[2]);//Purposefully only lighting top layer
	glVertex3fv(ground[0]);
	glVertex3fv(ground[1]);
	glVertex3fv(ground[2]);
	glVertex3fv(ground[3]);
	glEnd();

	//Place Pyramids
	buildPyramid(2, 5, -7);
	buildPyramid(1.75, -1, -1);
	buildPyramid(1, -5, 4);
	buildPyramid(.5, -4, 7);
	buildPyramid(.5, -5.5, 7);
	buildPyramid(.5, -7, 7);

	glFlush();  // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("The Great Pyramids of OpenGL");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
