WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com


//=============================================================================
// solution.c
//
//Author: Doron Nussbaum (C) 2015 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a. solution framework for assignments
//
//
// Description:
//--------------
// A simple framework for drawing objecs 
//
//
// License
//--------------
//
// Code can be used for instructional and educational purposes.
// Usage of code for other purposes is not allowed without a given permission by the author.
//
//
// Disclaimer
//--------------
//
// The code is provided as is without any warranty

//=============================================================================



/*****************************************************************************/

// DEFINES

#include "Solution.h"

#include "GL/nuss_math.h"
#include <ctime>
#include "time.h"



#define NORMAL_SPEED 0.5f
#define MAX_SPEED 2.0f





/************************************************************/
// DEFINES
#define NO_LIGHT 0
#define POINT_LIGHT 1
#define SPOT_LIGHT  2
#define DIRECTIONAL_LIGHT 3





/************************************************************/
// GLOBALS


Solution *Solution::sol = NULL;

/****************************************************************************/

Solution::Solution() : numFrames(0)

{

}
 
/*************************************************************************/


Solution::~Solution()
{
	printf("\n exiting the progam gracefully\n");

}
/******************************************************************************/


// initializing the opengl functions and windows
int Solution::initOpenGL()
{
	//initialize OpenGL
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(300, 300);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Skybox");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_FRONT);
	glCullFace(GL_BACK);
	glDisable(GL_CULL_FACE);
	glutDisplayFunc(Solution::renderCB);
	glutReshapeFunc(Solution::winResizeCB);
	glutKeyboardFunc(Solution::keyboardCB);
	glutSpecialFunc(Solution::specialKeyboardCB);
	glutTimerFunc(FRAME_TIME, Solution::timerCB, UPDATE_RENDERRED_OBJECTS);

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		printf("Error - %s \n", glewGetErrorString(res));
		return (-1);
	}


	return 0;
}

/******************************************************************************/

// render callback function.  This is a static funcion


void Solution::renderCB()
{

	sol->render();
	
}


/************************************************************/

// keyboard callback function.  This is a static funcion


void Solution::keyboardCB(unsigned char key, int x, int y)
{
	sol->keyboard(key, x, y);
}


/************************************************************/

// special keyboard callback function.  This is a static funcion



void Solution::specialKeyboardCB(int key, int x, int y)
{
	sol->specialKeyboard(key, x, y);
}


/************************************************************/

// window resize callback function.  This is a static funcion



void Solution::winResizeCB(int width, int height)
{
	sol->winResize(width, height);
}

/************************************************************/

// timer  callback function.  This is a static funcion


void Solution::timerCB(int operation)
{

	glutTimerFunc(FRAME_TIME, Solution::timerCB, UPDATE_RENDERRED_OBJECTS);	
	sol->timer(operation);

}


/************************************************************/

// timrt  function.  


int Solution::timer(int operation)
{

	switch (operation) {
	case UPDATE_RENDERRED_OBJECTS:
		updateObjects(numFrames);
		break;
	default:
		break;
	}
	return(0);
}




/******************************************************************************/
// initialization of the solution
int Solution::initSolution()
{
	int rc;
	Vertices vtx;
	Indices ind;
	char* texSky[6] = {
		"TropicalSunnyDayLeft2048.png",
		"TropicalSunnyDayRight2048.png",
		"TropicalSunnyDayUp2048.png",
		"TropicalSunnyDayDown2048.png",
		"TropicalSunnyDayFront2048.png",
		"TropicalSunnyDayBack2048.png" };
	char* texCat[6] = {
			"cat.png",
			"cat.png",
			"cat.png",
			"cat.png",
			"cat.png",
			"cat.png" };



	// create a shader for the sphere
	rc = sphereShader.createShaderProgram("sphereBox.vs", "sphereBox.fs");
	if (rc != 0) {
		printf(" error after generating the spere shader \n");
		rc = 1;
	}

	float scalex = 200, scaley = 200, scalez = 200;

	// create the first object a sphere
	Sphere::createSphere(70, 35, 0, 1, 0, 1, vtx, ind);
	testSphere1.createVAO(sphereShader, vtx, ind);
	testSphere1.setModelPosition(0, 0, 0);
	testSphere1.setModelScale(scalex, scaley, scalez);

	// create a surface

		// create a shader for the sphere
	rc = waveShader.createShaderProgram("waveSurface.vs", "waveSurface.fs");
	if (rc != 0) {
		printf(" error after generating the wave surface shader \n");
		rc = 1;
	}

	Surface::createSurface(50, 50, 0, 1, 0, 1, vtx, ind);
	waveSurface.createVAO(waveShader, vtx, ind);
	waveSurface.setModelPosition(50, 0, 50);
	waveSurface.setModelScale(400, 1,400);
	waveSurface.drawWave = 0;
	waveSurface.renderCircularWave = 0;
	

	// load the texture of the surface
	waveTex.loadTextureImage("blue_liquid_sea.png", GL_TEXTURE_2D);


	// set the camera initial position
	cam.setCamera(Vector3f(0, 150, 500), Vector3f(0, 0, 0), Vector3f(0, 1, 0));
	cam.setPerspectiveView(110, 1, 0.01f, 1000);

	//skybox initialization
	rc = skybox.init("skybox.vs", "skybox.fs");
	if (rc != 0) {
		printf(" error after generating the skybox  shader \n");
		rc = 1;
	}
	//skybox.loadColourTexture();
	skybox.loadTextureImages(texSky);
	//skybox.loadTextureImages(texCat);


	plotWireFrame = 0;
	refractFlag = 0;

	time = 0;
	// speed factor
	factor = 1;

	err:
	return 0;
}


/**********************************************************************/

void Solution::setSolution(Solution * _sol)
{
	Solution::sol = _sol;
}



/************************************************************/

// render function.  


void Solution::render()
{
	

	time++;		// increament the time
	Vector3f viewerPosition = Vector3f(150, 150, 0);
	Vector3f lookAtPoint = Vector3f(150, 10, 100);
	Vector3f upVector = Vector3f(0, 1, 0);
	Matrix4f viewMat, projMat;
	

	viewerPosition = Vector3f(0, 500, 0);
	lookAtPoint = Vector3f(0, 0, 0);
	upVector = Vector3f(0, 0, 1);

	



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (!plotWireFrame) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	skybox.render(cam);


	// render the skybox
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.getTexHandle());

	// render the sphere
	sphereShader.useProgram(1);
	sphereShader.copyIntVectorToShader(&refractFlag, 1, 1, "refractFlag");
	testSphere1.render(sphereShader, cam, time, GL_TEXTURE3 - GL_TEXTURE0);


	// render the surface
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, waveTex.getTexId()); 

	//waveSurface.render(waveShader, cam, time, GL_TEXTURE4 - GL_TEXTURE0);


	glutSwapBuffers();
}


/************************************************************/

// keyboard handling function. 


void Solution::keyboard(unsigned char key, int x, int y)
{
	static int nc = 0;
	nc++;
	switch (key) {
	case 033:
	case 'Q':
	case 'q':
		this->~Solution();
		exit(1);
		break;
	case 'x':	// not used
		break;
	case 'c':	// cirular wave or linear wave
		waveSurface.renderCircularWave = waveSurface.renderCircularWave ? 0 : 1;
		break;
	case 'v':	// not used
		break;
	case 'b':	// toggle drawing  the wave
		waveSurface.drawWave = waveSurface.drawWave ? 0 : 1;
		break;
	case 'w':
		cam.moveForward(NORMAL_SPEED*factor);
		break;
	case 's':
		cam.moveBackward(NORMAL_SPEED*factor);
		break;
	case 'a':
		cam.yaw((float) .2*factor);
		break;
	case 'd':
		cam.yaw((float)-.2*factor);
		break;
	case 'g':
		cam.moveRight(NORMAL_SPEED*factor);
		break;
	case 'G':
		cam.moveLeft(NORMAL_SPEED*factor);
		break;
	case 'z':
		cam.zoomIn();
		break;
	case 'Z':
		cam.zoomOut();
		break;
	case 't':
		refractFlag = (refractFlag == 0) ? 1 : 0;
		break;
	case 'p':
		plotWireFrame = plotWireFrame ? 0 : 1;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		factor = (float) (key - '0');
		break;
	}


}


/************************************************************/

// special keyboard handling  function.  



void Solution::specialKeyboard(int key, int x, int y)
{
	switch (key) {
	case 033:
	case 'Q':
	case 'q':
		exit(1);
		break;
	case GLUT_KEY_LEFT:
		cam.roll((float) .2*factor);
		break;
	case GLUT_KEY_UP:
		cam.pitch((float) .2*factor);
		break;
	case GLUT_KEY_RIGHT:
		cam.roll((float)-.2*factor);
		break;
	case GLUT_KEY_DOWN:
		cam.pitch((float)-.2*factor);
		break;
	}
}


/************************************************************/

// window resize handling function.  



void Solution::winResize(int width, int height)
{

	glViewport(0, 0, width, height);

}

/***********************************************************/
// update the state of the objects

int Solution::updateObjects(int numFrames)
{
	// recall that this will be carried out in the model space
	//testSphere1.incrementRotations(0, 0, 0.5);

	glutPostRedisplay();
	return 0;
}




/*************************************************************************************************************/

int Solution::printOpenGLError(int errorCode)
{
	switch (errorCode) {
	case GL_INVALID_VALUE:
		printf("GL_INVALID_VALUE is generated if program is not a value generated by OpenGL.\n");
		break;
	case GL_INVALID_OPERATION:
		printf("GL_INVALID_OPERATION is generated if program is not a program object. or \n");
		printf("GL_INVALID_OPERATION is generated if program has not been successfully linked. or \n");
		printf("GL_INVALID_OPERATION is generated if location does not correspond to a valid uniform variable location for the specified program object.");
		break;
	default:
		printf("openGL unknown error \n");
	}

	return 0;
}
