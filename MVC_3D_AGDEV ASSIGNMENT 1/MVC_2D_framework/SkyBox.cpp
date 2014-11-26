#include "SkyBox.h"

SkyBox::SkyBox()
{
	Init();
}


SkyBox::~SkyBox()
{
}

void SkyBox::Init()
{
	Top = 10;
	Bottom = -10;
	Left = 10;
	Right = -10;
	Near = -10;
	Far = 10;
}

void SkyBox::Draw()
{
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
	glBindTexture(GL_TEXTURE_2D, textureID[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(10.0f, -10.0f, Near);
	glTexCoord2f(1, 0); glVertex3f(-10.0f, -10.0f, Near);
	glTexCoord2f(1, 1); glVertex3f(-10.0f, 10.0f, Near);
	glTexCoord2f(0, 1); glVertex3f(10.0f, 10.0f, Near);
	glEnd();

	// Render the back quad
	glBindTexture(GL_TEXTURE_2D, textureID[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-10.0f, -10.0f, Far);
	glTexCoord2f(1, 0); glVertex3f(10.0f, -10.0f, Far);
	glTexCoord2f(1, 1); glVertex3f(10.0f, 10.0f, Far);
	glTexCoord2f(0, 1); glVertex3f(-10.0f, 10.0f, Far);

	glEnd();

	// Render the left quad
	glBindTexture(GL_TEXTURE_2D, textureID[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(Left, -10.0f, 10.0f);
	glTexCoord2f(1, 0); glVertex3f(Left, -10.0f, -10.0f);
	glTexCoord2f(1, 1); glVertex3f(Left, 10.0f, -10.0f);
	glTexCoord2f(0, 1); glVertex3f(Left, 10.0f, 10.0f);
	glEnd();

	// Render the right quad
	glBindTexture(GL_TEXTURE_2D, textureID[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(Right, -10.0f, -10.0f);
	glTexCoord2f(1, 0); glVertex3f(Right, -10.0f, 10.0f);
	glTexCoord2f(1, 1); glVertex3f(Right, 10.0f, 10.0f);
	glTexCoord2f(0, 1); glVertex3f(Right, 10.0f, -10.0f);
	glEnd();

	// Render the top quad
	glBindTexture(GL_TEXTURE_2D, textureID[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-10.0f, Top, -10.0f);
	glTexCoord2f(0, 0); glVertex3f(-10.0f, Top, 10.0f);
	glTexCoord2f(1, 0); glVertex3f(10.0f, Top, 10.0f);
	glTexCoord2f(1, 1); glVertex3f(10.0f, Top, -10.0f);
	glEnd();

	// Render the bottom quad
	glBindTexture(GL_TEXTURE_2D, textureID[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-10.0f, Bottom, -10.0f);
	glTexCoord2f(0, 1); glVertex3f(-10.0f, Bottom, 10.0f);
	glTexCoord2f(1, 1); glVertex3f(10.0f, Bottom, 10.0f);
	glTexCoord2f(1, 0); glVertex3f(10.0f, Bottom, -10.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	//	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_BLEND);

	// Restore enable bits and matrix
	//glPopAttrib();
}

float SkyBox::GetTop()
{
	return Top;
}

float SkyBox::GetBottom()
{
	return Bottom;
}

float SkyBox::GetLeft()
{
	return Left;
}

float SkyBox::GetRight()
{
	return Right;
}

float SkyBox::GetNear()
{
	return Near;
}

float SkyBox::GetFar()
{
	return Far;
}