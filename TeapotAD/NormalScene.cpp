#include "NormalScene.h"
#include <iostream>

NormalScene::NormalScene()
{

}

void NormalScene::initScene(QuatCamera camera)
{
	oShaderProgram = ShaderProgram("shaders/steepparallax.vert", "shaders/steepparallax.frag");

	gl::Enable(gl::DEPTH_TEST);

	plane = new VBOMesh("models/floor.obj", false, true, true);

	Bitmap diffBitmap = Bitmap::bitmapFromFile("textures/cobblesDiffuse.png");
	gTextureDiffuse = new Texture(diffBitmap);

	Bitmap normBitmap = Bitmap::bitmapFromFile("textures/cobblesNormal.png");
	gTextureNormal = new Texture(normBitmap);

	Bitmap hghtBitmap = Bitmap::bitmapFromFile("textures/cobblesHeight.png");
	gTextureHeight = new Texture(hghtBitmap);

	Bitmap specBitmap = Bitmap::bitmapFromFile("textures/cobblesSpecular.png");
	gTextureSpecular = new Texture(specBitmap);
}

void NormalScene::Input(int key, int action)
{
	if (key == GLFW_KEY_SPACE)
	{
		height_scale += 0.1f;
		if (height_scale > 1.0f)
		{
			height_scale = 1.0f;
		}
	}
	if (key == GLFW_KEY_C)
	{
		height_scale -= 0.1f;
		if (height_scale < 0.0f)
		{
			height_scale = 0.0f;
		}
	}

	if (key == GLFW_KEY_1 && action == GLFW_RELEASE)
	{
		oShaderProgram = ShaderProgram("shaders/diffuse.vert", "shaders/diffuse.frag");
	}
	if (key == GLFW_KEY_2 && action == GLFW_RELEASE)
	{
		oShaderProgram = ShaderProgram("shaders/normal.vert", "shaders/normal.frag");
	}
	if (key == GLFW_KEY_3 && action == GLFW_RELEASE)
	{
		oShaderProgram = ShaderProgram("shaders/parallax.vert", "shaders/parallax.frag");
	}
	if (key == GLFW_KEY_4 && action == GLFW_RELEASE)
	{
		oShaderProgram = ShaderProgram("shaders/steepparallax.vert", "shaders/steepparallax.frag");
	}
}

void NormalScene::update(float t)
{

}

void NormalScene::render(QuatCamera camera)
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	oShaderProgram.Use();

	oShaderProgram.setUniform("lightPos", glm::vec3(0, 0, 10));
	oShaderProgram.setUniform("viewPos", camera.position());

	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindTexture(gl::TEXTURE_2D, gTextureDiffuse->object());
	oShaderProgram.setUniform("diffusemap", 0);

	gl::ActiveTexture(gl::TEXTURE1);
	gl::BindTexture(gl::TEXTURE_2D, gTextureNormal->object());
	oShaderProgram.setUniform("normalmap", 1);

	gl::ActiveTexture(gl::TEXTURE2);
	gl::BindTexture(gl::TEXTURE_2D, gTextureHeight->object());
	oShaderProgram.setUniform("depthmap", 2);

	oShaderProgram.setUniform("heightscale", height_scale);

	//rendering plane
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0))); // rotate the quad to show parallax mapping from multiple directions
	ConfigMatrices(camera);
	plane->render();

	oShaderProgram.Disable();
}

void NormalScene::resize(QuatCamera camera, int w, int h)
{
	gl::Viewport(0, 0, w, h);
	width = w;
	height = h;
	camera.setAspectRatio((float)w / h);
}

void NormalScene::ConfigMatrices(QuatCamera camera)
{
	oShaderProgram.setUniform("Model", ModelMatrix);
	oShaderProgram.setUniform("View", camera.view());
	oShaderProgram.setUniform("Projection", camera.projection());
}