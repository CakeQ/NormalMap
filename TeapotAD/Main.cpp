#include "gl_core_4_3.hpp"
#include "glfw3.h"

#include "Scene.h"
#include "NormalScene.h"
#include "QuatCamera.h"

#include <string>
using std::string;

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

GLFWwindow *window;
NormalScene *normalScene;
QuatCamera camera;

//To keep track of cursor location
double lastCursorPositionX, lastCursorPositionY, cursorPositionX, cursorPositionY;

//////////////////////////////////////////////////////////
////  Key press callback /////////////////////////////////
//////////////////////////////////////////////////////////
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		if (normalScene)
		{
			normalScene->animate(!(normalScene->animating()));
		}
	}
	if (key == 'R' && action == GLFW_RELEASE)
	{
		camera.reset();
	}
	
	normalScene->Input(key, action);
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Callback function when mouse wheel is scrolled
/////////////////////////////////////////////////////////////////////////////////////////////
void scroll_callback(GLFWwindow *window, double x, double y)
{
	camera.zoom((float)y * 0.5f);
}

////////////////////////////////////////////////////////
//////  Create the scene and initialise ////////////////
////////////////////////////////////////////////////////
void initializeGL() 
{
	gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	lastCursorPositionX = 0.0;
	lastCursorPositionY = 0.0;
	cursorPositionX = 0.0;
	cursorPositionY = 0.0;

	camera.setPosition(glm::vec3(0.0f, 0.0f, 1.0f));

	normalScene = new NormalScene();
	normalScene->initScene(camera);
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Update
/////////////////////////////////////////////////////////////////////////////////////////////
void update(float t)
{
	//Get the current cursor position
	glfwGetCursorPos(window, &cursorPositionX, &cursorPositionY);

	//See how much the cursor has moved
	float deltaX = (float)(lastCursorPositionX - cursorPositionX);
	float deltaY = (float)(lastCursorPositionY - cursorPositionY);

	//Using a different way (i.e. instead of callback) to check for LEFT mouse button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
	{
		//std::cout << "Left button \n";
		//Rotate the camera. The 0.001f is a velocity mofifier to make the speed sensible

		//	std::cout <<"deltaX " << deltaX << " deltaY " << deltaY << "\n";

		camera.rotate(deltaX*ROTATE_VELOCITY, deltaY * ROTATE_VELOCITY);
	}

	//Using a different way (i.e. instead of callback) to check for RIGHT mouse button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		//std::cout << "Right button \n";
		//Rotate the camera. The 0.01f is a velocity mofifier to make the speed sensible
		camera.pan(deltaX*MOVE_VELOCITY, deltaY * MOVE_VELOCITY);

	}
	//To adjust Roll with MIDDLE mouse button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE))
	{
		camera.roll(deltaX * ROTATE_VELOCITY);
	}

	//Store the current cursor position
	lastCursorPositionX = cursorPositionX;
	lastCursorPositionY = cursorPositionY;

}

////////////////////////////////////////////////////////
/////// Main loop  /////////////////////////////////////
////////////////////////////////////////////////////////
void mainLoop() {
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) 
	{
		//GLUtils::checkForOpenGLError(__FILE__,__LINE__);
		update((float)glfwGetTime());
		normalScene->render(camera);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

///////////////////////////////////////////////////////
//// resize ///////////////////////////////////////////
///////////////////////////////////////////////////////
void resizeGL(QuatCamera camera, int w, int h) 
{
	normalScene->resize(camera, w, h);
}

///////////////////////////////////////////////////////
///////  Main  ////////////////////////////////////////
///////////////////////////////////////////////////////
int main(int argc, char *argv[])
{

	// Initialize GLFW
	if (!glfwInit()) exit(EXIT_FAILURE);

	// Select OpenGL 4.3 with a forward compatible core profile.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, TRUE);

	// Open the window
	string title = "Lab 16 - Normal Mapping";
	window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, title.c_str(), NULL, NULL);
	if (!window) 
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	//Scroll callback
	glfwSetScrollCallback(window, scroll_callback);//Set callback

	// Load the OpenGL functions.
	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();

	if (!didLoad) 
	{
		//Claen up and abort
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Initialization
	initializeGL();
	resizeGL(camera, WIN_WIDTH, WIN_HEIGHT);

	// Enter the main loop
	mainLoop();

	// Close window and terminate GLFW
	glfwTerminate();

	// Exit program
	exit(EXIT_SUCCESS);
}