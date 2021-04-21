#include "simulator.h"
#include "smoke_sim.h"
#include "camera.h"
#include "util/fps.h"
#include "util/constants.h" 
#include <stdio.h>
#include <cmath> 
#include "util/open_gl_headers.h" 
#include "util/basic_math.h"
#include <string.h>

const int theDim[3] = {32, 32, 1};

// Geometry and whatnot
SmokeSim theSmokeSim;
Camera theCamera;
mmc::FpsTracker theFpsTracker;
int windowSize = 480;

// UI Helpers
int lastX = 0, lastY = 0;
int theMenu = 0;
int theButtonState = 0;
int theModifierState = 0;
bool isRunning = true;

int savedWidth = 0;
int savedHeight = 0;

void initCamera(){
	double w = theDim[0]*theCellSize;
	double h = theDim[1]*theCellSize;
	double d = theDim[2]*theCellSize;
	double angle = 0.5*theCamera.dfltVfov*BasicMath::PI/180.0;
	double dist;
	if (w > h) dist = w*0.5/std::tan(angle);  // aspect is 1, so i can do this
	else dist = h*0.5/std::tan(angle);
	theCamera.dfltEye.set(w*0.5, h*0.5, -(dist+d*0.5));
	theCamera.dfltLook.set(w*0.5, h*0.5, 0.0);
	theCamera.reset();
}

void onMouseMotionCb(int x, int y)
{
	if (theSmokeSim.userInput == 0){ //source
		theSmokeSim.sourcePosX = int(-theDim[0]*1.0/windowSize*x+theDim[0]);
		theSmokeSim.sourcePosY = int(-theDim[1]*1.0/windowSize*y+theDim[1]);
	}else if (theSmokeSim.userInput == 1){//force
		theSmokeSim.forceX = 300*(x - lastX);
		theSmokeSim.forceY = 300*(y - lastY);
	}
	
	
	lastX = x;
	lastY = y;
	glutPostRedisplay();
}

void onMouseCb(int button, int state, int x, int y){
	theButtonState = button;
	theModifierState = glutGetModifiers();
	lastX = x;
	lastY = y;
	
	if (theSmokeSim.userInput == 0){ //source
		theSmokeSim.sourcePosX = int(-theDim[0]/480.*x+theDim[0]);
		theSmokeSim.sourcePosY = int(-theDim[1]/480.*y+theDim[1]);
	}else if (theSmokeSim.userInput == 1){ //force
		theSmokeSim.forcePosX = int(-theDim[0]/480.*x+theDim[0]);
		theSmokeSim.forcePosY = int(-theDim[1]/480.*y+theDim[1]);
	}

	
	glutSetMenu(theMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void onKeyboardCb(unsigned char key, int x, int y)
{
	if (key == ' ') theCamera.reset();
	else if (key == 'v') MACGrid::theDisplayVel = !MACGrid::theDisplayVel;
	else if (key == 'r') {
	 theSmokeSim.setRecording(!theSmokeSim.isRecording(), savedWidth, savedHeight);
	}
	else if (key == '>') isRunning = true;
	else if (key == '=') isRunning = false;
	else if (key == '<') theSmokeSim.reset();
	else if (key == 27) exit(0); // ESC Key
	else if (key == 'f')
		theSmokeSim.userInput = 1;
	else if (key == 's')
		theSmokeSim.userInput = 0;
	
	glutPostRedisplay();
}

void onMenuCb(int value)
{
    switch (value)
    {
    case -1: exit(0);
    case -6:
				theSmokeSim.reset();
        break;
    default: onKeyboardCb(value, 0, 0); break;
    }
}

void onTimerCb(int value)
{
   if (isRunning) {
		 theSmokeSim.step();
   }
   glutTimerFunc(theMillisecondsPerFrame, onTimerCb, 0);
   glutPostRedisplay();
}

void onResizeCb(int width, int height)
{
	
	// Save the width and height:
	savedWidth = width;
	savedHeight = height;
	
   // Update viewport
   glViewport(0, 0, width, height);

   // Update camera projection's aspect ratio
   float vfov, aspect, zNear, zFar;
   theCamera.getProjection(&vfov, &aspect, &zNear, &zFar);
   theCamera.setProjection(vfov, ((GLfloat) width)/height, zNear, zFar);
}

void drawOverlay()
{
  // Draw Overlay
  glColor4f(1.0, 1.0, 1.0, 1.0);
  glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRasterPos2f(0.01, 0.01);
     
	char info[1024];
	
	sprintf(info, "Framerate: %3.1f  |  Frame: %u  |  %s",
					theFpsTracker.fpsAverage(), theSmokeSim.getTotalFrames(),
					theSmokeSim.isRecording()? "Recording..." : "");
 
	for (unsigned int i = 0; i < strlen(info); i++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, info[i]);
	}
  glPopAttrib();
}

void onDrawCb()
{
	// Keep track of time
	theFpsTracker.timestamp();

	// Draw Scene and overlay
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	theCamera.draw();
	theSmokeSim.draw(theCamera);

	drawOverlay();
	glutSwapBuffers();
}

void init(void)
{
    initCamera();
    glClearColor(0.1, 0.1, 0.1, 1.0);

    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glCullFace(GL_BACK);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowSize, windowSize);
	glutInitWindowPosition(100, 100);
	
	glutCreateWindow("Smoke Simulation");

	glutDisplayFunc(onDrawCb);
	glutKeyboardFunc(onKeyboardCb);
	glutMouseFunc(onMouseCb);
	glutMotionFunc(onMouseMotionCb);
	glutTimerFunc(theMillisecondsPerFrame, onTimerCb, 0);
	glutReshapeFunc(onResizeCb);

	int viewMenu = glutCreateMenu(onMenuCb);
	glutAddMenuEntry("Toggle velocities\t'v'", 'v');
	glutAddMenuEntry("Render density as cubes\t'0'", '0');
	glutAddMenuEntry("Render density as sheets\t'1'", '1');
	
	int forceMenu = glutCreateMenu(onMenuCb);
	glutAddMenuEntry("Toggle external force\t'f'", 'f');
	glutAddMenuEntry("Toggle smoke source\t's'", 's');

	theMenu = glutCreateMenu(onMenuCb);
	glutAddMenuEntry("Start\t'>'", '>');
	glutAddMenuEntry("Pause\t'='", '=');
	glutAddMenuEntry("Reset\t'<'", '<');
	glutAddMenuEntry("Reset camera\t' '", ' ');
	glutAddMenuEntry("Record\t'r'", 'r');
	glutAddSubMenu("Display", viewMenu);
	glutAddSubMenu("left click", forceMenu);
	glutAddMenuEntry("_________________", -1);
	glutAddMenuEntry("Exit", 27);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	theSmokeSim.sourcePosX = -100;
	theSmokeSim.sourcePosY = -100;

	init();

	glutMainLoop();
	return 0;
}

