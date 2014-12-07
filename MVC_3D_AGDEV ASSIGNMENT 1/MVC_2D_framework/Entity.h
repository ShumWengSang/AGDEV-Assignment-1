#pragma once
#include "vector3D.h"
#include <vector>

enum EEntity{
	EXIT = 0,
	PLAYER
};

class Entity
{
protected:
	Vector3D m_Position;
	Vector3D m_Direction;
	Vector3D m_Velocity;
	bool Destroy;
public:
	Entity(void);
	~Entity(void);

	void SetPos(Vector3D theNewPos);
	void SetPos(float x, float y, float z);
	Vector3D GetPos();

	void SetDir(Vector3D theNewDir);
	void SetDir(float x, float y, float z);
	Vector3D GetDir();

	void SetVelo(Vector3D theNewVelo);
	void SetVelo(int x, int y, int z);
	Vector3D GetVelo();

	void SetDestruction(bool ToDestroy);

	virtual void update(float dt);

	virtual void CollisionEvent(Entity &other);
	
	virtual void Draw();
	EEntity ID;
};


