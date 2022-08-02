#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>

#include "texture.h"
#include "shader.h"

using std::string;
using std::map;

class ResourceManager
{
public:
	static map<string, Shader> Shaders;
	static map<string, Texture2D> Textures;

	static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, string name);
	static Shader GetShader(string name);
	static Texture2D LoadTexture(const char* file, bool alpha, string name);
	static Texture2D GetTexture(string name);

	static void Clear();
private:
	ResourceManager() {}
	static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	static Texture2D loadTextureFromFile(const char* file, bool alpha);
};

#endif