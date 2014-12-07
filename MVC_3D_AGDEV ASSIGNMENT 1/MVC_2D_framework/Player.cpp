#include "Player.h"


Player::Player()
{
	MAXSPEED = 10;
	u = 0; v = 0; u1 = 0; v1 = 0;
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
}

void Player::MoveMeForward(bool mode, float timeDiff)
{
	if (mode)
	{
		u = v;
		v = u + 1.f * timeDiff;

		Walk(v, true);

	}
	else
	{
		u = v;
		v = u - 1.f  * timeDiff;

		Walk(v, false);
	}
}
void Player::MoveMeSideways(bool mode, float timeDiff)
{
	if (mode)
	{
		u1 = v1;
		v1 = u1 + 1.f * timeDiff;
		Strafe(v1, true);
	}
	else
	{
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