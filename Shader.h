#pragma once

#include <string>
#include <GL/glew.h>
#include <fstream>
#include <iostream>

class Shader
{
public:
	Shader(const char* vShader, const char* fShader);
	Shader() {}

	void CreateShaderProgram(const char* vShader, const char* fShader);
	~Shader();
	std::string loadTextFile(const char *fname);
	GLint getProgramID();
private:
	GLint program;
};

