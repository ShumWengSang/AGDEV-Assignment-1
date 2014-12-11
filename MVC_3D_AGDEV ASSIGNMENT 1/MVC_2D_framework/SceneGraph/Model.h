#ifndef __MODEL_H__
#define __MODEL_H__

#ifndef __VECTOR_H__
#include "..\vector3D.h"
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

#ifndef __OBJ_H__
#include "..\Obj.h"
#endif
enum WhatToDraw
{
	Model,
	Cube,
	Sphere,
	Nothing
};

class CModel
{
private:
	Vector3D vTopLeft, vBottomRight;


	float red, green, blue;
public:
	CModel(void);
	~CModel(void);

	void DrawSphere(void);
	void DrawCube();
	void Draw(void);
	void SetColor(const float red, const float green, const float blue);



	Vector3D NearTopLeft, NearTopRight, NearBottomLeft, NearBottomRight;
	Vector3D FarTopLeft, FarTopRight, FarBottomLeft, FarBottomRight;

	// Get the top left of the bounding box of the instance
	Vector3D GetTopLeft(void);
	// Get the bottomright of the bounding box of the instance
	Vector3D GetBottomRight(void);

	//Class pointer to the Obj.
	//Use this to render the mesh.
	Obj * theObj;

	void InitObj();
	WhatToDraw states;
};
#endif