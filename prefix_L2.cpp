#include "prefix_L2.h"
//
////=======================================================================
//// Lighting Configuration Function
////=======================================================================
void L2::InitLightSource()
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
void L2::InitMaterial()
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
void L2::myInit(float fovy, float aspectRatio, float zNear, float zFar)
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


void L2::RenderGround()
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


void L2::Display(Player* p)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	//// Draw Ground
	RenderGround();
	DrawWalls();
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


L2::L2()
{
	tex_ground.Load("Textures/wall.bmp");


	obstacles[wall1] = Entity(Vector(55, 0, 0), Vector(1, 1, 1));
	obstacles[chair] = Entity(Vector(35, 0, -25), Vector(0.5, 0.5, 0.5));
	obstacles[chair].load_model("Models/chair/chair.3ds");
	obstacles[chair].scale *= 0.03;

	obstacles[dresser] = Entity(Vector(35, 0.5, 25), Vector(0.5, 0.5, 0.5));
	obstacles[dresser].load_model("Models/Dresser/Dresser.3ds");
	obstacles[dresser].scale *= 0.008;

	obstacles[table] = Entity(Vector(-35, 0, 0), Vector(0.5, 0.5, 0.5));
	obstacles[table].load_model("Models/table/uploads_files_3892034_1084_table.3ds");
	obstacles[table].scale *= 0.03;

	obstacles[armChair] = Entity(Vector(5, 0, -25), Vector(0.5, 0.5, 0.5));
	obstacles[armChair].load_model("Models/Armchair 3/Armchair 3.3ds");
	obstacles[armChair].scale *= 0.003;

	obstacles[door] = Entity(Vector(55, 0, 0), Vector(0.5, 0.5, 0.5));
	obstacles[door].load_model("Models/door/door.3ds");
	obstacles[door].scale *= 0.05;

	collectables[0] = Collectable(Vector(0, 0, 20), Vector(0.1, 1, 0.1), egg);
	collectables[0].load_model("Models/salt/salt.3ds");
	collectables[0].scale *= 0.03;

}

void L2::collect(int c, Player* p)
{
	collectables[c].collected = true;
	printf("type: %d\n", collectables[c].type);
	p->collectables[collectables[c].type]++;
}
void L2::DrawWall(GLTexture& texture, float width, float height)
{
	glEnable(GL_TEXTURE_2D);  // Enable 2D Texturing
	glBindTexture(GL_TEXTURE_2D, tex_wall.texture[0]);  // Bind the texture

	glBegin(GL_QUADS);  // Draw a rectangle

	// Define the 4 corners of the wall and their texture coordinates
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2, 0, -height / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2, 0, -height / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2, 0, height / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2, 0, height / 2);

	glEnd();

	glDisable(GL_TEXTURE_2D);  // Disable 2D Texturing after drawing the wall
}
void L2::DrawWalls()
{
	// Load the texture for the walls
	tex_wall.Load("Textures/wall.bmp");

	// Left Wall (Parallel to Z-axis, rotated 180 degrees)
	glPushMatrix();
	glTranslatef(5, 0, -25);
	glRotatef(90, 180, 1, 0);// Move the wall to the correct position
	DrawWall(tex_wall, 100, 70);  // Draw the back wall (Width: 20, Height: 10)
	glPopMatrix();

	// front Wall )with corridor) (Rotated 90 degrees around Y-axis)
	glPushMatrix();
	glTranslatef(55, 0, 0);  // Position left wall
	glRotatef(90, 0, 1, 90);  // Rotate the left wall
	DrawWall(tex_wall, 70, 70);  // Draw left wall (Width: 10, Height: 10)
	glPopMatrix();


	// inside Wall
	glPushMatrix();
	glTranslatef(35, 0,-25);  // Position left wall
	glRotatef(90, 0, 1, 90);  // Rotate the left wall
	DrawWall(tex_wall, 70, 35);  // Draw left wall (Width: 10, Height: 10)
	glPopMatrix();
	// inside Wall 
	glPushMatrix();
	glTranslatef(35, 0, 25);  // Position left wall
	glRotatef(90, 0, 1, 90);  // Rotate the left wall
	DrawWall(tex_wall, 70, 35);  // Draw left wall (Width: 10, Height: 10)
	glPopMatrix();
	 

	// inside Wall right (Parallel to Z-axis)
	glPushMatrix();
	glTranslatef(45.1, 0, 7.5);
	glRotatef(-90, 180, 1, 0);// Position front wall
	DrawWall(tex_wall, 21, 70);  // Draw the front wall (Width: 20, Height: 10)
	glPopMatrix();


	// inside Wall left (Parallel to Z-axis)
	glPushMatrix();
	glTranslatef(45.1, 0, -7.5);
	glRotatef(-90, 180, 1, 0);// Position front wall
	DrawWall(tex_wall, 21, 70);  // Draw the front wall (Width: 20, Height: 10)
	glPopMatrix();

	// Right Wall (Parallel to Z-axis)
	glPushMatrix();
	glTranslatef(5, 0, 25);
	glRotatef(-90, 180, 1, 0);// Position front wall
	DrawWall(tex_wall, 100, 70);  // Draw the front wall (Width: 20, Height: 10)
	glPopMatrix();

	// Back Wall (Rotated -90 degrees around Y-axis)
	glPushMatrix();
	glTranslatef(-35, 0, 0);  // Position right wall
	glRotatef(-90, 0, 1, 90);  // Rotate the right wall
	DrawWall(tex_wall, 70, 70);  // Draw right wall (Width: 10, Height: 10)
	glPopMatrix();

	
}
L2::~L2()
{

	tex_wall.Load("Textures/wall.bmp");
}

