#ifndef __MATRIX4X4_H__
#define __MATRIX4X4_H__

#ifndef __CMATH__
#include <cmath>
#define __CMATH__
#endif

#ifndef __IOSTREAM__
#include <iostream>
#define __IOSTREAM__
#endif

#ifndef __STDIO_H__
#include <stdio.h>
#define __STDIO_H__
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
using namespace std;

class Matrix4x4
{
public:
	float matrix[16];
	Matrix4x4();

	void Translatef(float x,float y,float z);
	void Rotatef(float angle,float x,float y,float z);
	void Scalef(float xScale,float yScale,float zScale);
	void InheritedScalef(float xScale, float yScale, float zScale);
	void Finish();
	void Clear();
	void coutM();
	int INDEX4(int x,int y);

	void PrintSelf(void);

		//! multiplication by a matrix
	const Matrix4x4 operator *(const Matrix4x4 &m)
	{
		Matrix4x4 temp;
		temp.matrix[0] = matrix[0]*m.matrix[0] + matrix[1]*m.matrix[4] + matrix[2]*m.matrix[8] + matrix[3]*m.matrix[12];
		temp.matrix[1] = matrix[0]*m.matrix[1] + matrix[1]*m.matrix[5] + matrix[2]*m.matrix[9] + matrix[3]*m.matrix[13];
		temp.matrix[2] = matrix[0]*m.matrix[2] + matrix[1]*m.matrix[6] + matrix[2]*m.matrix[10] + matrix[3]*m.matrix[14];
		temp.matrix[3] = matrix[0]*m.matrix[3] + matrix[1]*m.matrix[7] + matrix[2]*m.matrix[11] + matrix[3]*m.matrix[15];

		temp.matrix[4] = matrix[4]*m.matrix[0] + matrix[5]*m.matrix[4] + matrix[6]*m.matrix[8] + matrix[7]*m.matrix[12];
		temp.matrix[5] = matrix[4]*m.matrix[1] + matrix[5]*m.matrix[5] + matrix[6]*m.matrix[9] + matrix[7]*m.matrix[13];
		temp.matrix[6] = matrix[4]*m.matrix[2] + matrix[5]*m.matrix[6] + matrix[6]*m.matrix[10] + matrix[7]*m.matrix[14];
		temp.matrix[7] = matrix[4]*m.matrix[3] + matrix[5]*m.matrix[7] + matrix[6]*m.matrix[11] + matrix[7]*m.matrix[15];

		temp.matrix[8] = matrix[8]*m.matrix[0] + matrix[9]*m.matrix[4] + matrix[10]*m.matrix[8] + matrix[11]*m.matrix[12];
		temp.matrix[9] = matrix[8]*m.matrix[1] + matrix[9]*m.matrix[5] + matrix[10]*m.matrix[9] + matrix[11]*m.matrix[13];
		temp.matrix[10] = matrix[8]*m.matrix[2] + matrix[9]*m.matrix[6] + matrix[10]*m.matrix[10] + matrix[11]*m.matrix[14];
		temp.matrix[11] = matrix[8]*m.matrix[3] + matrix[9]*m.matrix[7] + matrix[10]*m.matrix[11] + matrix[11]*m.matrix[15];

		temp.matrix[12] = matrix[12]*m.matrix[0] + matrix[13]*m.matrix[4] + matrix[14]*m.matrix[8] + matrix[15]*m.matrix[12];
		temp.matrix[13] = matrix[12]*m.matrix[1] + matrix[13]*m.matrix[5] + matrix[14]*m.matrix[9] + matrix[15]*m.matrix[13];
		temp.matrix[14] = matrix[12]*m.matrix[2] + matrix[13]*m.matrix[6] + matrix[14]*m.matrix[10] + matrix[15]*m.matrix[14];
		temp.matrix[15] = matrix[12]*m.matrix[3] + matrix[13]*m.matrix[7] + matrix[14]*m.matrix[11] + matrix[15]*m.matrix[15];

		return temp;
	}
};

#endif