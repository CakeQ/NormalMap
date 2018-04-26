#pragma once

#include "gl_core_4_3.hpp"
#include "glm.hpp"
#include "gtx\transform.hpp"

#include "Scene.h"
#include "ShaderProgram.h"
#include "vbomesh.h"

#include "vboteapot.h"
#include "vboplane.h"
#include "Texture.h"

#define TWOPI_F 6.2831853f

class NormalScene : public Scene
{
private:
	int width, height;

	ShaderProgram oShaderProgram;

	glm::mat4 ModelMatrix;

	VBOMesh* plane;

	Texture *gTextureDiffuse;
	Texture *gTextureNormal;
	Texture *gTextureHeight;
	Texture *gTextureSpecular;

	float height_scale = 0.1f;

	void ConfigMatrices(QuatCamera camera);

public:
	NormalScene();

	void initScene(QuatCamera camera);
	void Input(int key, int action);
	void update(float t);
	void render(QuatCamera camera);
	void resize(QuatCamera camera, int, int);
};