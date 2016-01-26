#pragma once

#include <gl\GL.h>

GLfloat trawaVertices[] = {
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.08,
	0.02, 0.0, 0.0,
	0.02, 0.0, 0.08,
	0.01, 0.06, 0.04 };
GLubyte trawaIndices[] = { //6*3 = 18
	0, 1, 2,
	1, 2, 3,
	0, 1, 5,
	1, 2, 5,
	2, 3, 5,
	3, 4, 5 };
GLubyte TrawaColors[] =
{
	0, 255, 0,
	0, 255, 0,
	0, 255, 0,
	0, 255, 0,
	0, 255, 0};