#pragma once
#include "Entity.h"
#include "Math.h"
class Player :
	public Entity
{
public:
	Player();
	~Player();
	float u, u1, v, v1;


	int MAXSPEED;

	void MoveMeForward(bool , float );
	void MoveMeSideways(bool, float);

	void Walk(GLfloat delta, bool mode);
	void Strafe(GLfloat delta, bool mode);

	void deceleratestraight( float timeDiff);
	void deceleratesideways(float timeDiff);

	void ApplyRotatePlayer(float angle, int, int, int);
	void ApplyRotatePlayer(Vector3D);
};

