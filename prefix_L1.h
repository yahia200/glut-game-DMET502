#pragma once
//#include "TextureBuilder.h"
#include "GLTexture.h"
#include "prefix_Entity.h"
#include "prefix_Player.h"
#include <glut.h>

enum {
	tree = 0,
	tree2,
};

class L1
{
public:
	void InitLightSource();
	void InitMaterial();
	void myInit(float fovy, float aspectRatio, float zNear, float zFar);
	void Display(Player p);
	Entity obstacles[2];
	void RenderGround();
	GLTexture tex_ground;
	L1();
	GLuint tex;

};

