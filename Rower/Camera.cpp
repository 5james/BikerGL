#include "Camera.h"
#define PI 3.14159265358979323846

Camera::Camera(void)
{
	distance = 3;
	angle = 50;
	attached = true;
	step = 2.0;
}


Camera::~Camera(void)
{ }

void Camera::refresh()
{
	if (!attached) {
		GLfloat xrotator = (xRot > 170) ? 170 : xRot;
		gluLookAt(
			0, 1.5, 0,
			sin(yRot / 180 * PI), 1.5 - sin(xrotator / 180 * PI), cos(yRot / 180 * PI),
			0, 1, 0);

	}
	else {
		GLfloat xrotator = (xRot > 110) ? 110 : xRot;
		gluLookAt(*xForward - cos(angle / 180 * PI)*distance + sin(yRot / 180 * PI)*distance,
			1.5 + cos(angle / 180 * PI)*distance + cos(xrotator / 180 * PI),
			*zForward - cos(angle / 180 * PI)*distance / 2 + sin(angle / 180 * PI)*distance / 2 + cos(yRot / 180 * PI)*distance,
			*xForward,
			1.5,
			*zForward,
			0.0,
			1.0,
			0.0);
	}
}
