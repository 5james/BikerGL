#pragma once 

#include <stdio.h>
#include <windows.h>
#include "glut.h"

class World 
{
public:
	World();
	~World();
	void draw();
	void grass();
private:
	GLuint texture[1];
	GLfloat yPosition = -0.35f;
	char* groundTexture = "Grass.bmp";
	static const int iloscTrawy = 100;
	double trawaX[iloscTrawy];
	double trawaZ[iloscTrawy];
};
