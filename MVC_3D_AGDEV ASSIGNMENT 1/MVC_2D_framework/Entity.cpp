#include "Entity.h"


Entity::Entity()
{
	m_Position.Set(0, 0, 0);
	m_Direction.Set(0, 0, -1);
	m_Velocity.Set(0, 0, 0);
}


Entity::~Entity()
{
}

void Entity::SetPos(Vector3D theNewPos)
{
	m_Position = theNewPos;
}

void Entity::SetPos(float x, float y, float z)
{
	m_Position.m_x = x;
	m_Position.m_y = y;
	m_Position.m_z = z;
}

Vector3D Entity::GetPos()
{
	return m_Position;
}

void Entity::SetDir(Vector3D theNewDir)
{
	m_Direction = theNewDir;
}

void Entity::SetDir(float x, float y, float z)
{
	m_Direction.m_x = x;
	m_Direction.m_y = y;
	m_Direction.m_z = z;
}

Vector3D Entity::GetDir()
{
	return m_Direction;
}

void Entity::SetVelo(Vector3D theNewVelo)
{
	m_Velocity = theNewVelo;
}

void Entity::SetVelo(int x, int y, int z)
{
	m_Velocity.m_x = x;
	m_Velocity.m_y = y;
	m_Velocity.m_z = z;
}

Vector3D Entity::GetVelo()
{
	return m_Velocity;
}

void Entity::update(float dt)
{

}

void Entity::CollisionEvent(Entity &other)
{

}

void Entity::SetDestruction(bool ToDestroy)
{
	Destroy = ToDestroy;
}

void Entity::Draw()
{

}