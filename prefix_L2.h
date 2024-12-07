#pragma once
//#include "TextureBuilder.h"
#include "GLTexture.h"
#include "prefix_Entity.h"
#include "prefix_Collectable.h"
#include "prefix_Player.h"
#include <glut.h>


class L2
{
	enum { // asami el obstacles
		tree = 0, // awel wa7ed bas el me7tag '='
		wall1,  // Back wall
		wall2,  // Left wall
		wall3,  // Right wall
		wall4,  // Front wall
		wall5,
		door,
		chair,
		chair2,
		dresser,
		dresser1,
		sneakers,
		table,
		table2,
		armChair,


		num_obstacles // lazem ykoon a5er 7aga fe el enum
	};

public:
	void InitLightSource();
	void InitMaterial();
	void myInit(float fovy, float aspectRatio, float zNear, float zFar);
	void Display(Player* p);
	Entity obstacles[num_obstacles];
	const static int num_collectables = 1;
	Collectable collectables[num_collectables];
	void RenderGround();
	void DrawWall(GLTexture& texture, float width, float height);
	void DrawWalls();
	void CheckAllCollected();
	void collect(int c, Player* p);
	bool allCollected = false; // Flag to indicate all collectables are collected
	GLTexture tex_ground;

	GLTexture tex_wall;
	L2();
	~L2();

};

