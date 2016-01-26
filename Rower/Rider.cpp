#include "Rider.h"
#include "riderVertices.h"


Rider::Rider()
{
	quadratic = gluNewQuadric();
	step = 3.0;
}



Rider::~Rider()
{
}

void Rider::nextStep(const GLfloat step, int frame_no)
{
	if (movementSpeed < 0.05 && movementSpeed >= 0.0)
		pedalingSpeed = 0;
	else if (movementSpeed < 0.2 && movementSpeed >= 0.05)
		pedalingSpeed = 2;
	else if (movementSpeed < 0.3 && movementSpeed >= 0.2)
		pedalingSpeed = 3;
	else if (movementSpeed < 0.4 && movementSpeed >= 0.3)
		pedalingSpeed = 4;
	else if (movementSpeed < 0.5 && movementSpeed >= 0.4)
		pedalingSpeed = 5;
	else if (movementSpeed > -0.05 && movementSpeed < 0.0)
		pedalingSpeed = 0;
	else if (movementSpeed > -0.2 && movementSpeed <= -0.05)
		pedalingSpeed = -2;
	else if (movementSpeed > -0.3 && movementSpeed <= -0.2)
		pedalingSpeed = -3;
	else if (movementSpeed > -0.4 && movementSpeed <= -0.3)
		pedalingSpeed = -4;
	else if (movementSpeed > -0.5 && movementSpeed <= -0.4)
		pedalingSpeed = -5;
	else
		pedalingSpeed = (movementSpeed > 0.0 ? 8.0 : -8.0);

	if (pedalingSpeed > 0)
		constAngle += (turn * PI / 180) / 2;
	else if (pedalingSpeed < 0)
		constAngle -= (turn * PI / 180) / 2;


	Xforward += movementSpeed * step / 100 * cos(constAngle * PI / 180.0);  // counting movement axis x
	Zforward -= movementSpeed * step / 100 * sin(constAngle * PI / 180.0);  // counting movement axis z
	if (Xforward > RANGE || Xforward < -RANGE)
	{
		Xforward = -Xforward;
	}
	if (Zforward > RANGE || Zforward < -RANGE)
	{
		Zforward = -Zforward;
	}

	if (pedalingSpeed > 0)
	{
		wheelsAngle += pedalingSpeed / 3;
		legsAngle += pedalingSpeed / 2;
	}
	else if (pedalingSpeed<0)
	{
		wheelsAngle += pedalingSpeed / 3;
		legsAngle += pedalingSpeed / 2;
	}

	legsAngle = (legsAngle > 360) ? legsAngle - 360 : legsAngle;
	wheelsAngle = (wheelsAngle > 360) ? wheelsAngle - 360 : wheelsAngle;

}


void Rider::draw(int frame_no)
{
	glPushMatrix();
	glTranslatef(Xforward, 0, Zforward);
	glRotatef(constAngle, 0.0, 1.0, 0.0);

	// 1. SIODELKO
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glPushMatrix();  // bagaznik
	glVertexPointer(3, GL_DOUBLE, 0, siodelkoVertices);
	glColorPointer(3, GL_DOUBLE, 0, colors);
	glTranslatef(-0.5, 0.5, 0.1);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glDrawElements(GL_TRIANGLE_STRIP, 48, GL_UNSIGNED_BYTE, siodelkoIndices);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	// 2. KOLA
	//	a.TYLNIE
	//		OPONA
	glPushMatrix();
	glTranslatef(-0.65, 0.0, 0.0);
	glRotatef((float)frame_no, 0.0, 0.0, 1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialOpona);
	glutSolidTorus(0.05, 0.31, 30, 30);
	glPopMatrix();

	//		SZPRYCHY
	for (int i = 0; i < spokes; i++)
	{
		glPushMatrix();
		glTranslatef(-0.65, 0.0, 0.0);
		glRotatef(wheelsAngle + (180 / spokes) * i, 0.0, 0.0, -1.0);
		glTranslatef(0.0, -0.28, 0.0); 
		glRotatef(90, 0, 0, 1);
		glRotatef(90, 0, 1, 0);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, szprychy_diffuse);
		gluCylinder(quadratic, 0.08f / spokes, 0.08f / spokes, 0.56, 20, 1);
		glPopMatrix();
	}

	//	b.PRZEDNIE
	//		OPONA
	glPushMatrix();
	glTranslatef(0.65, 0.0, 0.0);
	glRotatef(turn, 0, 1, 0);
	glRotatef((float)frame_no, 0.0, 0.0, 1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialOpona);
	glutSolidTorus(0.05, 0.31, 30, 30);
	glPopMatrix();

	//		SZPRYCHY
	for (int i = 0; i < spokes; i++)
	{
		glPushMatrix();
		glTranslatef(0.65, 0.0, 0.0);
		glRotatef(turn, 0, 1, 0); // skrecanie
		glRotatef(wheelsAngle + (180 / spokes) * i, 0.0, 0.0, -1.0);
		glTranslatef(0.0, -0.28, 0.0);
		glRotatef(90, 0, 0, 1);
		glRotatef(90, 0, 1, 0);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, szprychy_diffuse);
		gluCylinder(quadratic, 0.08f / spokes, 0.08f / spokes, 0.56, 20, 1);
		glPopMatrix();
	}

	// 3. CIALO
	glPushMatrix();
	glTranslatef(-0.3, 0.54, 0.0);
	glRotatef(38, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cialo_diffuse);
	gluCylinder(quadratic, 0.1f, 0.1f, 0.55, 20, 1);
	glPopMatrix();

	// 4. NOGI
	//	a. LEWA
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.08);
	glTranslatef(-0.25, 0.57, 0.0);
	glRotatef(-45 + sin(legsAngle * PI / 180) * 20, 0, 0, 1);
	glRotatef(90, 0, 1, 0);

	//		UDO
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cialo_diffuse);
	gluCylinder(quadratic, 0.035f, 0.035f, 0.53, 20, 1);
	glPopMatrix();
	//		LYDKA
	glPushMatrix();
	leftCurAngle = sin(45 + legsAngle* PI / 180) * 58.3;
	glTranslatef(0.0, 0.0, 0.53);
	glRotatef(leftCurAngle, 1.0, 0.0, 0.0);
	glRotatef(60, 1, 0, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cialo_diffuse);
	gluCylinder(quadratic, 0.035f, 0.035f, 0.33, 20, 1);
	glPopMatrix();

	glPopMatrix();

	//	b. PRAWA
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.08);
	glTranslatef(-0.25, 0.57, 0.0);
	glRotatef(-45 - sin(legsAngle * PI / 180) * 20, 0, 0, 1);
	glRotatef(90, 0, 1, 0);

	//		UDO
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cialo_diffuse);
	gluCylinder(quadratic, 0.035f, 0.035f, 0.53, 20, 1);
	glPopMatrix();
	//		LYDKA	
	glPushMatrix();
	rightCurAngle = -sin(45 + legsAngle* PI / 180) * 58.3;
	glTranslatef(0.0, 0.0, 0.53);
	glRotatef(rightCurAngle, 1.0, 0.0, 0.0);
	glRotatef(60, 1, 0, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cialo_diffuse);
	gluCylinder(quadratic, 0.035f, 0.035f, 0.33, 20, 1);
	glPopMatrix();

	glPopMatrix();

	// 5. RECE
	//	a. PRAWA

	GLfloat alpha, beta, gamma;
	GLfloat con = 0.1 * sin(turn * PI / 180) / cos(turn * PI / 180);
	gamma = sin((0.29 / 0.49 + con) * PI / 180) / cos((0.29 / 0.49 + con) * PI / 180);
	GLfloat x = 0.57 + con;
	alpha = acosf((0.42 * 0.42 + x * x - 0.2 * 0.2) / (0.84 * x));
	beta = asinf((sin(alpha) * x) / 0.2);

	glPushMatrix();
	glTranslatef(0.27, 0.53, 0.1);
	glRotatef(135, 0, 0, 1);
	glTranslatef(0.42, 0.0, 0.0);
	glRotatef(-165 - (gamma * 180 / PI + alpha * 180 / PI), 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cialo_diffuse);
	gluCylinder(quadratic, 0.028f, 0.028f, 0.42, 20, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.27, 0.53, 0.1);
	glRotatef(135, 0, 0, 1);
	glTranslatef(0.42, 0.0, 0.0);
	glRotatef(-165 - (gamma * 180 / PI + alpha * 180 / PI), 0, 0, 1);
	glTranslatef(0.42, 0.0, 0.0);
	glRotatef((beta * 180 / PI), 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cialo_diffuse);
	gluCylinder(quadratic, 0.02f, 0.02f, 0.2, 20, 1);
	glPopMatrix();

	//	b. LEWA

	con = -0.1 * sin(turn * PI / 180) / cos(turn * PI / 180);
	gamma = sin((0.29 / 0.49 + con) * PI / 180) / cos((0.29 / 0.49 + con) * PI / 180);
	x = 0.5777 + con;
	alpha = acosf((0.42 * 0.42 + x * x - 0.2 * 0.2) / (0.84 * x));
	beta = asinf((sin(alpha) * x) / 0.2);

	glPushMatrix();
	glTranslatef(0.27, 0.53, -0.1);
	glRotatef(135, 0, 0, 1);
	glTranslatef(0.42, 0.0, 0.0);
	glRotatef(-165 - (gamma * 180 / PI + alpha * 180 / PI), 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cialo_diffuse);
	gluCylinder(quadratic, 0.028f, 0.028f, 0.42, 20, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.27, 0.53, -0.1);

	glRotatef(135, 0, 0, 1);
	glTranslatef(0.42, 0.0, 0.0);

	glRotatef(-165 - (gamma * 180 / PI + alpha * 180 / PI), 0, 0, 1);
	glTranslatef(0.42, 0.0, 0.0);

	glRotatef((beta * 180 / PI), 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cialo_diffuse);
	gluCylinder(quadratic, 0.02f, 0.02f, 0.2, 20, 1);
	glPopMatrix();

	// 6. ROWER
	//	a.rama1
	glPushMatrix();
	glTranslatef(-0.2, 0.0, 0.0);

	glRotatef(207, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rowerDiffuse);
	gluCylinder(quadratic, 0.02f, 0.02f, 0.75, 20, 1);
	glPopMatrix();

	//	b.rama2
	glPushMatrix();
	glTranslatef(-0.4, 0.35, 0.0);

	glRotatef(90, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rowerDiffuse);
	gluCylinder(quadratic, 0.02f, 0.02f, 0.9, 20, 1);
	glPopMatrix();

	//	a.rama3
	glPushMatrix();
	glTranslatef(-0.2, 0.0, 0.0);

	glRotatef(-64, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rowerDiffuse);
	gluCylinder(quadratic, 0.02f, 0.02f, 0.57, 20, 1);
	glPopMatrix();

	//	a.rama4
	glPushMatrix();
	glTranslatef(-0.2, 0.0, 0.0);
	glRotatef(-90, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rowerDiffuse);
	gluCylinder(quadratic, 0.02f, 0.02f, 0.45, 20, 1);
	glPopMatrix();

	//	b.rama5
	glPushMatrix();
	glTranslatef(-0.4, 0.35, 0.0);

	glRotatef(-130, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rowerDiffuse);
	gluCylinder(quadratic, 0.02f, 0.02f, 0.45, 20, 1);
	glPopMatrix();


	//	c. raczka
	glPushMatrix();
	glTranslatef(0.5, 0.55, 0.0);
	glRotatef(turn, 0, 1, 0); 
	glTranslatef(0, 0, -0.2);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rowerDiffuse);
	gluCylinder(quadratic, 0.02f, 0.02f, 0.4, 20, 1);
	glPopMatrix();

	// d. glowka kierwonicy / sztyca
	glPushMatrix();
	glTranslatef(0.5, 0.35, 0.0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rowerDiffuse);
	gluCylinder(quadratic, 0.02f, 0.02f, 0.2, 10, 10);
	glPopMatrix();

	//glowa
	glPushMatrix();
	glTranslatef(0.24, 0.98, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, glowa_diffuse);
	glutSolidSphere(0.15, 20, 20);
	glPopMatrix();

	glPopMatrix();
}

void Rider::reset()
{
	turn = Xforward = Zforward = movementSpeed = constAngle = pedalingSpeed = wheelsAngle = 0;
}