#include "Camera.h"
#include <iostream>


Camera::Camera(void)
: MAXSPEED_MOVE(1.0f)
{
	SetCameraType(LAND_CAM);
	Reset();
	angle = 0;
	SetPosition(0.0, 2.0, -5.0);
	SetDirection(0.0, 0.0, 1.0);
	u = 0; v = 0; u1 = 0; v1 = 0;
	fov = 50;
	onground = true;
	yvel = 0;
	jump = 0;
	gravity = -0.5;
	Distance = 10;
}

Camera::Camera(CAM_TYPE ct)
: MAXSPEED_MOVE(1.0f)
{
	SetCameraType(ct);
	Reset();
	angle = 0;
	u = 0; v = 0; u1 = 0; v1 = 0;
	fov = 50;
	onground = true;
	yvel = 0;
	jump = 0;
	gravity = -0.5;
	Distance = 10;
}

Camera::~Camera(void)
{
}

void Camera::SetCameraType(CAM_TYPE ct) {
	CameraType = ct;
}

void Camera::Reset(void)
{
	Position = Vector3D(0.0, 0.0, 0.0);
	Along = Vector3D(1.0, 0.0, 0.0);
	Up = Vector3D(0.0, 1.0, 0.0);
	Forward = Vector3D(0.0, 0.0, -1.0);
	//	Update();

	MAXSPEED_MOVE = 1.0f;
}

void Camera::Update() {

	gluLookAt(Position.m_x, Position.m_y, Position.m_z,
		Position.m_x + Forward.m_x, Position.m_y + Forward.m_y, Position.m_z + Forward.m_z,
		0.0f, 1.0f, 0.0f);
}

void Camera::Update(Vector3D theTarget) {

	gluLookAt(Position.m_x, Position.m_y, Position.m_z,
		theTarget.m_x, theTarget.m_y, theTarget.m_z ,
		0.0f, 1.0f, 0.0f);
}

Vector3D Camera::GetPosition() {
	return Position;
}

void Camera::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	//Code here to find position of camera.
	//Vector3D camerapos = CalculateDistance(Vector3D(x, y, z));

	this->Position.Set(x , y , z );
}

void Camera::SetDirection(GLfloat x, GLfloat y, GLfloat z)
{
	this->Forward.Set(x, y, z);
}

void Camera::Pitch(GLfloat theta)
{
	Forward.m_y -= theta;
	if (Forward.m_y > 3.142f)
		Forward.m_y = 3.142f;
	else if (Forward.m_y < -3.142f)
		Forward.m_y = -3.142f;
}
void Camera::Yaw(GLfloat theta)
{
	Forward.m_x = sin(-theta);
	Forward.m_z = -cos(-theta);
}
void Camera::Roll(GLfloat theta)
{
}
void Camera::Walk(GLfloat delta, bool mode)
{
	if (mode){
		if (delta > MAXSPEED_MOVE)
			delta = MAXSPEED_MOVE;
	}
	else{
		if (delta < -MAXSPEED_MOVE)
			delta = -MAXSPEED_MOVE;
	}
	Position.Set(Position.m_x + Forward.m_x * delta, Position.m_y, Position.m_z + Forward.m_z * delta);
}
void Camera::Strafe(GLfloat delta, bool mode)
{
	if (mode){
		if (delta > MAXSPEED_MOVE)
			delta = MAXSPEED_MOVE;
	}
	else{
		if (delta < -MAXSPEED_MOVE)
			delta = -MAXSPEED_MOVE;
	}
	Along = Forward.CrossVector3D(Up);
	Along.NormalizeVector3D();
	Position.Set(Position.m_x + Along.m_x * delta,
		Position.m_y + Along.m_y * delta,
		Position.m_z + Along.m_z * delta);


}
void Camera::Fall(float vel)
{
	Position.Set(Position.m_x , Position.m_y - vel, Position.m_z );
}

// Toggle HUD mode
void Camera::SetHUD(bool m_bHUDmode)
{
	if (m_bHUDmode)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, 800, 600, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	}
	else
	{
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
		glEnable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_DEPTH_TEST);
	}
}

// Get the direction of the camera
Vector3D Camera::GetDirection(void)
{
	return Forward;
}

void Camera::moveMeForward(bool mode, float timeDiff)
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

void Camera::moveMeSideway(bool mode, float timeDiff)
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

void Camera::calculations(float diffX, float diffY)
{
	Pitch(diffY * 3.142f / 180.0f);

	angle += (float)diffX * 3.142f / 180.0f;
	if (angle > 6.284f)
		angle -= 6.284f;
	else if (angle < -6.284f)
		angle += 6.284f;

	Yaw(-angle);
}

void Camera::deceleratestraight(float timeDiff)
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

void Camera::deceleratesideways(float timeDiff)
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

void Camera::recoil(float y_recoil, float x_recoil)
{
	Vector3D temp(GetDirection());
	SetDirection(temp.m_x + x_recoil, temp.m_y + y_recoil, temp.m_z);
	
}

void Camera::setFOV(float fov)
{
	this->fov = fov;
}

void Camera::crouch()
{
	Position.Set(Position.m_x , Position.m_y - 100 , Position.m_z );
}

Vector3D Camera::CalculateDistance(Vector3D theFirstPosition)
{
	Vector3D theSecondPosition;

	theSecondPosition = Forward * Distance;

	return theSecondPosition;
}