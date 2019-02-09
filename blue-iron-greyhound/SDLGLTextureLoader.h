#ifndef SDLGLTEXTURELOADER
#define SDLGLTEXTURELOADER

#pragma once

#include <GL/glew.h>
#include "SDL.h"
#include <SDL_image.h>
#include <iostream>


namespace SDLGLTextureLoader {

	GLuint loadBitmap(char *fname);

	GLuint loadCubeMap(const char *fname[6], GLuint *texID);

	GLuint loadPNG(char *fname);


	GLuint checkTextures(char* fileName);

	GLuint loadMd2Bitmap(char *fname);


	
}


#endif