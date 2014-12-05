#pragma once

#ifndef __THIRDPERSONCAMERA_H__
#define __THIRDPERSONCAMERA_H__
#ifndef __VECTOR3D_H__
#include "vector3D.h"
#endif
//
//REDOING THE ENTIRE CAMERA FROM GROND UP WITH A
//THIRD PERSON CAMERA IN MIND
//
class ThirdPersonCamera
{
public:
	ThirdPersonCamera();
	~ThirdPersonCamera();

	Vector3D m_vPosition;								// The camera's position
	Vector3D m_vView;									// The camera's View
	Vector3D m_vUpVector;								// The camera's UpVector
	Vector3D m_vStrafe;									// The camera's Strafe. We want this once so we don't
														// calculate it all the time

	// This changes the position, view, and up vector of the camera.
	// This is primarily used for initialization
	void PositionCamera(float positionX, float positionY, float positionZ,
		float viewX, float viewY, float viewZ,
		float upVectorX, float upVectorY, float upVectorZ);

	// This rotates the camera's view around the position using axis-angle rotation
	void RotateView(float angle, float X, float Y, float Z);


	// This rotates the camera around a point (i.e. your character).
	// vCenter is the point that we want to rotate the position around.
	// Like the other rotate function, the x, y and z is the axis to rotate around.
	void RotateAroundPoint(Vector3D vCenter, float angle, float x, float y, float z);

	// This will move the camera forward or backward depending on the speed
	void MoveCamera(float speed);

	void MoveUpCamera(float speed);

	//This is to call the lookat.
	void UpdateLookAt();

	void StrafeCamera(float speed);

	void Update();
};

#endif