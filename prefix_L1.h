#pragma once
//#include "TextureBuilder.h"
#include "GLTexture.h"
#include "prefix_Entity.h"
#include "prefix_Player.h"
#include <glut.h>

enum { // asami el obstacles
	tree = 0, // awel wa7ed bas el me7tag '='
	tree2,




	num_obstacles // lazem ykoon a5er 7aga fe el enum
};

class L1
{
public:
	void InitLightSource();
	void InitMaterial();
	void myInit(float fovy, float aspectRatio, float zNear, float zFar);
	void Display(Player p);
	Entity obstacles[num_obstacles];
	void RenderGround();
	GLTexture tex_ground;
	L1();
	GLuint tex;

};

