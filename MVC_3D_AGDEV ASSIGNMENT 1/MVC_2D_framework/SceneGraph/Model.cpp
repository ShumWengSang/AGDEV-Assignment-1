#ifndef __MODEL_H__
#include "Model.h"
#endif


#include <stdio.h>


CModel::CModel(void) : theObj()
{
	vTopLeft = Vector3D( 1.0f, 1.0f, 1.0f );
	vBottomRight = Vector3D( -1.0f, -1.0f, -1.0f );
	red = 128;
	green = 255;
	blue = 0;

	NearTopLeft.Set(1, 1, 1);
	NearTopRight.Set(-1, 1, 1);
	NearBottomLeft.Set(1, -1, 1);
	NearBottomRight.Set(-1, -1, 1);

	FarTopLeft.Set(1, 1, -1);
	FarTopRight.Set(-1, 1, -1);
	FarBottomLeft.Set(1, -1, -1);
	FarBottomRight.Set(-1, -1, -1);

	states = Cube;
}

CModel::~CModel(void)
{
}

void CModel::InitObj()
{
	theObj = new Obj();
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
	switch (states)
	{
	case Model:
		theObj->RenderMesh();
		break;
	case Cube:
		DrawCube();
		break;
	case Nothing:
		break;
	default:
		break;
	}
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

void CModel::DrawCube(void)
{
	//glPushMatrix();

	//glColor3f(red, green, blue);
	//glBegin(GL_QUADS);
	//glEnable(GL_TEXTURE_2D);

	///*      This is the top face*/
	//glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	//glTexCoord2f(0,0);
	//glTexCoord2f(0,1);
	//glTexCoord2f(1,1);
	//glTexCoord2f(1,0);
	//glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);
	//glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vBottomRight.m_z);
	//glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vBottomRight.m_z);
	//glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vTopLeft.m_z);

	///*      This is the front face*/
	//glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	//glTexCoord2f(0, 0);
	//glTexCoord2f(0, 1);
	//glTexCoord2f(1, 1);
	//glTexCoord2f(1, 0);
	//glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);
	//glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vTopLeft.m_z);
	//glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vTopLeft.m_z);
	//glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vTopLeft.m_z);


	///*      This is the right face*/
	//glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	//glTexCoord2f(0, 0);
	//glTexCoord2f(0, 1);
	//glTexCoord2f(1, 1);
	//glTexCoord2f(1, 0);
	//glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);
	//glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vTopLeft.m_z);
	//glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vBottomRight.m_z);
	//glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vBottomRight.m_z);

	///*      This is the left face*/
	//glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	//glTexCoord2f(0, 0);
	//glTexCoord2f(0, 1);
	//glTexCoord2f(1, 1);
	//glTexCoord2f(1, 0);
	//glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vTopLeft.m_z);
	//glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vBottomRight.m_z);
	//glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);
	//glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vTopLeft.m_z);

	///*      This is the bottom face*/
	//glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	//glTexCoord2f(0, 0);
	//glTexCoord2f(0, 1);
	//glTexCoord2f(1, 1);
	//glTexCoord2f(1, 0);
	//glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vTopLeft.m_z);
	//glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vBottomRight.m_z);
	//glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);
	//glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vTopLeft.m_z);

	///*      This is the back face*/
	//glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	//glTexCoord2f(0, 0);
	//glTexCoord2f(0, 1);
	//glTexCoord2f(1, 1);
	//glTexCoord2f(1, 0);
	//glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vBottomRight.m_z);
	//glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vBottomRight.m_z);
	//glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);
	//glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vBottomRight.m_z);

	//glEnd();
	//glPopMatrix();
	//glDisable(GL_TEXTURE_2D);

	//// Draw the lines of the BOXES
	//glColor3f(1.0f, 1.0f, 1.0f);
	//glLineWidth(5);
	//glBegin(GL_LINES);

	//// Lines for the top face
	//glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);
	//glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vBottomRight.m_z);

	//glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vBottomRight.m_z);
	//glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vBottomRight.m_z);

	//glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vBottomRight.m_z);
	//glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vTopLeft.m_z);

	//glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vTopLeft.m_z);
	//glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);

	//// Lines for the bottom face
	//glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vTopLeft.m_z);
	//glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vBottomRight.m_z);

	//glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vBottomRight.m_z);
	//glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);

	//glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);
	//glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vTopLeft.m_z);

	//glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vTopLeft.m_z);
	//glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vTopLeft.m_z);

	//// Lines for the sides of the box
	//glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);
	//glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vTopLeft.m_z);

	//glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vTopLeft.m_z);
	//glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vTopLeft.m_z);

	//glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vBottomRight.m_z);
	//glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vBottomRight.m_z);

	//glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vBottomRight.m_z);
	//glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);

	//glEnd();
	//glLineWidth(1);

	//DrawSphere();

	//glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	//	glDisable(GL_DEPTH_TEST);
	//glDisable(GL_LIGHTING);
	//glDisable(GL_BLEND);

	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Just in case we set all vertices to white.
	glColor4f(1, 1, 1, 1);

	// Render the front quad
	glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);
	glTexCoord2f(1, 0); glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vTopLeft.m_z);
	glTexCoord2f(1, 1); glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vTopLeft.m_z);
	glTexCoord2f(0, 1); glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vTopLeft.m_z);
	glEnd();

	// Render the back quad
	glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vBottomRight.m_z);
	glTexCoord2f(1, 0); glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vBottomRight.m_z);
	glTexCoord2f(1, 1); glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);
	glTexCoord2f(0, 1); glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vBottomRight.m_z);

	glEnd();

	// Render the left quad
	glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vTopLeft.m_z);
	glTexCoord2f(1, 0); glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vBottomRight.m_z);
	glTexCoord2f(1, 1); glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);
	glTexCoord2f(0, 1); glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vTopLeft.m_z);
	glEnd();

	// Render the right quad
	glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);
	glTexCoord2f(1, 0); glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vTopLeft.m_z);
	glTexCoord2f(1, 1); glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vBottomRight.m_z);
	glTexCoord2f(0, 1); glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vBottomRight.m_z);
	glEnd();

	// Render the top quad
	glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);
	glTexCoord2f(0, 0); glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vBottomRight.m_z);
	glTexCoord2f(1, 0); glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vBottomRight.m_z);
	glTexCoord2f(1, 1); glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vTopLeft.m_z);
	glEnd();

	// Render the bottom quad
	glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vTopLeft.m_z);
	glTexCoord2f(0, 1); glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vBottomRight.m_z);
	glTexCoord2f(1, 1); glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);
	glTexCoord2f(1, 0); glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vTopLeft.m_z);
	glEnd();

	glDisable(GL_TEXTURE_2D);

}