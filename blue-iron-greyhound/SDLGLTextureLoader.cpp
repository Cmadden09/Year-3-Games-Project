#include "SDLGLTextureLoader.h"

namespace SDLGLTextureLoader {


	static char* TexturePaths[30];
	static int TextureIDs[30];
	static int texCount;

	GLuint checkTextures(char* fileName)
	{
		for (int i = 0; i < texCount; i++)
		{
			if (strcmp(TexturePaths[i], fileName) == 0)
				return TextureIDs[i];
		}

		return 0;
	}



	GLuint loadBitmap(char *fname) {

		if (checkTextures(fname))
			return checkTextures(fname);




		GLuint texID;
		glGenTextures(1, &texID); // generate texture ID

								  // load file - using core SDL library
		SDL_Surface *tmpSurface;
		tmpSurface = SDL_LoadBMP(fname);
		if (!tmpSurface) {
			std::cout << "Error loading bitmap" << std::endl;
		}

		// bind texture and set parameters 
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		SDL_PixelFormat *format = tmpSurface->format;

		GLuint externalFormat, internalFormat;
		if (format->Amask) {
			internalFormat = GL_RGBA;
			externalFormat = (format->Rmask < format->Bmask) ? GL_RGBA : GL_BGRA;
		}
		else {
			internalFormat = GL_RGB;
			externalFormat = (format->Rmask < format->Bmask) ? GL_RGB : GL_BGR;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, tmpSurface->w, tmpSurface->h, 0,
			externalFormat, GL_UNSIGNED_BYTE, tmpSurface->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);

		SDL_FreeSurface(tmpSurface); // texture loaded, free the temporary buffer

		if (texID == NULL)
			std::cout << "ERROR: Texture " << fname << " not loaded" << std::endl;
	

		
		TexturePaths[texCount] = fname;
		TextureIDs[texCount] = texID;
		texCount++;

		return texID;	// return value of texture ID
	}



	//Utility
	GLuint loadMd2Bitmap(char *fname)
	{
		GLuint texID;
		glGenTextures(1, &texID); // generate texture ID
								  // load file - using core SDL library
		SDL_Surface *tmpSurface;
		tmpSurface = SDL_LoadBMP(fname);
		if (!tmpSurface)
		{
			std::cout << "Error loading bitmap" << std::endl;
		}

		// bind texture and set parameters
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		SDL_PixelFormat *format = tmpSurface->format;
		GLuint externalFormat, internalFormat;
		if (format->Amask) {
			internalFormat = GL_RGBA;
			externalFormat = (format->Rmask < format->Bmask) ? GL_RGBA : GL_BGRA;
		}
		else {
			internalFormat = GL_RGB;
			externalFormat = (format->Rmask < format->Bmask) ? GL_RGB : GL_BGR;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, tmpSurface->w, tmpSurface->h, 0,
			externalFormat, GL_UNSIGNED_BYTE, tmpSurface->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		SDL_FreeSurface(tmpSurface); // texture loaded, free the temporary buffer
		return texID;	// return value of texture ID
	}


	// A simple cubemap loading function
	// lots of room for improvement - and better error checking!
	GLuint loadCubeMap(const char *fname[6], GLuint *texID)
	{
		glGenTextures(1, texID); // generate texture ID
		GLenum sides[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
			GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y };
		SDL_Surface *tmpSurface;

		glBindTexture(GL_TEXTURE_CUBE_MAP, *texID); // bind texture and set parameters
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		GLuint externalFormat;
		for (int i = 0; i<6; i++)
		{
			// load file - using core SDL library
			tmpSurface = SDL_LoadBMP(fname[i]);
			if (!tmpSurface)
			{
				std::cout << "Error loading bitmap" << std::endl;
				return *texID;
			}

			// skybox textures should not have alpha (assuming this is true!)
			SDL_PixelFormat *format = tmpSurface->format;
			externalFormat = (format->Rmask < format->Bmask) ? GL_RGB : GL_BGR;

			glTexImage2D(sides[i], 0, GL_RGB, tmpSurface->w, tmpSurface->h, 0,
				externalFormat, GL_UNSIGNED_BYTE, tmpSurface->pixels);
			// texture loaded, free the temporary buffer
			SDL_FreeSurface(tmpSurface);
		}
		return *texID;	// return value of texure ID, redundant really
	}



	/////////////////////////////////
	//Loads a PNG file as a texture//
	/////////////////////////////////
	GLuint loadPNG(char *fname) {

		if (checkTextures(fname))
			return checkTextures(fname);


		GLuint texID;
		glGenTextures(1, &texID); // generate texture ID

								  // load file - using core SDL library
		SDL_Surface *tmpSurface;
		tmpSurface = IMG_Load(fname);
		if (!tmpSurface) {
			//std::cout << "Error loading bitmap" << std::endl;
			printf("IMG_Load: %s\n", IMG_GetError());
		}

		// bind texture and set parameters
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		SDL_PixelFormat *format = tmpSurface->format;

		////
		//// Widthand height in number of pixels 
		///int width = tmpSurface->w;
		///int height = tmpSurface->h;
		////
		////

		GLuint externalFormat, internalFormat;
 		if (format->Amask) {
			internalFormat = GL_RGBA;
			externalFormat = (format->Rmask < format->Bmask) ? GL_RGBA : GL_BGRA;
		}
		else {
			internalFormat = GL_RGB;
			externalFormat = (format->Rmask < format->Bmask) ? GL_RGB : GL_BGR;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, tmpSurface->w, tmpSurface->h, 0,
			externalFormat, GL_UNSIGNED_BYTE, tmpSurface->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);

		SDL_FreeSurface(tmpSurface); // texture loaded, free the temporary buffer

		
		TextureIDs[texCount] = texID;
		TexturePaths[texCount] = fname;
		texCount++;

		return texID;	// return value of texture ID
	}


}