#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

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

#ifndef __NODE_H__
#include "node.h"
#endif

#ifndef __MATRIX4X4_H__
#include "Matrix4x4.h"
#endif

#ifndef __VECTOR_H__
#include "..\\vector3D.h"
#endif

class CSceneNode;

class CTransform :
	public CNode
{
private:
	Matrix4x4 Mtx, Update_Mtx;

public:
	CTransform(void);
	CTransform( const float dx, const float dy, const float dz  );
	CTransform(Vector3D Translate, Vector3D Scale);
	~CTransform(void);

	void PreRendering();
	void Draw(void);
	void PostRendering();

	void SetTranslate( const float dx, const float dy, const float dz  );
	void SetRotate( const float angle, const float rx, const float ry, const float rz  );
	void SetRotate2( const float angle, const float rx, const float ry, const float rz, 
					 const float offset_x, const float offset_y, const float offset_z );
	void SetScale( const float sx, const float sy, const float sz , bool );
	void ApplyTransform( Matrix4x4 newMTX );
	void GetOffset( float& x, float& y, float& z );
	// Get the transformation matrix
	Matrix4x4 GetTransform(void);
};
#endif