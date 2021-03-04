//--------------------------------------------------------------------------
// Eddie Gyger
// Computer Graphics
// My House - 10/5/2020
// 
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
const double PI = 3.141592653589793;
GLuint drawSun;

// Set up a display list for drawing the Sun.
void init()
{
	drawSun = glGenLists(1);
	glNewList(drawSun, GL_COMPILE);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 0.0f);
	for (GLint degrees = 0; degrees <= 350; degrees += 10)
	{
		GLdouble radians, x, y;
		radians = degrees * PI / 180;
		x = cos(radians);
		y = sin(radians);
		glVertex2f(x-10, y+4.5f); //Translate
	}
	glEnd();
	glEndList();
}

void display() {
	glClearColor(.683f, .783f, .96f, 1.0f);//Sky
	glClear(GL_COLOR_BUFFER_BIT);

	// Enabling blending makes it possible to use the alpha component of the
	// color to control opacity.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// These functions set the world coordinate system that will be used
	// for drawing the figures in the code that follows.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-25.0f, 25.0f, -12.0f, 12.0f); //Arguments: xmin, xmax, ymin, ymax

	// Grass
	glBegin(GL_QUADS);
	glColor3f(.25f, .535f, .065f);
	glVertex2f(-25.0f, -6.0f);
	glVertex2f(25.0f, -6.0f);
	glVertex2f(25.0f, -12.0f);
	glVertex2f(-25.0f, -12.0f);


	//House Body
	glColor3f(.8f, .216f, .1f);
	glVertex2f(-10.0f, -5.0f);
	glVertex2f(10.0f, -5.0f);
	glVertex2f(10.0f, -10.0f);
	glVertex2f(-10.0f, -10.0f);

	//Overhang
	glColor3f(.303f, .107f, .061f);
	glVertex2f(-12.0f, -5.0f);
	glVertex2f(12.0f, -5.0f);
	glVertex2f(13.0f, -4.5f);
	glVertex2f(-13.0f, -4.5f);

	//Roof
	glColor3f(.4f, .145f, .086f);
	glVertex2f(-8.0f, 0.0f);
	glVertex2f(8.0f, 0.0f);
	glVertex2f(13.0f, -4.5f);
	glVertex2f(-13.0f, -4.5f);

	//Door
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-2.0f, -6.0f);
	glVertex2f(2.0f, -6.0f);
	glVertex2f(2.0f, -9.0f);
	glVertex2f(-2.0f, -9.0f);

	//DoorKnob
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(1.25f, -7.25f);
	glVertex2f(1.75f, -7.25f);
	glVertex2f(1.75f, -7.75f);
	glVertex2f(1.25f, -7.75f);

	//Window Left
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-8.0f, -6.0f);
	glVertex2f(-4.0f, -6.0f);
	glVertex2f(-4.0f, -8.0f);
	glVertex2f(-8.0f, -8.0f);

	//Window Right
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(8.0f, -6.0f);
	glVertex2f(4.0f, -6.0f);
	glVertex2f(4.0f, -8.0f);
	glVertex2f(8.0f, -8.0f);
	glEnd();

	//Window Lines
	glBegin(GL_LINES); 
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(6.0f, -6.0f);
	glVertex2f(6.0f, -8.0f);
	glVertex2f(4.0f, -7.0f);
	glVertex2f(8.0f, -7.0f);
	glVertex2f(-6.0f, -6.0f);
	glVertex2f(-6.0f, -8.0f);
	glVertex2f(-4.0f, -7.0f);
	glVertex2f(-8.0f, -7.0f);
	glEnd();

	//Step 1
	glBegin(GL_QUADS); 
	glColor3f(.33f, .32f, 0.32f);
	glVertex2f(-2.5f, -9.0f);
	glVertex2f(2.5f, -9.0f);
	glVertex2f(2.5f, -9.5f);
	glVertex2f(-2.5f, -9.5f);

	 //Step 2
	glColor3f(.33f, .32f, 0.32f);
	glVertex2f(-3.0f, -9.5f);
	glVertex2f(3.0f, -9.5f);
	glVertex2f(3.0f, -10.0f);
	glVertex2f(-3.0f, -10.0f);
	glEnd();

	//Step Line
	glBegin(GL_LINES); 
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(2.5f, -9.5f);
	glVertex2f(-2.5f, -9.5f);
	glEnd();

	//Berry Bush
	glBegin(GL_TRIANGLE_FAN); 
	glColor4f(0.04f, 0.9f, 0.04f, 0.6f); // SOMETHING A LITTLE TRANSPARENT
	glVertex2f(11.5f, -8.875f);
	glVertex2f(10.375f, -7.750f);
	glVertex2f(12.625f, -7.750f);
	glVertex2f(13.750f, -8.875f);
	glVertex2f(12.625f, -10.0f);
	glVertex2f(10.375f, -10.0f);
	glVertex2f(9.250f, -8.875f);
	glVertex2f(10.375f, -7.750f);
	glEnd();

	//Berries
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 1.0f); //SOMETHING PURPLE
	glVertex2f(11.35f, -9.3f);
	glVertex2f(11.65f, -9.3f);
	glVertex2f(11.65f, -9.4f);
	glVertex2f(11.35f, -9.4f);

	glVertex2f(10.55f, -8.5f);
	glVertex2f(10.85f, -8.5f);
	glVertex2f(10.85f, -8.6f);
	glVertex2f(10.55f, -8.6f);
	
	glVertex2f(12.15f, -8.5f);
	glVertex2f(12.45f, -8.5f);
	glVertex2f(12.45f, -8.6f);
	glVertex2f(12.15f, -8.6f);
	glEnd();

	//Sun
	glScalef(2.0f, 2.0f, 1.0f);
	glCallList(drawSun);

	glFlush();  // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitWindowSize(1000, 500);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow("My House"); // Create a window with the given title
	glutDisplayFunc(display); // Register display callback handler for window re-paint
	init();
	glutMainLoop();           // Enter the infinitely event-processing loop
	return 0;
}


