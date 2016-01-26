#include "World.h"
#include "SOIL.h"
#include "Rider.h"
#include "worldVertices.h"

World::World()
{

	this->texture[0] = SOIL_load_OGL_texture
		(
		groundTexture,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
}
World::~World()
{
}

void World::draw()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	GLfloat worldRange = (float)RANGE;
	GLfloat eachTextureWidth = (float)1.0;

	glColor3f(0.0f, 1.0f, 0.0f);

	for (auto i = -worldRange; i <= worldRange; i += eachTextureWidth)
	{
		glBegin(GL_QUAD_STRIP);
		glNormal3f(0.0f, 1.0f, 0.0f);
		int cord = 0;
		for (auto j = -worldRange; j <= worldRange; j += eachTextureWidth)
		{
			glTexCoord2f(0.0f, (float)(cord % 2)); glVertex3f(i, yPosition, j);
			glTexCoord2f(1.0f, (float)(cord % 2)); glVertex3f(i + eachTextureWidth, yPosition, j);
			++cord;
		}
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	for (int i = 0; i < iloscTrawy; i++)
	{
		glPushMatrix();
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, TrawaColors);
		glVertexPointer(3, GL_FLOAT, 0, trawaVertices);
		glTranslatef(trawaX[i], yPosition, trawaZ[i]);
		glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_BYTE, trawaIndices);
		glPopMatrix();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
void World::grass()
{
	for (int i = 0; i < iloscTrawy; i++)
	{
		trawaX[i] = double(rand() % RANGE * 2) - (double)RANGE;
		trawaZ[i] = double(rand() % RANGE * 2) - (double)RANGE;
	}
}
