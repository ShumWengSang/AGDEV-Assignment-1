#pragma once
#include "vector3D.h"
#include "Quarternion.h"
#include "MVC_View.h"

class QuarternionCamera
{
public:
	QuarternionCamera();
	~QuarternionCamera();

	Vector3D  Position;
	float Angle;
	float Distance;
	float YawRotation;
	//One can be anything greater than zero
	//variable2 is the camera's position
	//variable 3 is the subject's yaw rotation

	void Init();
	void MouseCalculations(float Diffx, float Diffy);

	void FindPosition(Vector3D theTargetPosition);
	void Update(void(MVC_View::*DrawObject)(void), void(MVC_View::*DrawScene)(void), MVC_View * theView);
};

