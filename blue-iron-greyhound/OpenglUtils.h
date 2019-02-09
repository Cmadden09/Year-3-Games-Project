/* 
This is a complete rip off of rt3d supplied in the real time 3D class 
*/

#ifndef OPENGLUTILS
#define OPENGLUTILS

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

namespace OpenglUtils
{
	struct materialStruct {
		GLfloat ambient[4];
		GLfloat diffuse[4];
		GLfloat specular[4];
		GLfloat shininess;
	};

	struct lightStruct {
		GLfloat ambient[4];
		GLfloat diffuse[4];
		GLfloat specular[4];
		GLfloat position[4];
	};

	void printShaderError(const GLint shader);

	char* loadFile(const char *fname, GLint &fSize);

	GLuint initShaders(const char *vertFile, const char *fragFile);
	GLuint initParticleShaders( char *vertFile,  char *fragFile);

	GLuint createMesh(const GLuint numVerts, const GLfloat* vertices, const GLfloat* colours, const GLfloat* normals,
		const GLfloat* texcoords,const GLuint texCount, const GLuint indexCount, const GLuint* indices);
	
	GLuint createMesh(const GLuint numVerts, const GLfloat* vertices, const GLfloat* colours,
		const GLfloat* normals, const GLfloat* texcoords, const GLuint indexCount, const GLuint* indices);

	GLuint createMesh(const GLuint numVerts, const GLfloat* vertices, const GLfloat* colours, const GLfloat* normals,
		const GLfloat* texcoords);

	void setUniformMatrix4fv(const GLuint program, const char* uniformName, const GLfloat *data);

	void setLight(const GLuint program, const lightStruct light);

	void setLightPos(const GLuint program, const GLfloat *lightPos);
	void setMaterial(const GLuint program, const materialStruct material);

	void drawIndexedMesh(const GLuint mesh, const GLuint indexCount, const GLuint primitive);
	void drawMesh(const GLuint mesh, const GLuint numVerts, const GLuint primitive);

	void updateMesh(const GLuint mesh, const unsigned int bufferType, const GLfloat *data, const GLuint size);
}

#endif
