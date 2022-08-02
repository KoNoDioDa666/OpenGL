#pragma once
#ifndef POST_PROCESS_H
#define POST_PROCESS_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"
#include "shader.h"

class PostProcessor
{
public:
	Shader PostProcessingShader;
	Texture2D Texture;
	unsigned int Width, Height;
	bool Confuse, Chaos, Shake;
	PostProcessor(Shader shader, unsigned int width, unsigned int height);
	void BeginRender();
	void EndRender();
	void Render(float time);
private:
	unsigned int msFBO, FBO;
	unsigned int RBO;
	unsigned int VAO;

	void initRenderData();
};

#endif