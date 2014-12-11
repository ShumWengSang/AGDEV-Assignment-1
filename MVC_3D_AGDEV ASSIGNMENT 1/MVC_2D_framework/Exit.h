#pragma once
#include "Entity.h"
#include "texture.h"
class Exit :
	public Entity
{
public:
	Exit();
	~Exit();

	void Draw();
	int textureID[6];
};

