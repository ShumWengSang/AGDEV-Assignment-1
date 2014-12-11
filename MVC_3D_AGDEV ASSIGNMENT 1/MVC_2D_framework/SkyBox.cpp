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
	Top = 100;
	Bottom = -50;
	Left = 100;
	Right = -100;
	Near = -100;
	Far = 100;
	Width = Left - Right;
	Height = Top - Bottom;
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
	glTexCoord2f(0, 0); glVertex3f(Left,Bottom, Near);
	glTexCoord2f(1, 0); glVertex3f(Right, Bottom, Near);
	glTexCoord2f(1, 1); glVertex3f(Right, Top, Near);
	glTexCoord2f(0, 1); glVertex3f(Left, Top, Near);
	glEnd();

	// Render the back quad
	glBindTexture(GL_TEXTURE_2D, textureID[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(Right, Bottom, Far);
	glTexCoord2f(1, 0); glVertex3f(Left, Bottom, Far);
	glTexCoord2f(1, 1); glVertex3f(Left, Top, Far);
	glTexCoord2f(0, 1); glVertex3f(Right, Top, Far);

	glEnd();

	// Render the left quad
	glBindTexture(GL_TEXTURE_2D, textureID[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(Left, Bottom, Far);
	glTexCoord2f(1, 0); glVertex3f(Left, Bottom, Near);
	glTexCoord2f(1, 1); glVertex3f(Left, Top, Near);
	glTexCoord2f(0, 1); glVertex3f(Left, Top, Far);
	glEnd();

	// Render the right quad
	glBindTexture(GL_TEXTURE_2D, textureID[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(Right, Bottom, Near);
	glTexCoord2f(1, 0); glVertex3f(Right, Bottom, Far);
	glTexCoord2f(1, 1); glVertex3f(Right, Top, Far);
	glTexCoord2f(0, 1); glVertex3f(Right, Top, Near);
	glEnd();

	// Render the top quad
	glBindTexture(GL_TEXTURE_2D, textureID[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(Right, Top, Near);
	glTexCoord2f(0, 0); glVertex3f(Right, Top, Far);
	glTexCoord2f(1, 0); glVertex3f(Left, Top, Far);
	glTexCoord2f(1, 1); glVertex3f(Left, Top, Near);
	glEnd();

	// Render the bottom quad
	glBindTexture(GL_TEXTURE_2D, textureID[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(Right, Bottom, Near);
	glTexCoord2f(0, 1); glVertex3f(Right, Bottom, Far);
	glTexCoord2f(1, 1); glVertex3f(Left, Bottom, Far);
	glTexCoord2f(1, 0); glVertex3f(Left, Bottom, Near);
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