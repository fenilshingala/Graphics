// cs541texture-template.cpp
// -- template for assignment #4 (textures)
// cs541 10/18
//
// To compile from Visual Studio 2015 command prompt:
//    cl /EHsc cs541texture-template.cpp Affine.cpp Camera.cpp Plane.cpp Sphere.cpp Torus.cpp Shader.cpp opengl32.lib glew32.lib sdl2.lib sdl2main.lib /link /subsystem:console
//     
// To compile from Linux command line:
//    g++ cs541texture-template.cpp Affine3D.cpp Plane.cpp
//        -lGL -lGLEW -lSDL2

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Affine.h"
#include "Camera.h"
#include "Plane.h"
#include "Torus.h"
#include "Sphere.h"
using namespace std;

#include "Shader.h"

const int MESH_SIZE = 50;
const float THICKNESS = 0.5f;
const float PI = 4.0f*atan(1.0f);
const glm::vec4 O(0.0f, 0.0f, 0.0f, 1.0f),
EX(1.0f, 0.0f, 0.0f, 0.0f),
EY(0.0f, 1.0f, 0.0f, 0.0f),
EZ(0.0f, 0.0f, 1.0f, 0.0f);
glm::vec4 eye = O + 15.0f*EZ + 5.0f*EY;
glm::vec4 look(0.2f, -0.5f, -1.0f, 0.0f);

glm::vec4 LIGHT_POSITION(0.0f, 0.0f, -5.0f, 0.0f); // OVERRIDE IN MAIN

glm::vec4 look2(0.0f, 0.0f, -1.0f, 0.0f);
glm::vec4 eye2 = LIGHT_POSITION;

glm::vec4 currentEye = eye;
glm::vec4 currentLook = look;

#define NO_OF_OBJECTS 7
#define NO_OF_SHADERS 3


//My Temp Variables
//unsigned int pos, texture/*uniform*/, textID, textBuffer;
//unsigned int depthBuffer;
//unsigned int depthMap;
//unsigned int modelingMat;
//Shader depthPass; 
//Shader defaultTexture; 
//unsigned int vao[3], normal[3], face[3];
//int faceCount;
//float aspect = 1.0f, fov = 80.0f, near = 1.0f;
//
//unsigned char* loadBitmapFile(const char *fname, int *width, int *height);
//
//void initShadowData() {
//
//	depthPass.CreateShaderProgram("shadow.vert", "shadow.frag");
//	defaultTexture.CreateShaderProgram("default_texture.vert", "default_texture.frag");
//
//	//create depth buffer and bind
//	glGenFramebuffers(1, &depthBuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, depthBuffer);
//
//	glGenTextures(1, &depthMap);
//	glBindTexture(GL_TEXTURE_2D, depthMap);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//
//	int width, height;
//	unsigned char *rgbdata = loadBitmapFile("spherical.bmp", &width, &height);
//
//	glGenTextures(1, &textID);
//	glBindTexture(GL_TEXTURE_2D, textID);
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, rgbdata);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//
//
//	// creation of plane
//	Plane plane(MESH_SIZE);
//	faceCount = plane.faceCount();
//
//
//	// (III.A) vertex buffer //////////////////////////////////////////
//	glGenBuffers(1, &vao[0]);
//	glBindBuffer(GL_ARRAY_BUFFER, vao[0]);
//	int vertex_buffer_size = sizeof(glm::vec4)*plane.vertexCount();
//	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, plane.vertexArray(), GL_STATIC_DRAW);
//
//	// (III.B) normal buffer
//	glGenBuffers(1, &normal[0]);
//	glBindBuffer(GL_ARRAY_BUFFER, normal[0]);
//	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, plane.normalArray(), GL_STATIC_DRAW);
//
//	// (III.C) face buffer
//	glGenBuffers(1, &face[0]);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face[0]);
//	int face_buffer_size = sizeof(Mesh3D::Face)*faceCount;
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_buffer_size, plane.faceArray(), GL_STATIC_DRAW);
//
//	// (III.D) texture coordinate buffer
//	glGenBuffers(1, &textBuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, textBuffer);
//	float* texcoord = new float[2 * plane.vertexCount()];
//	glm::mat4 Std2Unit = cs541::scale(0.5f, 0.5f, 1)
//		* cs541::translate(glm::vec4(1, 1, 0, 0));
//	for (int i = 0; i < plane.vertexCount(); ++i) {
//		glm::vec4 uv = Std2Unit * plane.vertexArray()[i];
//		texcoord[2 * i + 0] = uv[0];
//		texcoord[2 * i + 1] = uv[1];
//	}
//	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float)*plane.vertexCount(), texcoord, GL_STATIC_DRAW);
//	delete[] texcoord;
//
//
//
//
//	//creation of sphere
//	Sphere sphere(MESH_SIZE);
//	faceCount = sphere.faceCount();
//
//	// (III.A) vertex buffer //////////////////////////////////////////
//	glGenBuffers(1, &vao[1]);
//	glBindBuffer(GL_ARRAY_BUFFER, vao[1]);
//	vertex_buffer_size = sizeof(glm::vec4)*sphere.vertexCount();
//	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, sphere.vertexArray(), GL_STATIC_DRAW);
//
//	// (III.B) normal buffer
//	glGenBuffers(1, &normal[1]);
//	glBindBuffer(GL_ARRAY_BUFFER, normal[1]);
//	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, sphere.normalArray(), GL_STATIC_DRAW);
//
//	// (III.C) face buffer
//	glGenBuffers(1, &face[1]);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face[1]);
//	face_buffer_size = sizeof(Mesh3D::Face)*faceCount;
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_buffer_size, sphere.faceArray(), GL_STATIC_DRAW);
//
//	// (IV) enable use of z-buffer
//	//glEnable(GL_DEPTH_TEST);
//	
//	
//	
//	
//	
//	
//	//creation torus
//
//	Torus torus(THICKNESS, MESH_SIZE);
//	faceCount = torus.faceCount();
//
//	// (III.A) vertex buffer //////////////////////////////////////////  INDEX 2
//	glGenBuffers(1, &vao[2]);
//	glBindBuffer(GL_ARRAY_BUFFER, vao[2]);
//	vertex_buffer_size = sizeof(glm::vec4)*torus.vertexCount();
//	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, torus.vertexArray(), GL_STATIC_DRAW);
//
//	// (III.B) normal buffer
//	glGenBuffers(1, &normal[2]);
//	glBindBuffer(GL_ARRAY_BUFFER, normal[2]);
//	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, torus.normalArray(), GL_STATIC_DRAW);
//
//	// (III.C) face buffer
//	glGenBuffers(1, &face[2]);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face[2]);
//	face_buffer_size = sizeof(Mesh3D::Face)*faceCount;
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_buffer_size, torus.faceArray(), GL_STATIC_DRAW);
//
//	// (IV) enable use of z-buffer
//	//glEnable(GL_DEPTH_TEST);
//}
//
//void drawDepthMap();
//
//void shadowPass(float dt) {
//
//	int width = 500;
//
//	//glBindFramebuffer(GL_FRAMEBUFFER, depthBuffer);
//	glUseProgram(depthPass.getProgramID());
//
//	glEnable(GL_DEPTH_TEST);
//	//clear
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
//	//set viewport
//	glViewport(0, 0, width, width);
//	//bind fbo
//
//	pos = glGetAttribLocation(depthPass.getProgramID(), "position");
//	texture = glGetAttribLocation(defaultTexture.getProgramID(), "texture_coord");
//
//	float color[3][4] = {
//			{ 1,0,0,1 },
//			{ 0,1,0,1},
//			{ 0,0,1,1} };
//	
//	//render scene
//	for (int i = 0; i < 3; ++i) {
//
//		//bind uniforms
//		glUniform4fv(20, 1, color[i]);
//		glm::mat4 T = cs541::translate(glm::vec4(5*(i-1), 0, -4, 0));
//		
//		
//		glm::mat4 S = cs541::scale(2.5f);
//		if (0 == i) {
//			T = cs541::translate(glm::vec4(5 * i, 0, -18, 0));
//			S = cs541::scale(12.5f);
//		}
//		glm::mat4 M = T * S;
//		glUniformMatrix4fv(14, 1, false, &M[0][0]);
//
//
//		glm::mat4 V = cs541::view(eye, look, EY);
//		glUniformMatrix4fv(13, 1, false, &V[0][0]);
//
//
//		glm::mat4 P = cs541::perspective(fov, aspect, near);
//		glUniformMatrix4fv(12, 1, false, &P[0][0]);
//
//
//		//glUseProgram(depthPass.getProgramID());
//		glBindBuffer(GL_ARRAY_BUFFER, vao[i]);
//		glVertexAttribPointer(pos, 4, GL_FLOAT, false, 0, 0);
//		glEnableVertexAttribArray(pos);
//
//		glBindBuffer(GL_ARRAY_BUFFER, textBuffer);
//		glVertexAttribPointer(texture, 2, GL_FLOAT, false, 0, 0);
//		glEnableVertexAttribArray(texture);
//
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face[i]);
//		glDrawElements(GL_TRIANGLES, 3 * faceCount, GL_UNSIGNED_INT, 0);
//	
//	}
//
//	//unbind fbo
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//	//drawDepthMap();
//}
//
////14 m
////13 v
////12 p
//void drawDepthMap() {
//
//	glUseProgram(defaultTexture.getProgramID());
//
//	//clear
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glClearColor(1, 1, 1, 1);
//
//	//viewport
//	glViewport(0, 0, 500, 500);
//
//	//bind texture
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, depthMap);
//	glUniform1i(0, 0);
//
//	//draw
//	pos = glGetAttribLocation(defaultTexture.getProgramID(), "position");
//	texture = glGetAttribLocation(defaultTexture.getProgramID(), "texture_coord");
//
//	float color[3][4] = {
//			{ 1,0,0,1 },
//			{ 1,1,0,1},
//			{ 1,0,1,1} };
//
//	//render scene
//	for (int i = 0; i < 1; ++i) {
//
//		//bind uniforms
//		glUniform4fv(20, 1, color[i]);
//		glm::mat4 T = cs541::translate(glm::vec4(5 * i, 0, -4, 0));
//
//
//		glm::mat4 S = cs541::scale(2.5f);
//		if (0 == i) {
//			T = cs541::translate(glm::vec4(5 * i, 0, -18, 0));
//			S = cs541::scale(12.5f);
//		}
//		glm::mat4 M = T * S;
//		glUniformMatrix4fv(14, 1, false, &M[0][0]);
//
//
//		glm::mat4 V = cs541::view(eye, look, EY);
//		glUniformMatrix4fv(13, 1, false, &V[0][0]);
//
//
//		glm::mat4 P = cs541::perspective(fov, aspect, near);
//		glUniformMatrix4fv(12, 1, false, &P[0][0]);
//
//
//		glBindBuffer(GL_ARRAY_BUFFER, vao[i]);
//		glVertexAttribPointer(pos, 4, GL_FLOAT, false, 0, 0);
//		glEnableVertexAttribArray(pos);
//
//		glBindBuffer(GL_ARRAY_BUFFER, textBuffer);
//		glVertexAttribPointer(texture, 2, GL_FLOAT, false, 0, 0);
//		glEnableVertexAttribArray(texture);
//
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face[i]);
//		glDrawElements(GL_TRIANGLES, 3 * faceCount, GL_UNSIGNED_INT, 0);
//	}
//
//
//}
//

// load a text file into a string
string loadTextFile(const char *fname) {
	string out,
		line;
	ifstream in(fname);
	getline(in, line);
	while (in) {
		out += line + "\n";
		getline(in, line);
	}
	return out;
}


// read a 24-bit color bitmap image file
//   Note: caller is responsible for deallocating the
//         RGB data
unsigned char* loadBitmapFile(const char *fname, int *width, int *height) {
	fstream in(fname, ios_base::in | ios_base::binary);
	char header[38];
	in.read(header, 38);
	unsigned offset = *reinterpret_cast<unsigned*>(header + 10);
	int W = *reinterpret_cast<int*>(header + 18),
		H = *reinterpret_cast<int*>(header + 22),
		S = 3 * W;
	S += (4 - S % 4) % 4;
	int size = S * H;
	in.seekg(offset, ios_base::beg);
	unsigned char *data = new unsigned char[size];
	in.read(reinterpret_cast<char*>(data), size);
	if (!in) {
		delete[] data;
		return 0;
	}

	for (int j = 0; j < H; ++j) {
		for (int i = 0; i < W; ++i) {
			int index = S * j + 3 * i;
			swap(data[index + 0], data[index + 2]);
		}
	}

	*width = W;
	*height = H;
	return data;
}


/////////////////////////////////////////////////////////////////
class Client {
public:
	Client(void);
	~Client(void);
	void draw(double dt);
	void keypress(SDL_Keycode kc);
	void resize(int W, int H);
	void mousedrag(int x, int y, bool lbutton);
	void RenderObject();
private:
	GLuint vertex_buffer[NO_OF_OBJECTS],
		   normal_buffer[NO_OF_OBJECTS],
		   face_buffer[NO_OF_OBJECTS],
		   frame_buffer,
		   depth_texture_buffer,
		   *texcoord_buffer,
		   *texture_buffer;
	GLint  *program,
		   *aposition,
		   *anormal,
		   *upersp_matrix,
		   *uview_matrix,
		   *umodel_matrix,
		   *unormal_matrix,
		   *ulight_position,
		   *ulight_color,
		   *ustd2unit_matrix,
		   uTiled,
		   *ulight_view_matrix;

	GLint atexture_coord,
		udiffuse_color,
		ucamera_position;

	int face_count;
	float time;
	float aspect;
	float fov, near, far;
};


Client::Client(void) {

	/*initShadowData();
	return;*/
	texcoord_buffer = new GLuint[NO_OF_SHADERS];
	texture_buffer = new GLuint[NO_OF_SHADERS];

	program = new GLint[NO_OF_SHADERS];
	aposition = new GLint[NO_OF_SHADERS];
	anormal = new GLint[NO_OF_SHADERS];
	upersp_matrix = new GLint[NO_OF_SHADERS];
	uview_matrix = new GLint[NO_OF_SHADERS];
	umodel_matrix = new GLint[NO_OF_SHADERS];
	unormal_matrix = new GLint[NO_OF_SHADERS];
	ulight_position = new GLint[NO_OF_SHADERS];
	ulight_color = new GLint[NO_OF_SHADERS];
	ustd2unit_matrix = new GLint[NO_OF_SHADERS];
	ulight_view_matrix = new GLint[NO_OF_SHADERS];

	//////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////// SHADOW ///////////////////////////////////////////////

	Shader* shader3 = new Shader("shadow.vert", "shadow.frag");
	program[2] = shader3->getProgramID();

	// shader attribute and uniform variable locations
	aposition[2] = glGetAttribLocation(program[2], "position");
	upersp_matrix[2] = glGetUniformLocation(program[2], "persp_matrix");
	ulight_view_matrix[2] = glGetUniformLocation(program[2], "view_matrix");
	umodel_matrix[2] = glGetUniformLocation(program[2], "model_matrix");

	glGenFramebuffers(1, &frame_buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);

	glGenTextures(1, &depth_texture_buffer);
	glBindTexture(GL_TEXTURE_2D, depth_texture_buffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glReadBuffer(GL_NONE);
	glDrawBuffer(GL_NONE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture_buffer, 0);

	//unsigned int rbo;
	//glGenRenderbuffers(1, &rbo);
	//glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	//glBindRenderbuffer(GL_RENDERBUFFER, 0);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);


	/*glReadBuffer(GL_NONE);
	glDrawBuffer(GL_NONE);*/

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "frame buffer failure" << endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	/////////////////////////////////////// SHADOW END ///////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////




	//////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////// TEXTURE SHADER ///////////////////////////////////////////

	Shader* shader1 = new Shader("diffuse_texture.vert", "diffuse_texture.frag");
	program[0] = shader1->getProgramID();

	// (II) get shader variable locations
	aposition[0] = glGetAttribLocation(program[0], "position");
	anormal[0] = glGetAttribLocation(program[0], "normal");
	atexture_coord = glGetAttribLocation(program[0], "texture_coord");
	upersp_matrix[0] = glGetUniformLocation(program[0], "persp_matrix");
	uview_matrix[0] = glGetUniformLocation(program[0], "view_matrix");
	umodel_matrix[0] = glGetUniformLocation(program[0], "model_matrix");
	unormal_matrix[0] = glGetUniformLocation(program[0], "normal_matrix");
	ulight_position[0] = glGetUniformLocation(program[0], "light_position");
	ulight_color[0] = glGetUniformLocation(program[0], "light_color");
	uTiled = glGetUniformLocation(program[0], "tile");
	ustd2unit_matrix[0] = glGetUniformLocation(program[0], "std2unit_matrix");
	ulight_view_matrix[0] = glGetUniformLocation(program[0], "light_view_matrix");

	//////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////// SKY DOME ///////////////////////////////////////////

	// (III) upload plane mesh to GPU
	Plane plane(MESH_SIZE);
	face_count = plane.faceCount();

	// (III.D) texture coordinate buffer
	glGenBuffers(1, &texcoord_buffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffer[0]);
	float *texcoord = new float[2 * plane.vertexCount()];
	glm::mat4 Std2Unit = cs541::scale(0.5f, 0.5f, 1)
		* cs541::translate(glm::vec4(1, 1, 0, 0));
	for (int i = 0; i < plane.vertexCount(); ++i) {
		glm::vec4 uv = Std2Unit * plane.vertexArray()[i];
		texcoord[2 * i + 0] = uv[0];
		texcoord[2 * i + 1] = uv[1];
	}
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float)*plane.vertexCount(), texcoord, GL_STATIC_DRAW);
	delete[] texcoord;

	glm::mat4 n = cs541::scale(PI, PI / 2, 1)
		* cs541::translate(glm::vec4(1, 1, 0, 0))
		* cs541::scale(1, -1, 1);
	for (int i = 0; i < plane.vertexCount(); ++i) {
		plane.vertexArray()[i] = n * plane.vertexArray()[i];

		float theta = plane.vertexArray()[i].y;
		float phi = plane.vertexArray()[i].x;

		plane.vertexArray()[i].x = sinf(theta) * sinf(phi);
		plane.vertexArray()[i].y = cosf(theta);
		plane.vertexArray()[i].z = -sinf(theta) * cosf(phi);

		plane.normalArray()[i] = plane.vertexArray()[i];
	}

	// (III.A) vertex buffer //////////////////////////////////////////  INDEX 0
	glGenBuffers(1, &vertex_buffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[0]);
	int vertex_buffer_size = sizeof(glm::vec4)*plane.vertexCount();
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, plane.vertexArray(), GL_STATIC_DRAW);

	// (III.B) normal buffer
	glGenBuffers(1, &normal_buffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, plane.normalArray(), GL_STATIC_DRAW);

	// (III.C) face buffer
	glGenBuffers(1, &face_buffer[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face_buffer[0]);
	int face_buffer_size = sizeof(Mesh3D::Face)*face_count;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_buffer_size, plane.faceArray(), GL_STATIC_DRAW);

	glActiveTexture(GL_TEXTURE0);
	GLint location = glGetUniformLocation(program[0], "usampler");
	glUniform1i(location, 0);

	// (IV) upload texture to GPU
	int width, height;
	unsigned char *rgbdata = loadBitmapFile("spherical.bmp", &width, &height);

	glGenTextures(1, &texture_buffer[0]);
	glBindTexture(GL_TEXTURE_2D, texture_buffer[0]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, rgbdata);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// (IV) upload texture to GPU
	rgbdata = loadBitmapFile("bitmap.bmp", &width, &height);
	glGenTextures(1, &texture_buffer[1]);
	glBindTexture(GL_TEXTURE_2D, texture_buffer[1]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, rgbdata);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depth_texture_buffer);
	location = glGetUniformLocation(program[0], "shadow_sampler");
	glUniform1i(location, 1);

	// (V) enable use of z-buffer
	glEnable(GL_DEPTH_TEST);


	////////////////////////////////////////// 2ND OBJECT ////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////

	// (III) upload plane mesh to GPU
	Plane plane_2(MESH_SIZE);
	face_count = plane_2.faceCount();

	// (III.D) texture coordinate buffer
	glGenBuffers(1, &texcoord_buffer[1]);
	glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffer[1]);
	texcoord = new float[2 * plane_2.vertexCount()];
	Std2Unit = cs541::scale(0.5f, 0.5f, 1)
		* cs541::translate(glm::vec4(1, 1, 0, 0));
	for (int i = 0; i < plane_2.vertexCount(); ++i) {
		glm::vec4 uv = Std2Unit * plane_2.vertexArray()[i];
		texcoord[2 * i + 0] = uv[0];
		texcoord[2 * i + 1] = uv[1];
	}
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float)*plane_2.vertexCount(), texcoord, GL_STATIC_DRAW);
	delete[] texcoord;

	n = cs541::scale(PI, PI / 2, 1)
		* cs541::translate(glm::vec4(1, 1, 0, 0))
		* cs541::scale(1, -1, 1);
	for (int i = 0; i < plane_2.vertexCount(); ++i) {
		plane_2.vertexArray()[i] = n * plane_2.vertexArray()[i];

		float theta = plane_2.vertexArray()[i].y;
		float phi = plane_2.vertexArray()[i].x;

		plane_2.vertexArray()[i].x = sinf(theta) * cosf(phi);
		plane_2.vertexArray()[i].y = cosf(theta);
		plane_2.vertexArray()[i].z = -sinf(theta) * sinf(phi);

		plane_2.normalArray()[i] = plane_2.vertexArray()[i];
	}

	// (III.A) vertex buffer //////////////////////////////////////////  INDEX 1
	glGenBuffers(1, &vertex_buffer[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[1]);
	vertex_buffer_size = sizeof(glm::vec4)*plane_2.vertexCount();
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, plane_2.vertexArray(), GL_STATIC_DRAW);

	// (III.B) normal buffer
	glGenBuffers(1, &normal_buffer[1]);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, plane_2.normalArray(), GL_STATIC_DRAW);

	// (III.C) face buffer
	glGenBuffers(1, &face_buffer[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face_buffer[1]);
	face_buffer_size = sizeof(Mesh3D::Face)*face_count;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_buffer_size, plane_2.faceArray(), GL_STATIC_DRAW);

	// (V) enable use of z-buffer
	glEnable(GL_DEPTH_TEST);

	//////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////// END //////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////// NORMAL SHADER ///////////////////////////////////////////

	Shader* shader2 = new Shader("solid.vert", "solid.frag");
	program[1] = shader2->getProgramID();

	// shader attribute and uniform variable locations
	aposition[1] = glGetAttribLocation(program[1], "position");
	anormal[1] = glGetAttribLocation(program[1], "normal");
	upersp_matrix[1] = glGetUniformLocation(program[1], "persp_matrix");
	uview_matrix[1] = glGetUniformLocation(program[1], "view_matrix");
	umodel_matrix[1] = glGetUniformLocation(program[1], "model_matrix");
	unormal_matrix[1] = glGetUniformLocation(program[1], "normal_matrix");
	ulight_position[1] = glGetUniformLocation(program[1], "light_position");
	ulight_color[1] = glGetUniformLocation(program[1], "light_color");
	udiffuse_color = glGetUniformLocation(program[1], "diffuse_color");
	ucamera_position = glGetUniformLocation(program[1], "camera_position");
	ustd2unit_matrix[1] = glGetUniformLocation(program[1], "std2unit_matrix");
	ulight_view_matrix[1] = glGetUniformLocation(program[1], "light_view_matrix");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depth_texture_buffer);
	location = glGetUniformLocation(program[1], "shadow_sampler");
	glUniform1i(location, 0);

	// ------------------------------------------------------------------------------------------------
	// (III) upload torus mesh to GPU
	Torus torus(THICKNESS, MESH_SIZE);
	face_count = torus.faceCount();

	// (III.A) vertex buffer //////////////////////////////////////////  INDEX 2
	glGenBuffers(1, &vertex_buffer[2]);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[2]);
	vertex_buffer_size = sizeof(glm::vec4)*torus.vertexCount();
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, torus.vertexArray(), GL_STATIC_DRAW);

	// (III.B) normal buffer
	glGenBuffers(1, &normal_buffer[2]);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer[2]);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, torus.normalArray(), GL_STATIC_DRAW);

	// (III.C) face buffer
	glGenBuffers(1, &face_buffer[2]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face_buffer[2]);
	face_buffer_size = sizeof(Mesh3D::Face)*face_count;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_buffer_size, torus.faceArray(), GL_STATIC_DRAW);

	// (IV) enable use of z-buffer
	//glEnable(GL_DEPTH_TEST);
	
	// ------------------------------------------------------------------------------------------------


	Plane texturedPlane(MESH_SIZE);
	face_count = texturedPlane.faceCount();

	// (III.A) vertex buffer //////////////////////////////////////////  INDEX 4
	glGenBuffers(1, &vertex_buffer[4]);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[4]);
	vertex_buffer_size = sizeof(glm::vec4)*texturedPlane.vertexCount();
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, texturedPlane.vertexArray(), GL_STATIC_DRAW);

	// (III.B) normal buffer
	glGenBuffers(1, &normal_buffer[4]);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer[4]);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, texturedPlane.normalArray(), GL_STATIC_DRAW);

	// (III.C) face buffer
	glGenBuffers(1, &face_buffer[4]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face_buffer[4]);
	face_buffer_size = sizeof(Mesh3D::Face)*face_count;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_buffer_size, texturedPlane.faceArray(), GL_STATIC_DRAW);

	// (IV) enable use of z-buffer
	//glEnable(GL_DEPTH_TEST);

	// ------------------------------------------------------------------------------------------------


	Sphere sphere(MESH_SIZE);
	face_count = sphere.faceCount();

	// (III.A) vertex buffer //////////////////////////////////////////  INDEX 3	LIGHT SOURCE
	glGenBuffers(1, &vertex_buffer[3]);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[3]);
	vertex_buffer_size = sizeof(glm::vec4)*sphere.vertexCount();
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, sphere.vertexArray(), GL_STATIC_DRAW);

	// (III.B) normal buffer
	glGenBuffers(1, &normal_buffer[3]);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer[3]);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, sphere.normalArray(), GL_STATIC_DRAW);

	// (III.C) face buffer
	glGenBuffers(1, &face_buffer[3]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face_buffer[3]);
	face_buffer_size = sizeof(Mesh3D::Face)*face_count;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_buffer_size, sphere.faceArray(), GL_STATIC_DRAW);

	// (IV) enable use of z-buffer
	glEnable(GL_DEPTH_TEST);

	// ------------------------------------------------------------------------------------------------


  //////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////// END //////////////////////////////////////////////////

	aspect = 1.0f;
	fov = 80.0f;
	near = 1.0f;
	far = 100.0f;

	time = 0;
}


Client::~Client(void) {
	// delete the shader program
	return;
	glUseProgram(0);
	for (int i = 0; i < NO_OF_OBJECTS; ++i) {
		// delete the vertex, normal, texture coordinate, and face buffers
		glDeleteBuffers(1, &face_buffer[i]);
		glDeleteBuffers(1, &normal_buffer[i]);
		glDeleteBuffers(1, &vertex_buffer[i]);
	}

	for (int i = 0; i < NO_OF_SHADERS; ++i) {
		// delete texture coordinates buffer
		glDeleteBuffers(1, &texcoord_buffer[i]);
		// delete texture buffer
		glDeleteBuffers(1, &texture_buffer[i]);
		// delete Shader Programs
		glDeleteProgram(program[i]);
	}

	delete[] program;
	delete[] aposition;
	delete[] anormal;
	delete[] upersp_matrix;
	delete[] uview_matrix;
	delete[] umodel_matrix;
	delete[] unormal_matrix;
	delete[] ulight_position;
	delete[] ulight_color;
}



void Client::draw(double dt) {

	/*shadowPass(dt);
	return;*/
	/*
		0 - SKY DOME
		1 - SPHERE-TEXTURED
		2,5 - TORUS - NON-TEXTURED
		3 - LIGHT SOURCE
		4 - PLANE TEXTURED
		6 - PLANE
	*/
	unsigned int pass = 1;
	/*
		1 - SHADOW MAP
		2 - SCENE RENDERING
	*/
	int viewport_save[4];
	glGetIntegerv(GL_VIEWPORT, viewport_save);

	while (pass <= 2) {

		eye2 = LIGHT_POSITION;

		glm::mat4 V;
		glm::mat4 P = glm::perspective(glm::radians(80.0f), (float)500 / (float)500, 1.0f, 100.0f);
		//glm::mat4 P = cs541::perspective(fov, aspect, near);

		glm::mat4 lightV = cs541::view(eye2, look2, EY);

		if (2 == pass) {
			if (eye == currentEye)
				V = cs541::view(eye, look, EY);
			else
				V = cs541::view(eye2, look2, EY);
		}
		else if (1 == pass) {
			glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
			glViewport(0, 0, 1024, 1024);
		}

		// clear frame buffer and z-buffer
		glClearColor(0.9f, 0.9f, 0.9f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearDepth(1);
		glEnable(GL_DEPTH_TEST);

		if (1 == pass) {
			glCullFace(GL_FRONT);
		}

		for (int i = 0; i < NO_OF_OBJECTS+1; ++i) {

			if(i==2) continue;
			int k = i;
			// FOR TEXTURE SHADERS
			if (i == 0 || i == 1 || i == 4) { k = 0; }
			// FOR NORMAL MESH SHADERS
			else { k = 1; }

			if (1 == pass) {
				if (i == 0 || i == 3)
					continue;
				k = 2;
			}

			

			// set shader uniform variable values
			glUseProgram(program[k]);
			glUniformMatrix4fv(upersp_matrix[k], 1, false, (float*)&P);
			if (2 == pass)
				glUniformMatrix4fv(uview_matrix[k], 1, false, (float*)&V);

			glUniformMatrix4fv(ulight_view_matrix[k], 1, false, (float*)&lightV);

			const float RATE = 360.0f / 8.0f;
			glm::vec4 AXIS = EY,
				CENTER = { (i - 1) * 5,0,0,0 };

			if (5 == i)
				CENTER = glm::vec4(5, 0, -4, 0);
			if (6 == i)
				CENTER = glm::vec4(0, 0, -14, 0);

			// TRANSLATE
			glm::mat4 T = cs541::translate(CENTER);
			/* SKY DOME */
			if (0 == i) {
				if (eye == currentEye)
					T = cs541::translate(eye);
				else
					T = cs541::translate(eye2);
			}
			/* LIGHT SOURCE */
			else if (3 == i)
				T = cs541::translate(LIGHT_POSITION);


			// ROTATE
			glm::mat4 R = cs541::rotate(RATE*time, AXIS);
			if (0 == i || 3 == i || 4 == i || 6 == i)
				R = cs541::rotate(0, AXIS);

			// SCALE
			glm::mat4 S = cs541::scale(2.5f);
			/* SKY DOME */
			if (0 == i)
				S = cs541::scale(50.0f);
			/* LIGHT SOURCE */
			else if (3 == i)
				S = cs541::scale(0.2f);
			else if (6 == i)
				S = cs541::scale(10.0f);

			glm::mat4 M = T * R * S;

			// MODEL & NORMAL MATRIX
			glUniformMatrix4fv(umodel_matrix[k], 1, false, (float*)&M);
			if (2 == pass) {
				if (0 != i) {
					glUniformMatrix4fv(unormal_matrix[k], 1, false, (float*)&R);
				}
				else {
					glUniformMatrix4fv(unormal_matrix[k], 1, false, (float*)&M);
				}

				// LIGHT POSITION AND COLOR
				const glm::vec4 LIGHT_COLOR(1, 1, 1, 1);
				glUniform4fv(ulight_position[k], 1, (float*)&LIGHT_POSITION);
				glUniform3fv(ulight_color[k], 1, (float*)&LIGHT_COLOR);

				// FOR EVERY OBJECTS EXCEPT SKY DOME
				if (0 != i) {
					glUniform3f(udiffuse_color, 0, 0, 1);
					if (6 == i)
						glUniform3f(udiffuse_color, 1, 1, 1);

					if (eye == currentEye) {
						glUniform4fv(ucamera_position, 1, &eye[0]);
					}
					else {
						glUniform4fv(ucamera_position, 1, &eye2[0]);
					}
				}

				glm::mat4 std2unit_matrix = cs541::translate(glm::vec4(.5f, .5f, .5f, 1.0f)) * cs541::scale(0.5f);
				glUniformMatrix4fv(ustd2unit_matrix[k], 1, false, (float*)&std2unit_matrix);
			}

			if (i == 5)
				glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[2]);
			else if (i == 6)
				glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[4]);
			else
				glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[i]);
			glVertexAttribPointer(aposition[k], 4, GL_FLOAT, false, 0, 0);
			glEnableVertexAttribArray(aposition[k]);

			if (2 == pass) {
				if (i == 5)
					glBindBuffer(GL_ARRAY_BUFFER, normal_buffer[2]);
				else if (i == 6)
					glBindBuffer(GL_ARRAY_BUFFER, normal_buffer[4]);
				else
					glBindBuffer(GL_ARRAY_BUFFER, normal_buffer[i]);
				glVertexAttribPointer(anormal[k], 4, GL_FLOAT, false, 0, 0);
				glEnableVertexAttribArray(anormal[k]);

				// TEXTURES
				if (0 == i || 1 == i || 4 == i) {
					int q = 0;

					/* TO USE DIFFERENT TEXTURES(int q) */
					if (4 == i) {
						/* TO TILE CERTAIN OBJECTS */
						q = 1;
						if (4 == i)
							glUniform1i(uTiled, 2);
					}
					else {
						glUniform1i(uTiled, 1);
					}


					if (1 == k) {
						glActiveTexture(GL_TEXTURE0);
						glBindTexture(GL_TEXTURE_2D, depth_texture_buffer);
						GLint location = glGetUniformLocation(program[1], "shadow_sampler");
						glUniform1i(location, 0);
					}
					else if (0 == k) {
						glActiveTexture(GL_TEXTURE1);
						glBindTexture(GL_TEXTURE_2D, depth_texture_buffer);
						GLint location = glGetUniformLocation(program[0], "shadow_sampler");
						glUniform1i(location, 1);
						// select the texture to use
						if (4 == i) {
							glActiveTexture(GL_TEXTURE0);
							GLint location = glGetUniformLocation(program[0], "usampler");
							glUniform1i(location, 0);
							glBindTexture(GL_TEXTURE_2D, depth_texture_buffer);
						}
						else {
							glActiveTexture(GL_TEXTURE0);
							GLint location = glGetUniformLocation(program[0], "usampler");
							glUniform1i(location, 0);
							glBindTexture(GL_TEXTURE_2D, texture_buffer[q]);
						}
					}

					glBindBuffer(GL_ARRAY_BUFFER, texcoord_buffer[1]);
					glVertexAttribPointer(atexture_coord, 2, GL_FLOAT, false, 0, 0);
					glEnableVertexAttribArray(atexture_coord);


				}
			}

			// draw the mesh
			if (i == 5)
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face_buffer[2]);
			else if (i == 6)
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face_buffer[4]);
			else
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, face_buffer[i]);
			glDrawElements(GL_TRIANGLES, 3 * face_count, GL_UNSIGNED_INT, 0);

			
		}

		if (1 == pass) {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(viewport_save[0], viewport_save[1], viewport_save[2], viewport_save[3]);
			glCullFace(GL_BACK);
		}
		++pass;
	}

	time += (float)dt;
}



void Client::RenderObject() {

}

void Client::keypress(SDL_Keycode kc) {
	// respond to keyboard input
	//   kc: SDL keycode (e.g., SDLK_SPACE, SDLK_a, SDLK_s)
	const float DIST_INC = 0.5f;
	switch (kc) {
	case SDLK_UP:
		if (eye == currentEye) {
			eye = eye + DIST_INC * look;
			currentEye = eye;
		}
		else {
			eye2 = eye2 + DIST_INC * look2;
			currentEye = eye2;
		}
		break;

	case SDLK_DOWN:
		if (eye == currentEye) {
			eye = eye - DIST_INC * look;
			currentEye = eye;
		}
		else {
			eye2 = eye2 - DIST_INC * look2;
			currentEye = eye2;
		}
		break;

	case SDLK_RIGHT:
		if (eye == currentEye) {
			eye = eye + DIST_INC * cs541::cross(look, EY);
			currentEye = eye;
		}
		else {
			eye2 = eye2 + DIST_INC * cs541::cross(look2, EY);
			currentEye = eye2;
		}
		break;

	case SDLK_LEFT:
		if (eye == currentEye) {
			eye = eye - DIST_INC * cs541::cross(look, EY);
			currentEye = eye;
		}
		else {
			eye2 = eye2 - DIST_INC * cs541::cross(look2, EY);
			currentEye = eye2;
		}
		break;

	case SDLK_w:
		LIGHT_POSITION.z -= DIST_INC;
		break;
	case SDLK_s:
		LIGHT_POSITION.z += DIST_INC;
		break;
	case SDLK_a:
		LIGHT_POSITION.x -= DIST_INC;
		break;
	case SDLK_d:
		LIGHT_POSITION.x += DIST_INC;
		break;
	case SDLK_x:
		if (currentEye == eye) {
			currentEye = eye2;
			currentLook = look2;
		}
		else {
			currentEye = eye;
			currentLook = look;
		}
		break;
	}
}


void Client::resize(int W, int H) {
	aspect = float(W) / float(H);
	glViewport(0, 0, W, H);
}


void Client::mousedrag(int x, int y, bool left_button) {
	// respond to mouse click
	//   (x,y): click location (in window coordinates)
	const float ANGLE_INC = 1.0f;
	
	glm::vec4 u;
	if(look == currentLook)
		u = glm::normalize(cs541::cross(look, EY));
	else
		u = glm::normalize(cs541::cross(look2, EY));

	glm::mat4 updown = cs541::rotate(-y * ANGLE_INC, u);
	glm::mat4 leftright = cs541::rotate(-x * ANGLE_INC, EY);

	if (look == currentLook) {
		look = leftright * updown * look;
		currentLook = look;
	}
	else {
		look2 = leftright * updown * look2;
		currentLook = look2;
	}
}



/////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// SDL: initialize and create a window
	SDL_Init(SDL_INIT_VIDEO);



	const char *title = "Window Title";
	int width = 500,
		height = 500;
	SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, width, height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext context = SDL_GL_CreateContext(window);

	// GLEW: get function bindings (if possible)
	glewInit();
	if (!GLEW_VERSION_2_0) {
		cout << "needs OpenGL version 2.0 or better" << endl;
		return -1;
	}

	LIGHT_POSITION = O + EX + 0.5f*EY + 15.0f*EZ;

	// animation loop
	bool done = false;
	Client *client = new Client();
	Uint32 ticks_last = SDL_GetTicks();
	while (!done) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				done = true;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					done = true;
				else
					client->keypress(event.key.keysym.sym);
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
					client->resize(event.window.data1, event.window.data2);
				break;
			case SDL_MOUSEMOTION:
				if ((event.motion.state&SDL_BUTTON_LMASK) != 0
					|| (event.motion.state&SDL_BUTTON_RMASK) != 0)
					client->mousedrag(event.motion.xrel, event.motion.yrel,
					(event.motion.state&SDL_BUTTON_LMASK) != 0);
				break;
			}
		}
		Uint32 ticks = SDL_GetTicks();
		double dt = 0.001*(ticks - ticks_last);
		ticks_last = ticks;
		client->draw(dt);
		SDL_GL_SwapWindow(window);
	}

	// clean up
	delete client;
	SDL_GL_DeleteContext(context);
	SDL_Quit();
	return 0;
}