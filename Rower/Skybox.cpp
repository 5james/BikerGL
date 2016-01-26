#include "Skybox.h"
#include "SOIL.h"

Skybox::Skybox(double r)
{
	this->radius = r;

	this->texture[0] = SOIL_load_OGL_texture
		(
		"front.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
	this->texture[1] = SOIL_load_OGL_texture
		(
		"left.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
	this->texture[2] = SOIL_load_OGL_texture
		(
		"back.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
	this->texture[3] = SOIL_load_OGL_texture
		(
		"right.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
	this->texture[4] = SOIL_load_OGL_texture
		(
		"top.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
	this->texture[5] = SOIL_load_OGL_texture
		(
		"bottom.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
}


Skybox::~Skybox(void)
{

}


void Skybox::refresh()
{
	glPushMatrix();

	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	glColor4f(1, 1, 1, 1);

	// Render the front quad
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(radius, -radius, -radius);
	glTexCoord2f(1, 0); glVertex3f(-radius, -radius, -radius);
	glTexCoord2f(1, 1); glVertex3f(-radius, radius, -radius);
	glTexCoord2f(0, 1); glVertex3f(radius, radius, -radius);
	glEnd();

	// Render the left quad
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(radius, -radius, radius);
	glTexCoord2f(1, 0); glVertex3f(radius, -radius, -radius);
	glTexCoord2f(1, 1); glVertex3f(radius, radius, -radius);
	glTexCoord2f(0, 1); glVertex3f(radius, radius, radius);
	glEnd();

	// Render the back quad
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-radius, -radius, radius);
	glTexCoord2f(1, 0); glVertex3f(radius, -radius, radius);
	glTexCoord2f(1, 1); glVertex3f(radius, radius, radius);
	glTexCoord2f(0, 1); glVertex3f(-radius, radius, radius);
	glEnd();

	// Render the right quad
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-radius, -radius, -radius);
	glTexCoord2f(1, 0); glVertex3f(-radius, -radius, radius);
	glTexCoord2f(1, 1); glVertex3f(-radius, radius, radius);
	glTexCoord2f(0, 1); glVertex3f(-radius, radius, -radius);
	glEnd();

	// Render the top quad
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-radius, radius, -radius);
	glTexCoord2f(0, 0); glVertex3f(-radius, radius, radius);
	glTexCoord2f(1, 0); glVertex3f(radius, radius, radius);
	glTexCoord2f(1, 1); glVertex3f(radius, radius, -radius);
	glEnd();

	// Render the bottom quad
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-radius, -radius, -radius);
	glTexCoord2f(0, 1); glVertex3f(-radius, -radius, radius);
	glTexCoord2f(1, 1); glVertex3f(radius, -radius, radius);
	glTexCoord2f(1, 0); glVertex3f(radius, -radius, -radius);
	glEnd();

	glPopAttrib();
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);

}