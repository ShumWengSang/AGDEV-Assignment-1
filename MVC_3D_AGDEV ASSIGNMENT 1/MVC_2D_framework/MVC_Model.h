#ifndef __MVC_MODEL_H__
#define __MVC_MODEL_H__

#ifndef __TEXTURE_H__
#include "texture.h"
#endif

#ifndef __VECTOR_H__
#include <vector>
#endif

#ifndef __CAMERA_H__
#include "camera.h"
#endif

#ifndef __SKYBOX_H__
#include "SkyBox.h"
#endif

#ifndef __MOUSE_H__
#include "Mouse.h"
#endif

#ifndef __CFRUSTUM_H__
#include "Frustum.h"
#endif

#ifndef __HUD_H__
#include "HUD.h"
#endif

class MVCTime;

class MVC_Model
{
public:
	MVC_Model(void);
	~MVC_Model(void);
	// Update the model
	void Update(void);
	bool Init(float fpsLimit);
	bool InitPhase2(void);//init after view's init e.g Textures,stuff requiring screen size
	
	float m_worldSizeX;
	float m_worldSizeY;

	float m_testX;
	float m_testY;
	float m_moveX;
	float m_moveY;

	TextureImage SkyBoxTextures[6];

	MVCTime* m_timer;
	CFrustum* theFrustum;

	HUD theHUD;
	SkyBox theBox;
	Camera theCamera;

	//DISTANCE FROM OBJECT TO CAMERA
	int distance;

	//TESTING CODES
	float x, y, z;
private: 
};

#endif