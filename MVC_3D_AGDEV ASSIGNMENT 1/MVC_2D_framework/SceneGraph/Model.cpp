#ifndef __MODEL_H__
#include "Model.h"
#endif


#include <stdio.h>


CModel::CModel(void)
{
	vTopLeft = Vector3D( 1.0f, 1.0f, 1.0f );
	vBottomRight = Vector3D( -1.0f, -1.0f, -1.0f );
	red = 128;
	green = 255;
	blue = 0;
}

CModel::~CModel(void)
{
}

void CModel::DrawSphere(void) 
{ 
	glPushMatrix();
		glTranslatef(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);
		glColor3f(1.0,1.0,1.0); 
		//glutSolidSphere( 0.1f, 9, 9); 
	glPopMatrix();

	glPushMatrix();
		glTranslatef(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);
		glColor3f(1.0,1.0,1.0); 
		//glutSolidSphere( 0.1f, 9, 9); 
	glPopMatrix();
} 

void CModel::Draw(void)
{
	glPushMatrix();

	glColor3f(red, green, blue);
	glBegin(GL_QUADS);

	/*      This is the top face*/
	glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);
	glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vBottomRight.m_z);
	glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vBottomRight.m_z);
	glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vTopLeft.m_z);

	/*      This is the front face*/
	glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);
	glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vTopLeft.m_z);
	glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vTopLeft.m_z);
	glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vTopLeft.m_z);


	/*      This is the right face*/
	glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);
	glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vTopLeft.m_z);
	glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vBottomRight.m_z);
	glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vBottomRight.m_z);

	/*      This is the left face*/
	glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vTopLeft.m_z);
	glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vBottomRight.m_z);
	glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);
	glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vTopLeft.m_z);

	/*      This is the bottom face*/
	glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vTopLeft.m_z);
	glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vBottomRight.m_z);
	glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);
	glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vTopLeft.m_z);

	/*      This is the back face*/
	glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vBottomRight.m_z);
	glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vBottomRight.m_z);
	glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);
	glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vBottomRight.m_z);

	glEnd();
	glPopMatrix();

		// Draw the lines of the Frustum
		glColor3f(1.0f, 1.0f, 1.0f);
		glLineWidth(5);
		glBegin( GL_LINES );

			// Lines for the top face
			glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);
			glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vBottomRight.m_z);

			glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vBottomRight.m_z);
			glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vBottomRight.m_z);

			glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vBottomRight.m_z);
			glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vTopLeft.m_z);

			glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vTopLeft.m_z);
			glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);

			// Lines for the bottom face
			glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vTopLeft.m_z);
			glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vBottomRight.m_z);

			glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vBottomRight.m_z);
			glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);

			glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);
			glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vTopLeft.m_z);

			glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vTopLeft.m_z);
			glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vTopLeft.m_z);

			// Lines for the sides of the box
			glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);
			glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vTopLeft.m_z);

			glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vTopLeft.m_z);
			glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vTopLeft.m_z);

			glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vBottomRight.m_z);
			glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vBottomRight.m_z);

			glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vBottomRight.m_z);
			glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);

		glEnd();
		glLineWidth(1);

	DrawSphere();
}

void CModel::SetColor(const float red, const float green, const float blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

// Get the top left of the bounding box of the instance
Vector3D CModel::GetTopLeft(void)
{
	return Vector3D(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);
}

// Get the bottomright of the bounding box of the instance
Vector3D CModel::GetBottomRight(void)
{
	return Vector3D(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);
}