#pragma once
#include <windows.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <cfloat>
#include <GL/gl.h>

class Skybox
{
public:
	Skybox(double r);
	~Skybox(void);
	void refresh(void);
	double radius;
	GLuint texture[6];

};

