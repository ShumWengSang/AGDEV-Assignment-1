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
	case Sphere:
		DrawSphere();
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

void CModel::DrawSphere()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();


	float radius = vBottomRight.m_y - vTopLeft.m_y;
	//Make sure it is not 0
	if (radius < 0)
		radius = -radius;
	radius /= 2;


	GLUquadricObj* Sphere;
	Sphere = gluNewQuadric();

	glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(Sphere, 1);
	gluSphere(Sphere, radius, 20, 20);
	gluDeleteQuadric(Sphere);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void CModel::DrawCube(void)
{

	glEnable(GL_TEXTURE_2D);

	// Just in case we set all vertices to white.
	glColor3f(red, green, blue);

	// Render the front quad
	if (theObj)
	glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vBottomRight.m_z);
	glTexCoord2f(1, 0); glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vBottomRight.m_z);
	glTexCoord2f(1, 1); glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vBottomRight.m_z);
	glTexCoord2f(0, 1); glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);
	glEnd();

	// Render the back quad
	if (theObj)
	glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vTopLeft.m_z);
	glTexCoord2f(1, 0); glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);
	glTexCoord2f(1, 1); glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vTopLeft.m_z);
	glTexCoord2f(0, 1); glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vTopLeft.m_z);

	glEnd();

	// Render the left quad
	if (theObj)
	glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vTopLeft.m_z);
	glTexCoord2f(1, 0); glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vTopLeft.m_z);
	glTexCoord2f(1, 1); glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vBottomRight.m_z);
	glTexCoord2f(0, 1); glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);
	glEnd();

	// Render the right quad
	if (theObj)
	glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vBottomRight.m_z);
	glTexCoord2f(1, 0); glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vBottomRight.m_z);
	glTexCoord2f(1, 1); glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);
	glTexCoord2f(0, 1); glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vTopLeft.m_z);
	glEnd();

	// Render the top quad
	if (theObj)
	glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vBottomRight.m_z);
	glTexCoord2f(0, 0); glVertex3f(vTopLeft.m_x, vTopLeft.m_y, vTopLeft.m_z);
	glTexCoord2f(1, 0); glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vTopLeft.m_z);
	glTexCoord2f(1, 1); glVertex3f(vBottomRight.m_x, vTopLeft.m_y, vBottomRight.m_z);
	glEnd();

	// Render the bottom quad
	if (theObj)
	glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vBottomRight.m_z);
	glTexCoord2f(0, 1); glVertex3f(vTopLeft.m_x, vBottomRight.m_y, vTopLeft.m_z);
	glTexCoord2f(1, 1); glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vTopLeft.m_z);
	glTexCoord2f(1, 0); glVertex3f(vBottomRight.m_x, vBottomRight.m_y, vBottomRight.m_z);
	glEnd();


	glDisable(GL_TEXTURE_2D);

}