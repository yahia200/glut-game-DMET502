#pragma once
//#include "TextureBuilder.h"
#include "GLTexture.h"
#include "prefix_Entity.h"
#include "prefix_Collectable.h"
#include "prefix_Player.h"
#include <glut.h>


class L1
{
enum { // asami el obstacles
	tree = 0, // awel wa7ed bas el me7tag '='
	outdoortable,
	house,
	tree1,
	tree2,
	tree3,
	tree4,
	tree5,
	wall1,  // Back wall
	wall2,  // Left wall
	wall3,  // Right wall
	wall4,  // Front wall

	num_obstacles // lazem ykoon a5er 7aga fe el enum
};
public:
	void InitLightSource();
	float intensity = 1;
	void InitMaterial();
	void myInit(float fovy, float aspectRatio, float zNear, float zFar);
	void Display(Player *p);
	Entity obstacles[num_obstacles];
	const static int num_collectables = 4;
	Collectable collectables[num_collectables];
	void RenderGround();
	void DrawWall(GLTexture& texture, float width, float height);
	void DrawWalls();
	GLTexture tex_ground;
	GLTexture tex_wall;
	L1();
	void collect(int c, Player *p);
	void CheckAllCollected();
	bool allCollected = false; // Flag to indicate all collectables are collected
	~L1();

};

