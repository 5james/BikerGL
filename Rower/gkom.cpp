#include"gkom.h"
#include <iostream>

bool perspective = false;

//======================================== INIT =================================================

void init()
{
	srand(time(NULL));
	

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 20.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);

	glEnable(GL_NORMALIZE); // dbaj o to zeby wektory normalne mialy dlugosc jednostkowa

	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.3, 0.9, 0.8f);   // kolor tla
	glutPostRedisplay();

	world = new World();
	rider = new Rider();
	camera = new Camera();
	skybox = new Skybox(20);

	world->grass();

	camera->riderAngle = &(rider->constAngle);
	camera->xForward = (&(rider->Xforward));
	camera->zForward = &(rider->Zforward);
}

//=================================================================================================
//===================================== DISPLAYOBJECTS ============================================

void displayObjects(int frame_no)
{
	glPushMatrix();

	if (perspective)
	{
		gluPerspective(30, (GLfloat)640 / 480, 7.5, 6);
	}

	camera->refresh();

	if (perspective)
	{
		glPushMatrix();
		skybox->refresh();
		glPopMatrix();
	}


	world->draw();


	rider->nextStep(rider->step, frame_no);
	rider->draw(frame_no);



	glPopMatrix();
}

//=================================================================================================
//================================= DISPLAY =======================================================

void display()
{
	static int frameCountSpeed = 0;
	frameCountSpeed++;
	if (frameCountSpeed % 3 == 0)
	{
		frameCountSpeed = 0;
		if (frame_no < 360)
			frame_no++;
		else
			frame_no = 0;
	}

	glMaterialf(GL_FRONT, GL_SHININESS, 0.0 + intensity);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	displayObjects(frame_no);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glFlush(); 
	glutSwapBuffers();   
}

void reshape(GLsizei w, GLsizei h)
{
	if (h > 0 && w > 0)
	{
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (w <= h)
			glOrtho(-2.25, 2.25, -2.25*h / w, 2.25*h / w, -10.0, 10.0);
		else
			glOrtho(-2.25*w / h, 2.25*w / h, -2.25, 2.25, -10.0, 10.0);
		glMatrixMode(GL_MODELVIEW);
	}
}

static void SpecialKey(unsigned char key, int x, int y) //Obsluga klawiatury, x,y - wspolrzedne polozenia myszy
{
	switch (key)
	{
	case 'i':
		if (camera->xRot > camera->step)
			camera->xRot -= camera->step;
		break;	
	case 'p':
		perspective = !perspective;
			break;
	case 'k':
		if (camera->attached == false)
		{
			if (camera->xRot < 174)
				camera->xRot += camera->step;
		}
		else
		{
			if (camera->xRot < 110)
				camera->xRot += camera->step;
		}
		break;
	case 'j':
		camera->yRot -= camera->step;
		break;
	case 'l':
		camera->yRot += camera->step;
		break;
	case 'm':
		camera->attached = !(camera->attached);
		camera->xRot = 12, camera->yRot = 180;
		rider->reset();
		break;
	case '.':
		camera->distance += 0.3;
		break;

	case ',':
		camera->distance -= 0.3;
		break;
	case 'a':
		if (rider->turn < 22)
			rider->turn += rider->step / 2;
		break;
	case 'd':
		if (rider->turn > -22)
			rider->turn -= rider->step / 2;
		break;
	case  's':
		rider->movementSpeed -= 0.1;
		break;
	case 'w':
		rider->movementSpeed += 0.1;
		break;
	case 'r':
		rider->Xforward = 0;
		rider->Zforward = 0;
		rider->pedalingSpeed = 0;
		rider->movementSpeed = 0;
		skybox->radius += 0.5;
		break;
	case 't':
		intensity += 0.5;
		break;
	case 'y':
		intensity -= 0.5;
		break;
	case 'q':
		exit(0);
	}
	glutPostRedisplay(); 
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(640, 480);
	glutCreateWindow("GKOM - Rowerzysta");

	glutDisplayFunc(display);			//Rejestracja funkcji odpowiedzialnej za wyswietlanie zawartosci okna
	glutReshapeFunc(reshape);			//Rejestracja funkcji odpowiedzialnej za zmiane parametrow po zmianie rozmiaru okna
	glutKeyboardFunc(SpecialKey);		//Rejestracja funkcji odpowiedzialnej za obsluge klawiatury
	glutIdleFunc(display);				//Odswieza obraz sceny

	init();
	glutMainLoop();
}