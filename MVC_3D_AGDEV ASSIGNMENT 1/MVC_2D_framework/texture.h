#ifndef TEXTURE_H
#define TEXTURE_H

#ifndef __WINDOWS_H__
#include <Windows.h>
#define __WINDOWS_H__
#endif

#ifndef __GL_H__
#include <gl\GL.h>
#define __GL_H__
#endif


typedef struct												// Create A Structure
{
	GLubyte	*imageData;										// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel.
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
} TextureImage;												// Structure Name


bool LoadTGA(TextureImage *texture, char *filename);			// Loads A TGA File Into Memory


#endif