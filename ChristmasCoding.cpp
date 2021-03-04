//--------------------------------------------------------------------------
// Developer -- Eddie Gyger
// Course ----- CS3233
// Project ---- A Scene Of Your Own
// Due date --- Dec.7 2020
// 
// Create a still life with proper lighting and a surprise!
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
#include <iostream>

bool pcOn = false;
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
	w[0] = ((u[1] * v[2]) - (u[2] * v[1]));
	w[1] = ((u[2] * v[0]) - (u[0] * v[2]));
	w[2] = ((u[0] * v[1]) - (u[1] * v[0]));
	//set normal vector
	glNormal3fv(w);
	std::cout << w[0] << " " << w[1] << " " << w[2] << std::endl;
}

void setColor(float r, float g, float b, float a, float shine) {
	float face_color[] = { r, g, b, a };
	float grey[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, face_color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grey);
	glMaterialfv(GL_FRONT, GL_AMBIENT, face_color);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
 }

void turnOn(int x) {
	pcOn = true;
	glutPostRedisplay();
}

void drawBox(float top[4][3], float bottom [4][3]) {

	glBegin(GL_QUADS);//Top Face
	setNormal(top[0], top[1], top[2]);
	glVertex3fv(top[0]);
	glVertex3fv(top[1]);
	glVertex3fv(top[2]);
	glVertex3fv(top[3]);
	glEnd();

	glBegin(GL_QUADS);//Sides
	setNormal(top[1], top[0], bottom[0]);
	glVertex3fv(top[0]);
	glVertex3fv(top[1]);
	glVertex3fv(bottom[1]);
	glVertex3fv(bottom[0]);
	glEnd();

	glBegin(GL_QUADS);
	setNormal(top[2], top[1], bottom[1]);
	glVertex3fv(top[1]);
	glVertex3fv(top[2]);
	glVertex3fv(bottom[2]);
	glVertex3fv(bottom[1]);
	glEnd();

	glBegin(GL_QUADS);
	setNormal(top[3], top[2], bottom[2]);
	glVertex3fv(top[2]);
	glVertex3fv(top[3]);
	glVertex3fv(bottom[3]);
	glVertex3fv(bottom[2]);
	glEnd();

	glBegin(GL_QUADS);
	setNormal(top[0], top[3], bottom[3]);
	glVertex3fv(top[3]);
	glVertex3fv(top[0]);
	glVertex3fv(bottom[0]);
	glVertex3fv(bottom[3]);
	glEnd();

	glBegin(GL_QUADS);//Bottom Face
	setNormal(bottom[2], bottom[1], bottom[0]);
	glVertex3fv(bottom[0]);
	glVertex3fv(bottom[1]);
	glVertex3fv(bottom[2]);
	glVertex3fv(bottom[3]);
	glEnd();

}

//Build Desk
void buildDesk(float scale, float posX, float posY, float posZ) {
	
	glPushMatrix();

	glTranslated(posX, posY, posZ);
	glScaled(scale, scale, scale); //uniform scaling

	//TableTop
	float tableTop[][3] = {
		{-5,0,2.5}, {-5,0,-2.5}, {5,0,-2.5}, {5,0,2.5}
	};
	float tableUnder[][3] = {
		{-5,-.5,2.5}, {-5,-.5,-2.5}, {5,-.5,-2.5}, {5,-.5,2.5}
	};
	drawBox(tableTop, tableUnder);

	//Legs
	for (int i = 0; i < 4; i++) {
		if (i == 1) {
			glTranslated(0.0, 0.0, .5);
		}
		else if (i == 3) {
			glTranslated(0.0, 0.0, -0.5);
		}
		else if (i == 2) {
			glTranslated(-0.5, 0.0, 0.0);
		}
		float legTop[][3] = {
			{tableUnder[i][0], tableUnder[i][1], tableUnder[i][2] },
			{tableUnder[i][0], tableUnder[i][1], tableUnder[i][2] - .5 },
			{tableUnder[i][0] + .5, tableUnder[i][1], tableUnder[i][2] - .5 },
			{tableUnder[i][0] + .5, tableUnder[i][1], tableUnder[i][2]}
		};
		float legBottom[][3] = {
			{tableUnder[i][0], tableUnder[i][1] - 5, tableUnder[i][2] },
			{tableUnder[i][0], tableUnder[i][1] - 5, tableUnder[i][2] - .5 },
			{tableUnder[i][0] + .5, tableUnder[i][1] - 5, tableUnder[i][2] - .5 },
			{tableUnder[i][0] + .5, tableUnder[i][1] - 5, tableUnder[i][2]}
		};
		drawBox(legTop, legBottom);
	}

	glPopMatrix();
}

//Build Chair
void buildChair(float scale, float posX, float posY, float posZ) {

	glPushMatrix();

	glTranslated(posX, posY, posZ);
	glScaled(scale, scale, scale); //uniform scaling

	//Seat
	float seatTop[][3] = {
		{-1,0,1}, {-1,0,-1}, {1,0,-1}, {1,0,1}
	};
	float seatBottom[][3] = {
		{-1,-.25,1}, {-1,-.25,-1}, {1,-.25,-1}, {1,-.25,1}
	};
	drawBox(seatTop, seatBottom);

	//Back
	float backTop[][3] = {
		{-1,2,1}, {-1,2,.75}, {1,2,.75}, {1,2,1}
	};
	float backBottom[][3] = {
		{-1,0,1}, {-1,0,.75}, {1,0,.75}, {1,0,1}
	};
	drawBox(backTop, backBottom);

	//Legs
	for (int i = 0; i < 4; i++) {
		if (i == 1) {
			glTranslated(0.0, 0.0, .25);
		}
		else if (i == 3) {
			glTranslated(0.0, 0.0, -0.25);
		}
		else if (i == 2) {
			glTranslated(-0.25, 0.0, 0.0);
		}
		float legTop[][3] = {
			{seatBottom[i][0], seatBottom[i][1], seatBottom[i][2] },
			{seatBottom[i][0], seatBottom[i][1], seatBottom[i][2] - .25 },
			{seatBottom[i][0] + .25, seatBottom[i][1], seatBottom[i][2] - .25 },
			{seatBottom[i][0] + .25, seatBottom[i][1], seatBottom[i][2]}
		};
		float legBottom[][3] = {
			{seatBottom[i][0], seatBottom[i][1] - 2, seatBottom[i][2] },
			{seatBottom[i][0], seatBottom[i][1] - 2, seatBottom[i][2] - .25 },
			{seatBottom[i][0] + .25, seatBottom[i][1] - 2, seatBottom[i][2] - .25 },
			{seatBottom[i][0] + .25, seatBottom[i][1] - 2, seatBottom[i][2]}
		};
		drawBox(legTop, legBottom);
	}

	glPopMatrix();
}

//Build PC
void buildPC(float scale, float posX, float posY, float posZ) {

	glPushMatrix();

	glTranslated(posX, posY, posZ);
	glScaled(scale, scale, scale); //uniform scaling

	//Base
	float baseTop[][3] = {
		{-1,.1,.5}, {-1,.1,-.5}, {1,.1,-.5}, {1,.1,.5}
	};
	float baseBottom[][3] = {
		{-1,0,.5}, {-1,0,-.5}, {1,0,-.5}, {1,0,.5}
	};
	drawBox(baseTop, baseBottom);

	//Neck
	float neckTop[][3] = {
		{-.25,2,.25}, {-.25,2,-.25}, {.25,2,-.25}, {.25,2,.25}
	};
	float neckBottom[][3] = {
		{-.25,.1,.25}, {-.25,.1,-.25}, {.25,.1,-.25}, {.25,.1,.25}
	};
	drawBox(neckTop, neckBottom);

	//Monitor
	float monitorTop[][3] = {
		{-2,3,.5}, {-2,3,.25}, {2,3,.25}, {2,3,.5}
	};
	float monitorBottom[][3] = {
		{-2,1,.5}, {-2,1,.25}, {2,1,.25}, {2,1,.5}
	};
	drawBox(monitorTop, monitorBottom);

	if (pcOn) {
		setColor(0, 0, 1, 1, 128); //blue
	}
	else {
		setColor(0, 0, 0, 1, 128); //black
	}

	//Screen
	float screen[][3] = {
		{-1.8,1.2,.51}, {-1.8,2.8,.51}, {1.8,2.8,.51}, {1.8,1.2,.51}
	};
	glBegin(GL_QUADS);
	setNormal(screen[0], screen[1], screen[2]);
	glVertex3fv(screen[0]);
	glVertex3fv(screen[1]);
	glVertex3fv(screen[2]);
	glVertex3fv(screen[3]);
	glEnd();

	glPopMatrix();
}

//Build Keyboard
void buildKeyboard(float scale, float posX, float posY, float posZ) {

	glPushMatrix();

	glTranslated(posX, posY, posZ);
	glScaled(scale, scale, scale); //uniform scaling

	//board
	float boardTop[][3] = {
		{-1.5,.1,.5}, {-1.5,.1,-.5}, {1.5,.1,-.5}, {1.5,.1,.5}
	};
	float boardBottom[][3] = {
		{-1.5,0,.5}, {-1.5,0,-.5}, {1.5,0,-.5}, {1.5,0,.5}
	};
	drawBox(boardTop, boardBottom);

	glPopMatrix();
}

//Build Mouse
void buildMouse(float scale, float posX, float posY, float posZ) {

	glPushMatrix();

	glTranslated(posX, posY, posZ);
	glScaled(scale, scale, scale); 

	//mouse
	float mouseTop[][3] = {
		{-.25,.15,.4}, {-.25,.15,-.4}, {.25,.15,-.4}, {.25,.15,.4}
	};
	float mouseBottom[][3] = {
		{-.25,0,.4}, {-.25,0,-.4}, {.25,0,-.4}, {.25,0,.4}
	};
	drawBox(mouseTop, mouseBottom);

	glPopMatrix();
}

void buildCup(float scale, float posX, float posY, float posZ) {

	glPushMatrix();

	glTranslated(posX, posY, posZ);
	glScaled(scale, scale, scale); 

	//cup
	float cupTop[][3] = {
		{-.25,.6,.25}, {-.25,.6,-.25}, {.25,.6,-.25}, {.25,.6,.25}
	};
	float cupBottom[][3] = {
		{-.25,0,.25}, {-.25,0,-.25}, {.25,0,-.25}, {.25,0,.25}
	};
	drawBox(cupTop, cupBottom);

	//handleConnection
	float connectTop[][3] = {
		{.45,.4,.1}, {.45,.4,-.1}, {.55,.4,-.1}, {.55,.4,.1}
	};
	float connectBottom[][3] = {
		{.45,.2,.1}, {.45,.2,-.1}, {.55,.2,-.1}, {.55,.2,.1}
	};
	drawBox(connectTop, connectBottom);

	//handle
	for (int i = 0; i < 2; i++) {
		if (i > 0) {
			glTranslated(0, -.3, 0);
		}
		float handleTop[][3] = {
			{.25,.5,.1}, {.25,.5,-.1}, {.55,.5,-.1}, {.55,.5,.1}
		};
		float handleBottom[][3] = {
			{.25,.4,.1}, {.25,.4,-.1}, {.55,.4,-.1}, {.55,.4,.1}
		};
		drawBox(handleTop, handleBottom);
	}

	glPopMatrix();
}

//Build Christmas Tree
void buildChristmasTree(float scale, float posX, float posY, float posZ) {
	float pyramidBaseVertices[][3] = {
		{-2,-3,2}, {-2,-3,-2}, {2,-3,-2}, {2,-3,2}
	};
	float pyramidTip[] = { 0, 7, 0 };
	glPushMatrix();

	glTranslated(posX, posY, posZ);
	glScaled(scale, scale, scale); 

	for (int i = 0; i < 4; i++)
	{
		glBegin(GL_TRIANGLES);
		if (i < 3) {
			setNormal(pyramidBaseVertices[i + 1], pyramidTip, pyramidBaseVertices[i]);
			glVertex3fv(pyramidBaseVertices[i]);
			glVertex3fv(pyramidTip);
			glVertex3fv(pyramidBaseVertices[i + 1]);
		}
		else {
			setNormal(pyramidBaseVertices[0], pyramidTip, pyramidBaseVertices[i]);
			glVertex3fv(pyramidBaseVertices[i]);
			glVertex3fv(pyramidTip);
			glVertex3fv(pyramidBaseVertices[0]);
		}
		glEnd();
	}

	glBegin(GL_QUADS);
	setNormal(pyramidBaseVertices[2], pyramidBaseVertices[1], pyramidBaseVertices[0]);//bottom reflective
	glVertex3fv(pyramidBaseVertices[0]);
	glVertex3fv(pyramidBaseVertices[1]);
	glVertex3fv(pyramidBaseVertices[2]);
	glVertex3fv(pyramidBaseVertices[3]);
	glEnd();

	//trunk
	setColor(.396, .263, .129, 1, 20);
	float trunkTop[][3] = {
		{-.5,-3,.5}, {-.5,-3,-.5}, {.5,-3,-.5}, {.5,-3,.5}
	};
	float trunkBottom[][3] = {
		{-.5,-5.5,.5}, {-.5,-5.5,-.5}, {.5,-5.5,-.5}, {.5,-5.5,.5}
	};
	drawBox(trunkTop, trunkBottom);

	glPopMatrix();
}

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	cameraSetLimits(-12.0f, 12.0f, -12.0f, 12.0f, -12.0f, 12.0f);
	cameraApply();
	glRotatef(15, 1, 1, 0);//Rotate for good initial view of screen

	setColor(.2695, .1914, .1367, 1, 20);//Wood
	buildDesk(1, 0, 0, 0);
	
	setColor(.15, .15, .15, 1, 20);//Grey
	buildChair(1.5, 0, -2, 4);

	setColor(1, 1, 1, 1, 20);//White
	buildPC(1, 0, 0, 0);

	setColor(1, 1, 1, 1, 20);//White
	buildKeyboard(1, 0, 0, 1.5);

	setColor(1, 1, 1, 1, 20);//White
	buildMouse(1, 2, 0, 1.5);

	setColor(1, 0, 0, 1, 20);//Red
	buildCup(1, 3, 0, -.1);

	setColor(0, 1, 0, 1, 10);//Green
	buildChristmasTree(1, -5, 0, -6);

	float p1[][3] = {
		{7.0f, 8.0f, 9.0f}, {1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}
	};
	setNormal(p1[0], p1[1], p1[2]);

	glFlush();  // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Christmas Morning Boot Up");
	glutDisplayFunc(display);
	init();
	glutTimerFunc(3000, turnOn, 0);
	glutMainLoop();
	return 0;
}
