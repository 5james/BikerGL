#pragma once

#include <windows.h>
#include <cmath>
#include "glut.h"
#include <GL/gl.h>

#define PI 3.14159265358979323846
#define RANGE 20


class Rider
{
private:
	GLUquadricObj *quadratic;
public:
	GLdouble Xforward = 0, Zforward = 0, turn = 0, movementSpeed = 0, pedalingSpeed = 0;
	GLfloat constAngle = 0;
	GLfloat wheelsAngle = 0;
	GLfloat legsAngle = 0;
	GLfloat leftCurAngle, rightCurAngle;
	GLfloat step;
	int spokes = 6;

	Rider();
	~Rider();
	void draw(int frame_no);
	void draw(int frame_no, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ, GLfloat offsetX, GLfloat offsetZ);
	void nextStep(const GLfloat step, int frame_no);
	void reset();
};

