#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include "C:\Users\Matteo\Desktop\Mano\A__DualModeDriverBeta3\include\p5dll.h"
#include <windows.h>

GLint FPS = 120,stop = 3;		// Frames per Second. used in the animation function
			// to control the maximum number of frames generated per second

int lastframe = 0;	
int bend[5];
float position[3];
float angle[3];
float cube_pos[3];
float cube_ang[3];

bool grasp = true;
bool near_to = true;
int spin_x = 0, old_x = 0;		// spin_ amount of spinning
int spin_y = 0, old_y = 0;		// old_  previous value
int phase = 0;		// specifies the current state of the animation

GLint index[14];
GLfloat thumb_length = 14;
GLfloat finger_length = 28;
GLfloat palm_size = 32;

/*
 * menu function
 *
 * op - integer representing the chosen action
 */
void menu(int op) {

  switch(op) {
  case 'Q':
  case 'q':
    exit(0);
  }
}

/*
 * invoked by GLUT when a key is pressed
 *
 * key - pressed key
 * x, y - mouse coordinates
 */
void keyboardDown(unsigned char key, int x, int y)
{
}

/*
 * invoked by GLUT when a key is released
 *
 * key - pressed key
 * x, y - mouse coordinates
 */
void keyboardUp(unsigned char key, int x, int y) {}

/*
 * invoked by GLUT when the window is modified
 *
 * width. height - new size of the window
 */
void reshape(int width, int height)
{
  GLfloat fieldOfView = 45.0f;
  glViewport (0, 0, (GLsizei) width, (GLsizei) height);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fieldOfView, (GLfloat) width/(GLfloat) height, 0.1, 500.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/*
 * invoked by GLUT when a mouse button is released or pressed
 *
 * button - identifier of the button
 * state - current state of the button
 * x, y - mouse coordinates
 */
void mouseClick(int button, int state, int x, int y)
{
	old_x = x;
	old_y = y;

	glutPostRedisplay();
}


void mouseMotion(int x, int y)
{
	spin_x = x - old_x;
	spin_y = y - old_y;

	glutPostRedisplay();
}

/*
 * draws the axis
 *
 * length - length of the 3 axis
 */
void DrawAxes(float length)
{
	glPushMatrix();
	glScalef(length, length, length);

		glLineWidth(2.f);
		glBegin(GL_LINES);

		// x red
		glColor3f(100.f, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(100.f, 0.f, 0.f);

		// y green
		glColor3f(0.f, 100.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 100.f, 0.f);

		// z blue
		glColor3f(0.f, 0.f, 100.f);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 100.f);

		glEnd();
		glLineWidth(1.f);

	glPopMatrix();
}

/*
 * draws a palm of size dim*dim on the XY plane
 * and depth dim/4 along z
 */

void palm (float dim)
{
	glPushMatrix();
		glColor3f(1,1,1);
		glScalef(dim, dim, 0.25 * dim);
		glutSolidCube(1.0);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(0.0, -dim/2, 0.0);
		glutSolidSphere(0.25*dim, 100,100);
	glPopMatrix();
	
}

void palm2(){
	glPushMatrix();
		glColor3f(1,1,1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_POLYGON);
			glVertex3f(-10,-16, -4);//A
			glVertex3f(-10,-4.08, -4);//B
			glVertex3f(-11.86, 3.4, -4);//C
			glVertex3f(-11.49, 8.51, -4);//D
			glVertex3f(-12.29, 16, -4);//E
			glVertex3f(17,16, -4);//F
			glVertex3f(12,-16, -4);//G)
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(-10,-16, 4);//A
			glVertex3f(-10,-4.08, 4);//B
			glVertex3f(-11.86, 3.4, 4);//C
			glVertex3f(-11.49, 8.51, 4);//D
			glVertex3f(-12.29, 16, 4);//E
			glVertex3f(17,16, 4);//F
			glVertex3f(12,-16, 4);//G
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-10,-16, -4);//A
			glVertex3f(-10,-16, 4);//A
			glVertex3f(-10,-4.08, 4);//B
			glVertex3f(-10,-4.08, -4);//B

			glVertex3f(-10,-4.08, 4);//B
			glVertex3f(-10,-4.08, -4);//B
			glVertex3f(-11.86, 3.4, -4);//C
			glVertex3f(-11.86, 3.4, 4);//C

			glVertex3f(-11.86, 3.4, -4);//C
			glVertex3f(-11.86, 3.4, 4);//C
			glVertex3f(-11.49, 8.51, 4);//D
			glVertex3f(-11.49, 8.51, -4);//D

			glVertex3f(-11.49, 8.51, 4);//D
			glVertex3f(-11.49, 8.51, -4);//D
			glVertex3f(-12.29, 16, -4);//E
			glVertex3f(-12.29, 16, 4);//E

			glVertex3f(-12.29, 16, -4);//E
			glVertex3f(-12.29, 16, 4);//E
			glVertex3f(17,16, 4);//F
			glVertex3f(17,16, -4);//F

			glVertex3f(17,16, -4);//F
			glVertex3f(17,16, 4);//F
			glVertex3f(12,-16, 4);//G)
			glVertex3f(12,-16, -4);//G)

			glVertex3f(12,-16, -4);//G)
			glVertex3f(12,-16, 4);//G)
			glVertex3f(-10,-16, 4);//A
			glVertex3f(-10,-16, -4);//A
		glEnd();
	glPopMatrix();
}

/*
 * third phalanx of the finger [invoked by finger(...)]
 */
void phalanx3(float leng)
{
	glPushMatrix();
        glColor3f(1.0,1.0,1.0);
		glTranslatef(0.0, 0.15 * leng, 0.0);
		glScalef(0.66 * leng, leng, 0.66 * leng);
		glutSolidCube(0.2);
	glPopMatrix();

	// Sphere to round the end of the finger
	glPushMatrix();
		glTranslatef(0.0, 0.25*leng, 0.0);
		glutSolidSphere(0.075*leng, 10, 10);
	glPopMatrix();
}

/*
 * 	second phalanx of the finger [invoked by finger(...)]
 */
void phalanx2(float leng, float f)
{
	glPushMatrix();
        glColor3f(1.0,1.0,1.0);
		glTranslatef(0.0, 0.2 * leng, 0.0);
		glScalef(0.5 * leng, leng, 0.5 * leng);
		glutSolidCube(0.3);
	glPopMatrix();

	// sphere
	glPushMatrix();
        glColor3f(0,0,0);
		glTranslatef(0.0, 0.4 * leng, 0.0);
		glRotatef(f, 1.0, 0.0, 0.0);
		glutSolidSphere(0.075 * leng, 10, 10);
		phalanx3(leng);
	glPopMatrix();
}


void phalanx1(float leng, float f1, float f2)
{
	// first phalanx
	glPushMatrix();
        glColor3f(1.0,1.0,1.0);
		glTranslatef(0.0, 0.2*leng, 0.0);
		glScalef(0.5*leng, leng, 0.5*leng);
		glutSolidCube(0.3);
	glPopMatrix();

	// sphere
	glPushMatrix();
        glColor3f(0,0,0);
		glTranslatef(0.0,0.4*leng,0.0);
		glRotatef(f1, 1.0, 0.0, 0.0);
		glutSolidSphere(0.075*leng, 10,10);
		phalanx2(leng, f2);
	glPopMatrix();
}

/* leng -	length of the finger along the Y axis
 *			the dimensions on the XZ plane are proportional to leng
 * f1 -		rotation angle around the Z axis of the whole finger
 * f2 -		rotation angle around the Z axis of the second phalanx w.r.t. the first one
 * f3 -		rotation angle around the Z axis of the third phalanx w.r.t. the second one
 */
void finger(float leng, float f1, float f2, float f3)
{
	glPushMatrix();
        glColor3f(0,0,0);
		glRotatef(f1,1.0,0.0,0.0);
		glutSolidSphere(0.075*leng, 10,10);
		phalanx1(leng, f2, f3);
	glPopMatrix();
}

void phalanx_thumb2(float leng)
{
	glPushMatrix();
        glColor3f(1.0,1.0,1.0);
		glTranslatef(0.0, 0.2*leng, 0.0);
		glScalef(1.0*leng, leng, 1.0*leng);
		glutSolidCube(0.3);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 0.4*leng, 0.0);
		glutSolidSphere(0.2*leng, 10, 10);
	glPopMatrix();
}

void phalanx_thumb1(float leng, float ang)
{
	// first phalanx
	glPushMatrix();
		glTranslatef(0.0, 0.3*leng, 0.0);
		glScalef(0.66*leng, leng, 0.66*leng);
		glutSolidCube(0.5);
	glPopMatrix();

	// second joint
	glPushMatrix();
        glColor3f(0,0,0);
		glTranslatef(0.0,0.6*leng,0.0);
		glRotatef(ang, 0.0, 0.0, 1.0);
		glutSolidSphere(0.2*leng, 10,10);
		phalanx_thumb2(leng);
	glPopMatrix();
}

/*
 * draws a thumb with a joint.
 * There are small spheres between the phalanxes and at the junction of the finger with the palm
 *
 * leng -	length of the thumb along the Y axis
 *			the dimensions on the XZ plane are proportional to leng
 * ang1 -	rotation angle of the whole thumb around the Z axis
 * ang2 -	rotation angle of the second phalanx with respect to the first one around the Z axis
 */
void thumb(float leng, float ang1, float ang2)
{
	glPushMatrix();
        glColor3f(0,0,0);
		glRotatef(ang1, 1.0,0.0,0.0);
		glutSolidSphere(0.2*leng, 10,10);
		glColor3f(1.0,1.0,1.0);
		phalanx_thumb1(leng, ang2);
	glPopMatrix();
}


void hand() 
{
 glPushMatrix();
  /*glTranslatef(position[0]/5, position[1]/5, -position[2]/5);  
  glRotatef(-angle[0]+90,1,0,0);
  glRotatef(angle[1],0,0,1);
  glRotatef(angle[2]+180,0,1,0);
  */ glPushMatrix();
 	glColor3f(1.0,1.0,1.0); // white palm
	glTranslatef(-0.075*finger_length, 0,0);
    palm2();  // draws the palm
   glPopMatrix();

   glPushMatrix(); 
	glTranslatef(-12,-5,0);
	glRotatef(index[12],0,1,0);
	glRotatef(-40,1,0,0);
	thumb(thumb_length, index[13], index[14]);
   glPopMatrix();

   glPushMatrix();
	glScalef(1,0.9,1);
   	glTranslatef( (palm_size/8 + 0*palm_size/4) - palm_size/2, palm_size/2, 0.0);   
   	finger(finger_length, index[0], index[1], index[2]);  
   glPopMatrix();

   glPushMatrix();
	glColor3f(0.0,0.0,1.0); 
  	glTranslatef((palm_size/8 + 1*palm_size/4) - palm_size/2, palm_size/2, 0.0);   
   	finger(finger_length, index[3], index[4], index[5]);  
   glPopMatrix();

   glPushMatrix();
	glColor3f(1.0,1.0,0.0); 
	glScalef(1,0.95,1);
  	glTranslatef((palm_size/8 + 2*palm_size/4) - palm_size/2, palm_size/2, 0.0);   
   	finger(finger_length, index[6], index[7], index[8]);    
   glPopMatrix();

   glPushMatrix();
	glColor3f(1.0,0.0,1.0); // light blue little finger
	glScalef(1,0.85,1);
  	glTranslatef((palm_size/8 + 3*palm_size/4) - palm_size/2, palm_size/2, 0.0);   // insert transformations
   	finger(finger_length, index[9], index[10], index[11]);    // draws the ndex finger
   glPopMatrix();
glPopMatrix();




glutPostRedisplay();
}


void cube(){
	glPushMatrix();
			glColor3f(1,0,0);
			//glTranslatef(cube_pos[0]/5,cube_pos[1]/5-14,-cube_pos[2]/5);
			///*glRotatef(cube_ang[0],1,0,0);
			/*glRotatef(cube_ang[1],0,1,0);
			glRotatef(cube_ang[2],0,0,1);
			*///glTranslatef(-cube_pos[0]/5,-cube_pos[1]/5,-cube_pos[2]/5);
		glutSolidCube(20);
	glPopMatrix();
}

void plane(){
	glPushMatrix();
		glBegin(GL_QUADS);
			glVertex4f(-1000, 0,-1000, 1);
			glVertex4f(-1000, 0,1000, 1);
			glVertex4f(1000, 0, 1000, 1);
			glVertex4f(1000, 0,-1000, 1);
		glEnd();
	glPopMatrix();
}
/*
 * draws the scene
 */
using namespace std;
void draw()
{
    glClearColor(0.5,0.5,0.5,0.9);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(  0.0, 250 , 400.0,		// eye position
				0.0, 1.0, 0.0,		// center
				0.0, 1.0, 0.0);		// vector UP


	glTranslatef(-1.f, 0.f, -1.f);
	DrawAxes(2.0);
	
	
	/*glRotatef(spin_y, 1.0, 0.0, 0.0);
	glRotatef(spin_x, 0.0, 1.0, 0.0);
	*/
	//phalanx_thumb1(0,0);
	//palm2();
	//plane();
	glTranslatef(cube_pos[0]/5,cube_pos[1]/5-14,-cube_pos[2]/5);
	glTranslatef(position[0]/5, position[1]/5, -position[2]/5);  
  glRotatef(-angle[0]+90,1,0,0);
  glRotatef(angle[1],0,0,1);
  glRotatef(angle[2]+180,0,1,0);
  		
    hand();
	cube();
	//thumb(index[12],index[13],index[14]);
	glFlush();
	glutSwapBuffers();
}

/*
 * invoked when there are no other events to process
 */
void idle() { }

/*
 * initializes the state of OpenGL
 *
 * width, height - size of the OpenGL window
 */
void initGL(int width, int height)
{
	// color and type of the lights
	GLfloat light_ambient_0[] = {0.65, 0.65, 0.65, 1.0};// ambient color of light 0
	GLfloat light_diffuse_0[] = {1.0, 1.0, 1.0, 1.0};	// diffuse color of light 0
	GLfloat light_specular_0[] = {1.0, 1.0, 1.0, 1.0};	// specular color of light 0
	GLfloat light_position_0[] = {5.0, 5.0, 0.0, 0.0};	// position of light 0

	glLightfv (GL_LIGHT0, GL_AMBIENT,	light_ambient_0);
	glLightfv (GL_LIGHT0, GL_DIFFUSE,	light_diffuse_0);
	glLightfv (GL_LIGHT0, GL_SPECULAR,	light_specular_0);
	glLightfv (GL_LIGHT0, GL_POSITION,	light_position_0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	reshape(width, height);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void thumb(int bend){
	if(bend<150){
		index[12]=20;
		index[13]=-50;
		index[14]=-90;
	}

	else if(bend>220){
		index[12]=80;
		index[13]=0;
		index[14]=0;
	}
	else if(bend>196.7){
		index[12]=0.86*bend-109;
		index[13]=0;
		index[14]=0;
	}
	else if(bend>174){
		index[12]=0.86*bend-109;
		index[13]=1.07*bend-210.47;
		index[14]=0;
	}
	else if(bend>150){
		index[12]=0.86*bend-109;
		index[13]=1.07*bend-210.47;
		index[14]=1.93*bend-379.63;
	}
}

void index_f(int bend){
	
	if (bend<248){
		index[0] = -90;
		index[1] = -90;
		index[2] = -90;
	}
	else
		if(bend>400){
			index[0] = 0;
			index[1] = 0;
			index[2] = 0;
		}
		else 
			if (bend>349.33){
				index[0] = 0;
				index[1] = 0;
				index[2] = 0.29*bend-118.42;
			}
			else
				if (bend>324){
					index[0] = 0;
					index[1] = 0.88*bend-310.27;
					index[2] = 0.29*bend-118.42;
				}
				else {
					index[0] = 1.18*bend-383.68;
					index[1] = 0.88*bend-310.27;
					index[2] = 0.29*bend-118.42;
				}
}

void middle(int bend){
	if (bend<253){
		index[3] = -90;
		index[4] = -90;
		index[5] = -90;
	}
	else
		if(bend>382){
			index[3] = 0;
			index[4] = 0;
			index[5] = 0;
		}
		else 
			if (bend>339){
				index[3] = 0;
				index[4] = 0;
				index[5] = 0.35*bend-133.7;
			}
			else
				if (bend>317.5){
					index[3] = 0;
					index[4] = 1.05*bend-354.77;
					index[5] = 0.35*bend-133.7;
				}
				else {
					index[3] = 1.39*bend-443.02;
					index[4] = 1.05*bend-354.77;
					index[5] = 0.35*bend-133.7;;
				}
}


void anular(int bend){
	if (bend<290){
		index[6] = -90;
		index[7] = -90;
		index[8] = -90;
	}
	else
		if(bend>400){
			index[6] = 0;
			index[7] = 0;
			index[8] = 0;
		}
		else 
			if (bend>363.3){
				index[6] = 0;
				index[7] = 0;
				index[8] = 0.41*bend-163.64;
			}
			else
				if (bend>345){
					index[6] = 0;
					index[7] = 1.2*bend-434.22;
					index[8] = 0.41*bend-163.64;
				}
				else {
					index[6] = 1.64*bend-564.55;
					index[7] = 1.2*bend-434.22;
					index[8] = 0.41*bend-163.64;
				}
}

void little(int bend){
	if (bend<320){
		index[9] = -90;
		index[10] = -90;
		index[11] = -90;
	}
	else
		if(bend>498){
			index[9] = 0;
			index[10] = 0;
			index[11] = 0;
		}
		else 
			if (bend>438.67){
				index[9] = 0;
				index[10] = 0;
				index[11] = 0.25*bend-125.9;
			}
			else
				if (bend>409){
					index[9] = 0;
					index[10] = 0.76*bend-332.69;
					index[11] = 0.25*bend-125.9;
				}
				else {
					index[9] = 1.01*bend-413.6;
					index[10] = 0.76*bend-332.69;
					index[11] = 0.25*bend-125.9;
				}
}

/*
 * invoked each 1000/FPS milliseconds.
 * In this function you need to change the value of the parameters for next frame.
 * whenever the state changes, call glutPostRedisplay() to update the visualization.
 *
 * t - is the last parameter of the glutTimerFunc
 */
void animation(int t)
{
	P5State *state = P5_GetStatePointer(0);

	position[0] = state->FilterPos[0];
	position[1] = state->FilterPos[1];
	position[2] = state->FilterPos[2];

	angle[0] = state->FilterPitch;
	angle[1] = state->FilterYaw;
	angle[2] = state->FilterRoll;

	bend[0] = state->FingerAbsolute[0];
	bend[1] = state->FingerAbsolute[1];
	bend[2] = state->FingerAbsolute[2];
	bend[3] = state->FingerAbsolute[3];
	bend[4] = state->FingerAbsolute[4];

	index[12]=20;
	index[13]=-50;
	index[14]=-90;

	thumb(bend[0]);
	index_f(bend[1]);
	middle(bend[2]);
	anular(bend[3]);
	little(bend[4]);

	if(grasp && near_to){
		cube_pos[0]=position[0];
		cube_pos[1]=position[1];
		cube_pos[2]=position[2];
		cube_ang[0]=angle[0];
		cube_ang[1]=angle[1]+70;
		cube_ang[2]=angle[2];
		
	}
	printf(" %f, %f, %f - %f, %f,%f \n", cube_pos[0], cube_pos[1],cube_pos[2], position[0],position[1],position[2]);		
	/*index[1]=-90;
	index[2]=-90;
	index[0]=-90; tutto piegato*/
	glutTimerFunc((int) 1000/FPS, animation, 0);
}

/*
 * initializes GLUT, defines the callback functions, enters the main loop
 *
 * argc : number of command line parameters
 * argv : vector of the command line parameters
 *
 */
int main(int argc, char** argv)
{
	int width = 800;
	int height = 600;
	P5_Init();
	P5_SetUnits(P5_CM);
	P5_SetUnits(P5_DEGREES);
   
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Perspective's GLUT Template");

	// callback functions
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(reshape);
	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glutTimerFunc((int) 1000/FPS, animation, 0);
	glutIgnoreKeyRepeat(false); // process keys held down

	// creates a submenu
	int subMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Do nothing", 0);
	glutAddMenuEntry("Really Quit", 'q');

	// creates the main menu (right button)
	glutCreateMenu(menu);
	glutAddSubMenu("Sub Menu", subMenu);
	glutAddMenuEntry("Quit", 'q');
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// initializes OpenGL
	initGL(width, height);

	// starts the main loop
	glutMainLoop();
	system("PAUSE");
	return 0;
}
