#include "Shader.h"

Shader::Shader(const char* vShader, const char* fShader)
{
	// (I) create shader program
	GLint value;

	// (I.A) compile fragment shader
	std::string fragtextstr = loadTextFile(fShader);
	const char *fragtext = fragtextstr.c_str();
	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &fragtext, 0);
	glCompileShader(fshader);
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &value);
	if (!value) {
		std::cerr << "fragment shader failed to compile" << std::endl;
		char buffer[1024];
		glGetShaderInfoLog(fshader, 1024, 0, buffer);
		std::cerr << buffer << std::endl;
	}

	// (I.B) compile vertex shader
	std::string verttextstr = loadTextFile(vShader).c_str();
	const char *verttext = verttextstr.c_str();
	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &verttext, 0);
	glCompileShader(vshader);
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &value);
	if (!value) {
		std::cerr << "vertex shader failed to compile" << std::endl;
		char buffer[1024];
		glGetShaderInfoLog(vshader, 1024, 0, buffer);
		std::cerr << buffer << std::endl;
	}

	// (I.C) link shaders
	program = glCreateProgram();
	glAttachShader(program, fshader);
	glAttachShader(program, vshader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &value);
	if (!value) {
		std::cerr << "vertex shader failed to compile" << std::endl;
		char buffer[1024];
		glGetShaderInfoLog(vshader, 1024, 0, buffer);
		std::cerr << buffer << std::endl;
	}
	glDeleteShader(fshader);
	glDeleteShader(vshader);
}

void Shader::CreateShaderProgram(const char* vShader, const char* fShader) {
	// (I) create shader program
	GLint value;

	// (I.A) compile fragment shader
	std::string fragtextstr = loadTextFile(fShader);
	const char *fragtext = fragtextstr.c_str();
	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &fragtext, 0);
	glCompileShader(fshader);
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &value);
	if (!value) {
		std::cerr << "fragment shader failed to compile" << std::endl;
		char buffer[1024];
		glGetShaderInfoLog(fshader, 1024, 0, buffer);
		std::cerr << buffer << std::endl;
	}

	// (I.B) compile vertex shader
	std::string verttextstr = loadTextFile(vShader).c_str();
	const char *verttext = verttextstr.c_str();
	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &verttext, 0);
	glCompileShader(vshader);
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &value);
	if (!value) {
		std::cerr << "vertex shader failed to compile" << std::endl;
		char buffer[1024];
		glGetShaderInfoLog(vshader, 1024, 0, buffer);
		std::cerr << buffer << std::endl;
	}

	// (I.C) link shaders
	program = glCreateProgram();
	glAttachShader(program, fshader);
	glAttachShader(program, vshader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &value);
	if (!value) {
		std::cerr << "vertex shader failed to compile" << std::endl;
		char buffer[1024];
		glGetShaderInfoLog(vshader, 1024, 0, buffer);
		std::cerr << buffer << std::endl;
	}
	glDeleteShader(fshader);
	glDeleteShader(vshader);
}

Shader::~Shader()
{
}

// load a text file into a string
std::string Shader::loadTextFile(const char *fname) {
	std::string out,
		line;
	std::ifstream in(fname);
	getline(in, line);
	while (in) {
		out += line + "\n";
		getline(in, line);
	}
	return out;
}

GLint Shader::getProgramID() { return program; }