#pragma once

#include "glfw3.h"
#include "QuatCamera.h"

/* Abstract Scene class*/
class Scene
{
public:
	Scene() : m_animate(true)
	{ }
	
    virtual void initScene(QuatCamera camera) = 0; //called at start, use to initalise all objects
	virtual void Input(int key, int action) = 0; //called when keyboard input occurs
    virtual void update( float t ) = 0; //called every frame, use to update animation
    virtual void render(QuatCamera camera) = 0; //use to draw objects to screen
    virtual void resize(QuatCamera camera, int, int) = 0; //called when screen is resized
    
    void animate( bool value ) 
	{ 
		m_animate = value; 
	}

    bool animating() 
	{ 
		return m_animate; 
	}
    
protected:
	bool m_animate;
};
