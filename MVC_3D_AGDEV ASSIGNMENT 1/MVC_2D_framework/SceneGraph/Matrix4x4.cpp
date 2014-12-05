#ifndef __MATRIX4X4_H__
#include "Matrix4x4.h"
#endif

Matrix4x4::Matrix4x4()
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if (i == j)
			{
				matrix[INDEX4(i,j)] = 1;
			}
			else
			{
				matrix[INDEX4(i,j)] = 0;
			}
		}
	}
}

int Matrix4x4::INDEX4(int x,int y)
{
	return y*4 + x;
}

void Matrix4x4::PrintSelf(void)
{
	cout << "*** start of Matrix printout ***" << endl;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			cout << matrix[INDEX4(i,j)] << "\t";
		}
		cout << endl;
	}
	cout << "*** end of Matrix printout ***" << endl;
}

void Matrix4x4::Translatef(float x,float y,float z)
{
	matrix[INDEX4(0,3)] = x;
	matrix[INDEX4(1,3)] = y;
	matrix[INDEX4(2,3)] = z;
}

void Matrix4x4::Scalef(float x,float y,float z)
{
	matrix[INDEX4(0,0)] = x;
	matrix[INDEX4(1,1)] = y;
	matrix[INDEX4(2,2)] = z;
}

void Matrix4x4::InheritedScalef(float xScale, float yScale, float zScale)
{
	matrix[INDEX4(0, 0)] *= xScale;
	matrix[INDEX4(1, 1)] *= yScale;
	matrix[INDEX4(2, 2)] *= zScale;
}

void Matrix4x4::Rotatef(float angle, float x, float y, float z)
{
	angle *= (float) (3.141592f / 180.0f);
	if (x >= 1)
	{
		matrix[INDEX4(1,1)] = cos(angle);
		matrix[INDEX4(1,2)] = -sin(angle);
		matrix[INDEX4(2,1)] = sin(angle);
		matrix[INDEX4(2,2)] = cos(angle);
	}

	else if (y >= 1)
	{
		matrix[INDEX4(0,0)] = cos(angle);
		matrix[INDEX4(2,0)] = -sin(angle);
		matrix[INDEX4(0,2)] = sin(angle);
		matrix[INDEX4(2,2)] = cos(angle);
	}
	else if (z >= 1)
	{
		matrix[INDEX4(0,0)] = cos(angle);
		matrix[INDEX4(0,1)] = -sin(angle);
		matrix[INDEX4(1,0)] = sin(angle);
		matrix[INDEX4(1,1)] = cos(angle);
	}
}

void Matrix4x4::Finish(void)
{
	glMultMatrixf(matrix);
}

void Matrix4x4::Clear(void)
{
	Matrix4x4();
}

void Matrix4x4::coutM()
{
	cout<<matrix[0]<<","<<matrix[1]<<","<<matrix[2]<<","<<matrix[3]<<endl;
	cout<<matrix[4]<<","<<matrix[5]<<","<<matrix[6]<<","<<matrix[7]<<endl;
	cout<<matrix[8]<<","<<matrix[9]<<","<<matrix[10]<<","<<matrix[11]<<endl;
	cout<<matrix[12]<<","<<matrix[13]<<","<<matrix[14]<<","<<matrix[15]<<endl;
	cout<<endl;
}