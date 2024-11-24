#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include "prefix_Entity.h"
#include "prefix_Player.h"
#include "prefix_Camera.h"
#include "prefix_L1.h"
#include <glut.h>
#include <windows.h>

#define DEBOUNCE 0.1


int WIDTH = 1280;
int HEIGHT = 720;
bool keys[256];
int mouse_x = 0;
int last_mouse_x = WIDTH/2;
float debounce_time = 0;
GLuint tex;
char title[] = "3D Model Loader Sample";
// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 100;




int cameraZoom = 0;
Player p;
L1 l1;


void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void checkKeys();
void move(Vector v);
bool is_colliding(Entity e1, Entity e2);


//=======================================================================
// Display Function
//=======================================================================
void myDisplay(void)
{
	
	l1.Display(p);


	//sky box
	glPushMatrix();

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 100, 100, 100);
	gluDeleteQuadric(qobj);


	glPopMatrix();



	glutSwapBuffers();
}

//=======================================================================
// Keyboard Function
//=======================================================================
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

	if (x || y || z)
		move(Vector(x, y, z));


	glutPostRedisplay();
}


//=======================================================================
// Motion Function
//=======================================================================
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

//=======================================================================
// Mouse Function
//=======================================================================
void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;
	
}

//=======================================================================
// Reshape Function
//=======================================================================
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

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	p.load_model("Models/house/house.3DS");
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
}

//=======================================================================
// Main Function
//=======================================================================

void mouse(int x, int y)
{
	mouse_x = x;
}

void update(int value)
{
	checkKeys();


	if ((mouse_x != last_mouse_x))
	{
		//printf("Mouse: %d, last: %d\n", mouse_x, last_mouse_x);
		p.rotate(Vector(0, (last_mouse_x - mouse_x) * 0.007, 0));
		glutWarpPointer(WIDTH / 2, HEIGHT / 2);
	}

	p.update();

	debounce_time += 0.016;

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

	for (Entity e : l1.obstacles)
	{
		Vector diff = e.position - p.position;
		if ((!(direction) ^ !(diff)) > 0.0f) {
		printf("%d\n", (!(direction) ^ !(diff)) > 0.0f);
			if (is_colliding(p, e))
			{
				return;
			}
		}
	}

	p.move(direction);
}

bool is_colliding(Entity e1, Entity e2)
{
	Vector e1_min = e1.position - e1.hit_box;
	Vector e1_max = e1.position + e1.hit_box;

	Vector e2_min = e2.position - e2.hit_box;
	Vector e2_max = e2.position + e2.hit_box;

	if (e1_min.x < e2_max.x && e1_max.x > e2_min.x &&
		e1_min.y < e2_max.y && e1_max.y > e2_min.y &&
		e1_min.z < e2_max.z && e1_max.z > e2_min.z)
	{
		return true;
	}
	return false;
}

void main(int argc, char** argv)
{
	p.rotation = Vector(90, 0, 0);
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

	glutSetCursor(GLUT_CURSOR_NONE);


	//glutMouseFunc(myMouse);

	glutReshapeFunc(myReshape);


	LoadAssets();
	l1 = L1();
	l1.myInit(fovy, aspectRatio, zNear, zFar);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}