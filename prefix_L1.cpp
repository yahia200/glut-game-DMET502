#include "prefix_L1.h"
//
////=======================================================================
//// Lighting Configuration Function
////=======================================================================
void L1::InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}
//
////=======================================================================
//// Material Configuration Function
////======================================================================
void L1::InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}
//
////=======================================================================
//// OpengGL Configuration Function
////=======================================================================
void L1::myInit(float fovy, float aspectRatio, float zNear, float zFar)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);



	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}


void L1::RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-100, 0, -100);
	glTexCoord2f(5, 0);
	glVertex3f(100, 0, -100);
	glTexCoord2f(5, 5);
	glVertex3f(100, 0, 100);
	glTexCoord2f(0, 5);
	glVertex3f(-100, 0, 100);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

// Method to draw a textured wall


void L1::Display(Player* p)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat lightIntensity[] = { intensity, intensity, intensity, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	// Draw Ground
	RenderGround();

	

	for (Entity e : obstacles)
	{
		e.draw();
	}

	for (Collectable c : collectables)
	{
		if (!c.collected)
			c.draw();
	}

	// Draw house Model
	p->draw();
}


L1::L1()
{
	tex_ground.Load("Textures/ground.bmp");


	obstacles[tree] = Entity(Vector(10, 0, 0), Vector(1, 1, 1));
	obstacles[tree].load_model("Models/tree/Tree1.3ds");

	obstacles[tree1] = Entity(Vector(66, 0, 22), Vector(1, 1, 1));
	obstacles[tree1].load_model("Models/tree/Tree1.3ds");
	
	obstacles[tree2] = Entity(Vector(45, 0, 10), Vector(1, 1, 1));
	obstacles[tree2].load_model("Models/tree/Tree1.3ds");
	
	obstacles[tree3] = Entity(Vector(-46, 0, -10), Vector(1, 1, 1));
	obstacles[tree3].load_model("Models/tree/Tree1.3ds");
	
	obstacles[tree4] = Entity(Vector(-22, 0, -22), Vector(1, 1, 1));
	obstacles[tree4].load_model("Models/tree/Tree1.3ds");
	
	obstacles[tree5] = Entity(Vector(78, 0, 22), Vector(1, 1, 1));
	obstacles[tree5].load_model("Models/tree/Tree1.3ds");
	
	obstacles[house] = Entity(Vector(80, 0, 0), Vector(1.5, 1, 5.4));
	obstacles[house].load_model("Models/house/house.3ds");
	obstacles[house].rotate({ 90,0,90 });
	obstacles[house].scale *= 2; 

	obstacles[outdoortable] = Entity(Vector(38, -2, 20), Vector(0.5, 4, 4));
	obstacles[outdoortable].load_model("Models/outdoorfurn/Outdoor Furniture_02_3ds.3ds");
	obstacles[outdoortable].scale *= 0.08;

	//// Wall dimensions and positions around the house
	//obstacles[wall1] = Entity(Vector(80, 5, -10), Vector(20, 10, 1)); // Back wall
	//obstacles[wall2] = Entity(Vector(70, 5, 0), Vector(1, 10, 10));  // Left wall
	//obstacles[wall3] = Entity(Vector(90, 5, 0), Vector(1, 10, 10));  // Right wall
	//obstacles[wall4] = Entity(Vector(80, 5, 10), Vector(20, 10, 1)); // Front wall

	//// Load models for walls (using a cube)
	//obstacles[wall1].load_model("Models/cube/cube.3ds");
	//obstacles[wall2].load_model("Models/cube/cube.3ds");
	//obstacles[wall3].load_model("Models/cube/cube.3ds");
	//obstacles[wall4].load_model("Models/cube/cube.3ds");


	

	collectables[0] = Collectable(Vector(50, -0.1, 20), Vector(0.1, 1, 0.1), egg);
	collectables[0].load_model("Models/egg/egg.3ds");
	collectables[0].scale *= 0.1;

	collectables[1] = Collectable(Vector(90, -0.1, 20), Vector(1, 1, 1), apple);
	collectables[1].load_model("Models/apple/apple.3ds");
	collectables[1].scale *= 0.6;

	collectables[2] = Collectable(Vector(-10, 0.1, 20), Vector(0.1, 1, 0.1), apple);
	collectables[2].load_model("Models/apple/apple.3ds");
	collectables[2].scale *= 0.6;

	collectables[3] = Collectable(Vector(-22, 0.1, 20), Vector(0.00001, 1, 0.00001), egg);
	collectables[3].load_model("Models/egg/egg.3ds");
	collectables[3].scale *= 0.1;
}

void L1::CheckAllCollected() {
	allCollected = true; // Assume all are collected
	for (int i = 0; i < num_collectables; i++) {
		if (!collectables[i].collected) {
			allCollected = false; // If any collectable is not collected, set to false
			break;
		}
	}
}


void L1::collect(int c, Player *p)
{
	collectables[c].collected = true;
	printf("type: %d\n", collectables[c].type);
	p->collectables[collectables[c].type]++;
	CheckAllCollected(); // Update the allCollected flag
}

L1::~L1()
{
}

