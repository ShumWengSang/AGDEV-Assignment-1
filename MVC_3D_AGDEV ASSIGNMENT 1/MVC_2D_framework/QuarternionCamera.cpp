#include "QuarternionCamera.h"


QuarternionCamera::QuarternionCamera()
{
	Init();
}


QuarternionCamera::~QuarternionCamera()
{
}

void QuarternionCamera::MouseCalculations(float Diffx, float Diffy)
{

}

void QuarternionCamera::Init()
{
	Distance = 10;
	YawRotation = 20;
	Angle = 0;
}

void QuarternionCamera::FindPosition(Vector3D theTargetPosition)
{
	Position.m_x = Distance * sin((Angle)* PI / 180) + theTargetPosition.m_x;
	Position.m_z = Distance * cos((Angle)* PI / 180) + theTargetPosition.m_y;
}

void QuarternionCamera::Update(void(MVC_View::* DrawObject)(void), void(MVC_View::*DrawScene)(void), MVC_View * theView)
{

	// First I like to draw the subject. Basically you are just drawing the subject directly in front of you
	glTranslatef(0.0f, 0.0f, -Distance);
	((theView)->*(DrawObject))();

	//You reset the view and now any scenery or world that you want to draw is drawn.
	glLoadIdentity();
	glRotatef(360.0f - YawRotation, 0.0f, 1.0f, 0.0f);
	glTranslatef(-Position.m_x, 0.0f, -Position.m_y);
	((theView)->*(DrawScene))();
}