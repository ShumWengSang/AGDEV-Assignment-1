#include "Player.h"


Player::Player()
{
	MAXSPEED = 0.5;
	u = 0; v = 0; u1 = 0; v1 = 0;
	m_Position.Set(0, 2, 0);
	ToggleFrustum = false;
}



Player::~Player()
{
}


void Player::Walk(GLfloat delta, bool mode)
{
	if (mode){
		if (delta > MAXSPEED)
			delta = MAXSPEED;
	}
	else{
		if (delta < -MAXSPEED)
			delta = -MAXSPEED;
	}
	m_Position.Set(m_Position.m_x + m_Direction.m_x * delta, m_Position.m_y + m_Direction.m_y * delta, m_Position.m_z + m_Direction.m_z * delta);
	if (ToggleFrustum)
	{
		theFrustum->Update(GetPos(), GetDir());
	}
}
void Player::Strafe(GLfloat delta, bool mode)
{
	if (mode){
		if (delta > MAXSPEED)
			delta = MAXSPEED;
	}
	else{
		if (delta < -MAXSPEED)
			delta = -MAXSPEED;
	}
	Vector3D Along = m_Direction.CrossVector3D((Vector3D (0,1,0)));
	Along.NormalizeVector3D();
	m_Position.Set(m_Position.m_x + Along.m_x * delta,
		m_Position.m_y + Along.m_y * delta,
		m_Position.m_z + Along.m_z * delta);
	if (ToggleFrustum)
	{
		theFrustum->Update(GetPos(), GetDir());
	}
}

void Player::MoveMeForward(bool mode, float timeDiff)
{
	if (mode)
	{
		if (v < 0)
			v = 0;
		u = v;
		v = u + 1.f * timeDiff;

		Walk(v, true);

	}
	else
	{
		if (v > 0)
			v = 0;
		u = v;
		v = u - 1.f  * timeDiff;

		Walk(v, false);
	}
}
void Player::MoveMeSideways(bool mode, float timeDiff)
{
	if (mode)
	{
		if (v1 < 0)
			v1 = 0;
		u1 = v1;
		v1 = u1 + 1.f * timeDiff;
		Strafe(v1, true);
	}
	else
	{
		if (v1 > 0)
			v1 = 0;
		u1 = v1;
		v1 = u1 - 1.f * timeDiff;
		Strafe(v1, false);

	}
}

void Player::deceleratestraight(float timeDiff)
{
	if (v > 0)
	{
		v = u - 3.f * timeDiff;
		if (v < 0)
		{

			v = u = 0;
		}
	}
	else if (v < 0)
	{
		v = u + 3.f * timeDiff;
		if (v > 0)
		{
			v = u = 0;
		}
	}

	Walk(v, true);

	u = v;
}

void Player::deceleratesideways(float timeDiff)
{
	if (v1 > 0)
	{
		v1 = u1 - 3.f * timeDiff;
		if (v1 < 0)
		{

			v1 = u1 = 0;
		}
	}
	else if (v1 < 0)
	{
		v1 = u1 + 3.f * timeDiff;
		if (v1 > 0)
		{
			v1 = u1 = 0;
		}
	}

	Strafe(v1, true);

	u1 = v1;
}

void Player::ApplyRotatePlayer(float angle, int x, int y, int z)
{

}

void Player::ApplyRotatePlayer(Vector3D theNewDir)
{

}

void Player::DebugDraw()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	//	glDisable(GL_DEPTH_TEST);
	//glDisable(GL_LIGHTING);
	//glDisable(GL_BLEND);

	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Just in case we set all vertices to white.
	glColor3f(1, 1, 1);

	// Render the front quad
	//if (theObj)
		//glBindTexture(GL_TEXTURE_2D, theObj->theTexture.texID);
/*	glBegin(GL_LINES);
	glLineWidth(100);

	glTranslatef(m_Position.m_x , m_Position.m_y, m_Position.m_z);

	glPushMatrix();
	glVertex3f(m_Position.m_x, m_Position.m_y, m_Position.m_z);
	Vector3D newPos(m_Position + m_Direction * 10);
	glVertex3f(m_Position.m_x + (m_Direction.m_x * 10), m_Position.m_y + (m_Direction.m_y * 10), m_Position.m_z + (m_Direction.m_z * 10));
	glPopMatrix();



	glEnd();
	glPopMatrix();*/

	glDisable(GL_TEXTURE_2D);
}