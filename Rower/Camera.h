#pragma once

#include <windows.h>
#include <cmath>
#include "glut.h"
#include <GL/gl.h>

class Camera
{
public:
	Camera(void);
	~Camera(void);
	bool attached;
	void refresh(void);
	GLfloat step;
	GLfloat xRot = 12, yRot = 180, zRot = 0;
	GLdouble *xForward;
	GLdouble *zForward;
	GLfloat angle;
	GLfloat *riderAngle;
	double distance;
};

