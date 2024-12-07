#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include "prefix_Entity.h"
#include "prefix_Player.h"
#include "prefix_Camera.h"
#include "prefix_Physics.h"
#include "prefix_L1.h"
#include "prefix_L2.h"
#include <ctime>
#include <glut.h>
#include <windows.h>

constexpr auto DEBOUNCE = 0.1;

typedef enum {
	LVL1 = 0,
	LVL2,
	END,
} State;


float elapsedTime = 0;
int WIDTH = 1280;
int HEIGHT = 720;
bool keys[256];
int mouse_x = 0;
int last_mouse_x = WIDTH/2;
float debounce_time = 0;
int cameraZoom = 0;
char title[] = "3D Model Loader Sample";
GLuint tex;
GLuint tex_wall;
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 300;
State state = LVL1;



Player p;
L1 l1;
L2 l2;
Physics physics;



void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void checkKeys();
void move(Vector v);
void LoadAssets();
void mouse(int x, int y);
void update(int value);
void myReshape(int w, int h);
void myDisplay(void);
void myMotion(int x, int y);

// Function to display the timer
void displayTimer(float time) {
	std::string timeStr = "Time: " + std::to_string(static_cast<int>(time)) + "s";
	glColor3f(1.0f, 1.0f, 1.0f); // Set text color to white

	// Set up an orthographic projection for 2D rendering
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Position the text in the top right corner
	glRasterPos2f(WIDTH - 100, HEIGHT - 30);

	for (char c : timeStr) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}

	// Restore the previous projection and modelview matrices
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void myDisplay(void)
{
	if (state == LVL1)
	{
		l1.Display(&p);
	}
	else if (state == LVL2)
	{
		l2.Display(&p);
	}
	else
	{
		int i = 0;
		int len = 0;
		std::string text;
		text = std::to_string(elapsedTime);
		float x, y;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, 640, 0, 480);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glColor3f(1.0, 0.0, 0.0);
		x = (640 - (len * 9)) / 2;
		y = 240;
		glRasterPos2i(x, y);
		while (text[i] != '\0')
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i++]);
		}

		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
	// Display the timer
	displayTimer(elapsedTime);

	//sky box
	glPushMatrix();

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 200, 100, 100);
	gluDeleteQuadric(qobj);


	glPopMatrix();



	glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
	keys[key] = true;
}


void keyboardUp(unsigned char key, int x, int y)
{
	keys[key] = false;
}


void checkKeys()
{
	float x = 0;
	float y = 0;
	float z = 0;

	if (keys['w'])
	{
		z = 1;
	}

	if (keys['s'])
	{
		z = -1;
	}

	if (keys['a'])
	{
		x = 1;
	}

	if (keys['d'])
	{
		x = -1;
	}

	if (keys[' '])
	{
		p.jump();
	}
	// debounced key press
	if (keys['c'] && debounce_time > DEBOUNCE)
	{
		if (p.camera.prespective == TP)
			p.camera.prespective = FP;
		else
			p.camera.prespective = TP;
		debounce_time = 0;
	}

	if (keys['1'])
	{
		state = LVL1;
	}

	if (keys['2'])
	{
		state = LVL2;
	}

	if (x || y || z)
		move(Vector(x, y, z));


	glutPostRedisplay();
}


void myMotion(int x, int y)
{
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		p.rotate(Vector(0, 0.1, 0));
	}
	else
	{
		p.rotate(Vector(0, -0.1, 0));
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix


	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 
}


void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;
	
}


void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void LoadAssets()
{
	p.load_model("Models/player/player.3DS");
	p.scale *= 5;
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
	loadBMP(&tex_wall, "Textures/wall.bmp", true);
}


void mouse(int x, int y)
{
	mouse_x = x;
}

void myMouse2(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			// Change view
			if (p.camera.prespective == TP)
				p.camera.prespective = FP;
			else
				p.camera.prespective = TP;
		}
		else if (button == GLUT_RIGHT_BUTTON) {
			// Make the player jump
			p.jump();
		}
	}
}


void update(int value)
{
	checkKeys();
	l1.intensity -= 0.1 * 0.016;
	if (l1.intensity < 0)
		l1.intensity = 0;
	// Detect collision with the house in Level 1
	if (state == LVL1 && physics.is_colliding(p, l1.obstacles[2]) && l1.allCollected) {
		p.move(Vector(-p.position.x/p.speed, 0, -p.position.z/p.speed));
		state = LVL2;
	}

	// Detect collision with the door in Level 2
	if (state == LVL2 && physics.is_colliding(p, l2.obstacles[6]) && l2.allCollected) {
		p.move(Vector(-p.position.x / p.speed, 0, -p.position.z / p.speed));
		state = END;
	}

	if ((mouse_x != last_mouse_x))
	{
		//printf("Mouse: %d, last: %d\n", mouse_x, last_mouse_x);
		p.rotate(Vector(0, (last_mouse_x - mouse_x) * 0.007, 0));
		glutWarpPointer(WIDTH / 2, HEIGHT / 2);
	}

	p.update();

	debounce_time += 0.016;
	if (state != END)
		elapsedTime += 0.016; // Update the elapsed time


	glutPostRedisplay();
	glutTimerFunc(16, update, 0);


}


void move(Vector dir)
{
	// Calculate the direction vector based on the player's rotation
	float rad = p.rotation.y * (3.14 / 180.0); // Convert rotation to radians
	Vector direction;
	direction.x = dir.x * cos(rad) + dir.z * sin(rad);
	direction.z = dir.z * cos(rad) - dir.x * sin(rad);
	direction.y = 0;

	if (state == LVL1)
	{
	for (Entity e : l1.obstacles)
	{
		Vector diff = e.position - p.position;
		if ((!(direction) ^ !(diff)) > 0.0f) {
			if (physics.is_colliding(p, e))
			{
				p.move(-diff *3);
				return;
			}
		}
	}

	for (int c = 0; c < l1.num_collectables; c++)
	{

		if (!l1.collectables[c].collected && physics.is_colliding(p, l1.collectables[c]))
		{
			l1.collect(c, &p);
			p.collectedSoFar++;  // to use it for sccaling the player when he collects the items
				p.scale *= (1.025);
			
		}
	}

}
	if (state == LVL2) {
		for (Entity e : l2.obstacles)
		{
			Vector diff = e.position - p.position;
			if ((!(direction) ^ !(diff)) > 0.0f) {
				if (physics.is_colliding(p, e))
				{
					p.move(-diff * 3);
					return;
				}
			}
		}

		for (int c = 0; c < l2.num_collectables; c++)
		{

			if (!l2.collectables[c].collected && physics.is_colliding(p, l2.collectables[c]))
			{
				l2.collect(c, &p);
				p.scale *= (1.025);
			}
		}
	}
	p.move(direction);
}


void main(int argc, char** argv)
{
	p.rotation = Vector(0, 0, 0);
	p.scale *= 0.4;
	p.hit_box = Vector(3, 1, 1);
	p.camera.eye = Vector(0, 7, -20);
	p.camera.at = Vector(0, 0, 0);
	p.camera.up = Vector(0, 1, 0);
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Calculate centered position
	int windowPosX = (screenWidth - WIDTH) / 2;
	int windowPosY = (screenHeight - HEIGHT) / 2;

	glutInitWindowPosition(windowPosX, windowPosY);

	last_mouse_x = screenWidth/2;

	

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(keyboard);

	glutKeyboardUpFunc(keyboardUp);

	glutTimerFunc(16, update, 0);

	glutPassiveMotionFunc(mouse);

	glutWarpPointer(WIDTH / 2, HEIGHT / 2);

	glutFullScreen();

	glutMouseFunc(myMouse2);

	glutSetCursor(GLUT_CURSOR_NONE);


	//glutMouseFunc(myMouse);

	glutReshapeFunc(myReshape);


	LoadAssets();
	l1 = L1();
	l1.myInit(fovy, aspectRatio, zNear, zFar);
	l2 = L2();
	l2.myInit(fovy, aspectRatio, zNear, zFar);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}




	