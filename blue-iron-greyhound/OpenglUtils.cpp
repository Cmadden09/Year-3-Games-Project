#include "openglUtils.h"
#include <map>
/*
char * minimalVert =
{	
	"//vertex shader							\n"
	"											\n"
	"#version 330								\n"
	"											\n"
	"in vec3 in_position;						\n"
	"in vec3 in_Color;							\n"
	"out vec3 ex_Color;							\n"
	"											\n"
	"void main(void)							\n"
	"{											\n"
	"	ex_Color = in_Color;					\n"
	"	gl_Position = vec4(in_position, 1.0);	\n"
	"}                                          \n"
};

char * minimalFrag =
{
"									\n"
"	#version 330					\n"
"									\n"
"	precision highp float;			\n"
"									\n"
"	in  vec3 ex_Color;				\n"
"	out vec4 out_Color;				\n"
"									\n"
"	void main(void)					\n"
"	{								\n"
"	out_Color = vec4(ex_Color,1.0); \n"
"									\n"
"	}								\n"

};

*/

char * texVert =
{
"	// textured.vert												\n"
"	// use textures, but no lighting								\n"
"	#version 330													\n"
"																	\n"
"	uniform mat4 modelview;											\n"
"uniform mat4 projection;											\n"
"																	\n"
"in  vec3 in_Position;												\n"
"//in  vec3 in_Colour; // colour not used with lighting				\n"
"in  vec3 in_Normal;												\n"
"//out vec4 ex_Color;												\n"
"out vec3 ex_N;														\n"
"out vec3 ex_V;														\n"
"out vec3 ex_L;														\n"		
"out float ex_D;													\n"
"uniform vec4 lightPosition;										\n"
"																	\n"
"in vec2 in_TexCoord;												\n"
"out vec2 ex_TexCoord;												\n"
"																	\n"
"	void main(void) {												\n"
"																	\n"
"	// vertex into eye coordinates									\n"
"	vec4 vertexPosition = modelview * vec4(in_Position,1.0);		\n"
"    ex_D = distance(vertexPosition, lightPosition);				\n"
"																	\n"
"	ex_V = normalize(-vertexPosition).xyz;							\n"
"																	\n"
"	mat3 normalmatrix = transpose(inverse(mat3(modelview)));		\n"
"	ex_N = normalize(normalmatrix * in_Normal);						\n"
"	//ex_N = in_Normal;						\n"
"																	\n"
"	ex_L = normalize(lightPosition.xyz - vertexPosition.xyz);		\n"
"																	\n"				
"	gl_Position = projection * vertexPosition;						\n"
"																	\n"
"	ex_TexCoord = in_TexCoord;										\n"
"}																	\n"
																
};


char * texFrag =
{
"	// textured.frag										\n"
"	#version 330											\n"
"															\n"
"	// Some drivers require the following					\n"
"	precision highp float;									\n"
"															\n"
"in vec3 ex_N;												\n"
"in vec3 ex_V;												\n"
"in vec3 ex_L;												\n"
"in float ex_D;												\n"
"															\n"
"uniform float attConst;									\n"
"uniform float attLinear;									\n"
"uniform float attQuadratic;								\n"
"															\n"
"struct lightStruct											\n"
"{															\n"
"	vec4 ambient;											\n"
"	vec4 diffuse;											\n"
"	vec4 specular;											\n"
"};															\n"
"															\n"
"struct materialStruct										\n"
"{															\n"
"	vec4 ambient;											\n"
"	vec4 diffuse;											\n"
"	vec4 specular;											\n"
"	float shininess;										\n"
"};															\n"
"															\n"
"															\n"
"uniform lightStruct light;									\n"
"uniform materialStruct material;							\n"
"uniform sampler2D textureUnit0;							\n"
"															\n"
"in vec2 ex_TexCoord;										\n"
"layout(location = 0) out vec4 out_Color;					\n"
"															\n"
"void main(void) {											\n"
"															\n"
"																					\n"
"	// Ambient intensity															\n"
"	vec4 ambientI = light.ambient * material.ambient;								\n"
"																					\n"
"	// Diffuse intensity															\n"
"	vec4 diffuseI = light.diffuse * material.diffuse;								\n"
"	diffuseI = diffuseI * max(dot(normalize(ex_N),normalize(ex_L)),0);				\n"
"																					\n"
"	// Specular intensity															\n"
"	// Calculate R - reflection of light											\n"
"	vec3 R = normalize(reflect(normalize(-ex_L),normalize(ex_N)));					\n"
"																					\n"
"	vec4 specularI = light.specular * material.specular;							\n"
"	specularI = specularI * pow(max(dot(R,ex_V),0), material.shininess);			\n"
"																							\n"
"	float attenuation = 1.0f / (attConst + attLinear * ex_D + attQuadratic * ex_D*ex_D);	\n"
"	vec4 tmp_Color = (diffuseI + specularI)*texture(textureUnit0, ex_TexCoord);				\n"
"	//Attenuation does not affect transparency												\n"
"	vec4 litColour = vec4(tmp_Color.rgb *attenuation, tmp_Color.a);							\n"
"	vec4 amb = min(ambientI,vec4(1.0f));													\n"
"																							\n"
"	//out_Color = (diffuseI + specularI) + ambientI*texture(textureUnit0, ex_TexCoord),vec4(1.0f); \n"
"	// Fragment colour																		\n"
"	out_Color= (diffuseI + specularI +ambientI)*texture(textureUnit0, ex_TexCoord);			\n"
"	//out_Color = texture(textureUnit0, ex_TexCoord);;					\n"
"}																							\n"
};




#define RT3D_VERTEX		0
#define RT3D_COLOUR		1
#define RT3D_NORMAL		2
#define RT3D_TEXCOORD   3
#define RT3D_INDEX		4

namespace OpenglUtils
{
	static map<GLuint, GLuint *> vertexArrayMap;


	// printShaderError
	// Display (hopefully) useful error messages if shader fails to compile or link
	void printShaderError(const GLint shader)
	{
		int maxLength = 0;
		int logLength = 0;
		GLchar *logMessage;

		// Find out how long the error message is
		if (!glIsShader(shader))
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		else
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		if (maxLength > 0) { // If message has some contents
			logMessage = new GLchar[maxLength];
			if (!glIsShader(shader))
				glGetProgramInfoLog(shader, maxLength, &logLength, logMessage);
			else
				glGetShaderInfoLog(shader, maxLength, &logLength, logMessage);
			cout << "Shader Info Log:" << endl << logMessage << endl;
			delete[] logMessage;
		}
		// should additionally check for OpenGL errors here
	}


	//Not using due to errors. Shaders are coded into the top of this file.
	char* loadFile(const char *fname, GLint &fSize)
	{
		int size;
		char * memblock;

		// file read based on example in cplusplus.com tutorial
		ifstream file(fname, ios::in | ios::binary | ios::ate);
		if (file.is_open()) {
			size = (int)file.tellg(); // get location of file pointer i.e. file size
			fSize = (GLint)size;
			memblock = new char[size];
			file.seekg(0, ios::beg);
			file.read(memblock, size);
			file.close();
		
			cout << "file " << fname << " loaded" << endl;
			cout << fname << " size is:  " << size << endl;
		}
		else 
		{
			cout << "Unable to open file " << fname << endl;
			fSize = 0;
			return nullptr;
		}
	}


	//This function would normal take two file names and create shaders with them but it
	//has been changed to use the hard coded shaders at the top of this namespace
	GLuint initShaders(const char *vertFile, const char *fragFile)
	{
		GLuint p, f, v;

		char *vs, *fs;

		v = glCreateShader(GL_VERTEX_SHADER);
		f = glCreateShader(GL_FRAGMENT_SHADER);

		// load shaders & get length of each
		GLint vlen;
		GLint flen;

		//vs = loadFile(vertFile, vlen);
		//fs = loadFile(fragFile, flen);

		vs = texVert;
		fs = texFrag;
		
		

		const char * vv = vs;
		const char * ff = fs;

		//glShaderSource(v, 1, &vv, &vlen);
		//glShaderSource(f, 1, &ff, &flen);

		glShaderSource(v, 1, &vv, NULL);
		glShaderSource(f, 1, &ff, NULL);

		GLint compiled;

		glCompileShader(v);
		glGetShaderiv(v, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			cout << "Vertex shader not compiled." << endl;
			OpenglUtils::printShaderError(v);
		}

		glCompileShader(f);
		glGetShaderiv(f, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			cout << "Fragment shader not compiled." << endl;
			OpenglUtils::printShaderError(f);
		}

		p = glCreateProgram();

		glAttachShader(p, v);
		glAttachShader(p, f);

		glBindAttribLocation(p, RT3D_VERTEX, "in_Position");
		glBindAttribLocation(p, RT3D_COLOUR, "in_Color");
		glBindAttribLocation(p, RT3D_NORMAL, "in_Normal");
		glBindAttribLocation(p, RT3D_TEXCOORD, "in_TexCoord");

		glLinkProgram(p);
		glUseProgram(p);

		//delete[] vs; // dont forget to free allocated memory
		//delete[] fs; // we allocated this in the loadFile function...

		return p;
	}


	GLuint initParticleShaders(char *vertFile,char *fragFile)
	{
		GLuint p, f, v;

		char *vs, *fs;

		v = glCreateShader(GL_VERTEX_SHADER);
		f = glCreateShader(GL_FRAGMENT_SHADER);

		// load shaders & get length of each
		GLint vlen;
		GLint flen;

		//vs = loadFile(vertFile, vlen);
		//fs = loadFile(fragFile, flen);

		vs = vertFile ;
		fs = fragFile;



		const char * vv = vs;
		const char * ff = fs;

		//glShaderSource(v, 1, &vv, &vlen);
		//glShaderSource(f, 1, &ff, &flen);

		glShaderSource(v, 1, &vv, NULL);
		glShaderSource(f, 1, &ff, NULL);

		GLint compiled;

		glCompileShader(v);
		glGetShaderiv(v, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			cout << "Vertex shader not compiled." << endl;
			OpenglUtils::printShaderError(v);
		}

		glCompileShader(f);
		glGetShaderiv(f, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			cout << "Fragment shader not compiled." << endl;
			OpenglUtils::printShaderError(f);
		}

		p = glCreateProgram();

		glAttachShader(p, v);
		glAttachShader(p, f);

		glBindAttribLocation(p, RT3D_VERTEX, "in_Position");
		glBindAttribLocation(p, RT3D_COLOUR, "in_Color");
		glBindAttribLocation(p, RT3D_NORMAL, "in_Normal");
		glBindAttribLocation(p, RT3D_TEXCOORD, "in_TexCoord");

		glLinkProgram(p);
		glUseProgram(p);

		//delete[] vs; // dont forget to free allocated memory
		//delete[] fs; // we allocated this in the loadFile function...

		return p;
	}

	GLuint createMesh(const GLuint numVerts, const GLfloat* vertices, const GLfloat* colours,
		const GLfloat* normals, const GLfloat* texcoords) {
		return createMesh(numVerts, vertices, colours, normals, texcoords, 0, nullptr);
	}

	GLuint createMesh(const GLuint numVerts, const GLfloat* vertices, const GLfloat* colours,
		const GLfloat* normals, const GLfloat* texcoords, const GLuint indexCount, const GLuint* indices) {
		GLuint VAO;
		// generate and set up a VAO for the mesh
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		GLuint *pMeshBuffers = new GLuint[5];


		if (vertices == nullptr) {
			// cant create a mesh without vertices... oops
			//exitFatalError("Attempt to create a mesh with no vertices");
		}

		// generate and set up the VBOs for the data
		GLuint VBO;
		glGenBuffers(1, &VBO);

		// VBO for vertex data
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, 3 * numVerts * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)RT3D_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(RT3D_VERTEX);
		pMeshBuffers[RT3D_VERTEX] = VBO;


		// VBO for colour data
		if (colours != nullptr) {
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, 3 * numVerts * sizeof(GLfloat), colours, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)RT3D_COLOUR, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(RT3D_COLOUR);
			pMeshBuffers[RT3D_COLOUR] = VBO;
		}

		// VBO for normal data
		if (normals != nullptr) {
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, 3 * numVerts * sizeof(GLfloat), normals, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)RT3D_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(RT3D_NORMAL);
			pMeshBuffers[RT3D_NORMAL] = VBO;
		}

		// VBO for tex-coord data
		if (texcoords != nullptr) {
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, 2 * numVerts * sizeof(GLfloat), texcoords, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)RT3D_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(RT3D_TEXCOORD);
			pMeshBuffers[RT3D_TEXCOORD] = VBO;
		}

		if (indices != nullptr && indexCount > 0) {
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indices, GL_STATIC_DRAW);
			pMeshBuffers[RT3D_INDEX] = VBO;
		}
		// unbind vertex array
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		// return the identifier needed to draw this mesh

		vertexArrayMap.insert(pair<GLuint, GLuint *>(VAO, pMeshBuffers));

		return VAO;
	}



	GLuint createMesh(const GLuint numVerts, const GLfloat* vertices, const GLfloat* colours, const GLfloat* normals,
		const GLfloat* texcoords, const GLuint texCount, const GLuint indexCount, const GLuint* indices)
	{
		GLuint VAO;
		// generate and set up a VAO for the mesh
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		GLuint *pMeshBuffers = new GLuint[5];


		if (vertices == nullptr) {
			// cant create a mesh without vertices... oops
			cout << "ERROR: Attempt to create a mesh with no vertices" << endl;
		}

		// generate and set up the VBOs for the data
		GLuint VBO;
		glGenBuffers(1, &VBO);

	

		// VBO for vertex data
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER,  numVerts * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)RT3D_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(RT3D_VERTEX);
		pMeshBuffers[RT3D_VERTEX] = VBO;


		// VBO for colour data
		if (colours != nullptr) {
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, numVerts * sizeof(GLfloat), colours, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)RT3D_COLOUR, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(RT3D_COLOUR);
			pMeshBuffers[RT3D_COLOUR] = VBO;
		}

		// VBO for normal data
		if (normals != nullptr) {
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, numVerts * sizeof(GLfloat), normals, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)RT3D_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(RT3D_NORMAL);
			pMeshBuffers[RT3D_NORMAL] = VBO;
		}

		// VBO for tex-coord data
		if (texcoords != nullptr) {
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, texCount * sizeof(GLfloat), texcoords, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)RT3D_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(RT3D_TEXCOORD);
			pMeshBuffers[RT3D_TEXCOORD] = VBO;
		}

		if (indices != nullptr && indexCount > 0) {
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indices, GL_STATIC_DRAW);
			pMeshBuffers[RT3D_INDEX] = VBO;
		}
		// unbind vertex array
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		// return the identifier needed to draw this mesh

		
		
		vertexArrayMap.insert(pair<GLuint, GLuint *>(VAO, pMeshBuffers));



		return VAO;
	}

	void setUniformMatrix4fv(const GLuint program, const char* uniformName, const GLfloat *data)
	{
		int uniformIndex = glGetUniformLocation(program, uniformName);
		glUniformMatrix4fv(uniformIndex, 1, GL_FALSE, data);
	}

	void drawIndexedMesh(const GLuint mesh, const GLuint indexCount, const GLuint primitive) {
		glBindVertexArray(mesh);	// Bind mesh VAO
		glDrawElements(primitive, indexCount, GL_UNSIGNED_INT, 0);	// draw VAO 
		glBindVertexArray(0);
	}

	void drawMesh(const GLuint mesh, const GLuint numVerts, const GLuint primitive) {
		glBindVertexArray(mesh);	// Bind mesh VAO
		glDrawArrays(primitive, 0, numVerts);	// draw first vertex array object
		glBindVertexArray(0);
	}

	void setLight(const GLuint program, const lightStruct light)
	{
		// pass in light data to shader
		int uniformIndex = glGetUniformLocation(program, "light.ambient");
		glUniform4fv(uniformIndex, 1, light.ambient);
		uniformIndex = glGetUniformLocation(program, "light.diffuse");
		glUniform4fv(uniformIndex, 1, light.diffuse);
		uniformIndex = glGetUniformLocation(program, "light.specular");
		glUniform4fv(uniformIndex, 1, light.specular);
		uniformIndex = glGetUniformLocation(program, "lightPosition");
		glUniform4fv(uniformIndex, 1, light.position);
	}

	void setLightPos(const GLuint program, const GLfloat *lightPos)
	{
		int uniformIndex = glGetUniformLocation(program, "lightPosition");
		glUniform4fv(uniformIndex, 1, lightPos);
	}

	void setMaterial(const GLuint program, const materialStruct material)
	{
		// pass in material data to shader 
		int uniformIndex = glGetUniformLocation(program, "material.ambient");
		glUniform4fv(uniformIndex, 1, material.ambient);
		uniformIndex = glGetUniformLocation(program, "material.diffuse");
		glUniform4fv(uniformIndex, 1, material.diffuse);
		uniformIndex = glGetUniformLocation(program, "material.specular");
		glUniform4fv(uniformIndex, 1, material.specular);
		uniformIndex = glGetUniformLocation(program, "material.shininess");
		glUniform1f(uniformIndex, material.shininess);
	}


	void updateMesh(const GLuint mesh, const unsigned int bufferType, const GLfloat *data, const GLuint size) {
		GLuint * pMeshBuffers = vertexArrayMap[mesh];
		glBindVertexArray(mesh);

		// Delete the old buffer data
		glDeleteBuffers(1, &pMeshBuffers[bufferType]);

		// generate and set up the VBOs for the new data
		GLuint VBO;
		glGenBuffers(1, &VBO);
		// VBO for the data
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)bufferType, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(bufferType);
		pMeshBuffers[RT3D_VERTEX] = VBO;

		glBindVertexArray(0);

	}


}