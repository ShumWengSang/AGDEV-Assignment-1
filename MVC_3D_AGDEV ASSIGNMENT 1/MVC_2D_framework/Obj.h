#pragma once
#ifndef __OBJ_H__
#define __OBJ_H__


#include <iostream>
#ifndef __TEXTURE_H__
#include "texture.h"
#endif

#ifndef __WINDOWS_H__
#include <windows.h> // Header File For Windows
#endif

#ifndef __GL_H__
#include <gl\gl.h> // Header File For The OpenGL32 Library
#pragma comment(lib, "glu32.lib")
#endif

#ifndef __GLU_H__
#include <gl\glu.h> // Header File For The GLu32 Library
#pragma comment(lib, "opengl32.lib")
#endif


typedef struct {
	float x, y, z, u, v;
	unsigned int color;
} Vertex;

typedef struct {
	int * vIndices, *nIndices, *tcIndices; int vCount;
} Face;

typedef struct _Mesh
{
	Vertex * vertices;
	Vertex * normals;
	Vertex * texCoords;
	Face * faces;
	int noVertices, noNormals, noTexCoords, noFaces;
} Mesh;
class Obj
{
public:
	Obj();
	~Obj();

	TextureImage theTexture;
	Mesh * LoadObj(char * filename);
	Mesh * TheMesh;

	void RenderMesh();
};

#endif