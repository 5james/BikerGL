#pragma once

#include <windows.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <cfloat>
#include <GL/gl.h>
#include "World.h"
#include "Rider.h"
#include "Camera.h"
#include "Skybox.h"
#include "vertices.h"

static bool rotate_right = false, rotate_left = false, rotate_up = false, rotate_down = false, companyOn = false;
static GLfloat intensity = 5.0;
static int frame_no = 0;
static World* world;
static Rider *rider;
static Camera *camera;
static Skybox *skybox;


//void drawRider(int frame_no, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ, GLfloat offsetX, GLfloat offsetZ);