#include "NormalScene.h"
#include <iostream>

NormalScene::NormalScene()
{

}

void NormalScene::initScene(QuatCamera camera)
{
	oShaderProgram = ShaderProgram("shaders/normal.vert", "shaders/normal.frag");

	gl::Enable(gl::DEPTH_TEST);

	plane = new VBOPlane(25.0, 25.0, 25, 25);

	Bitmap diffBitmap = Bitmap::bitmapFromFile("textures/cobblesDiffuse.png");
	diffBitmap.flipVertically();
	gTextureDiffuse = new Texture(diffBitmap);

	Bitmap normBitmap = Bitmap::bitmapFromFile("textures/cobblesNormal.png");
	normBitmap.flipVertically();
	gTextureNormal = new Texture(normBitmap);

	Bitmap hghtBitmap = Bitmap::bitmapFromFile("textures/cobblesHeight.png");
	hghtBitmap.flipVertically();
	gTextureHeight = new Texture(hghtBitmap);

	Bitmap specBitmap = Bitmap::bitmapFromFile("textures/cobblesSpecular.png");
	specBitmap.flipVertically();
	gTextureSpecular = new Texture(specBitmap);
}

void NormalScene::Input(int key, int action)
{

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

	//rendering ogre
	ModelMatrix = glm::mat4(1.0f);
	ConfigMatrices(camera);
	plane->render();

	oShaderProgram.Disable();
	std::cout << camera.position().x << ", " << camera.position().y << ", " << camera.position().z << std::endl;
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