//*************************************************************************************************************************************//
//
//	Original MVC framework made by Mr Toh Da Jun for DM2231 Game Development Techniques
//	Adapted and modified by Kennard Kee Wei Sheng
//	Framework taken with permission by Shum Weng Sang
//************************************************************************************************************************************//
#ifndef __MVC_MODEL_H__
#include "MVC_Model.h"
#endif
#ifndef __MVC_TIME_H__
#include "MVCtime.h"
#endif

#ifndef __TEXTURE_H__
#include "texture.h"
#endif

//extern bool LoadTGA(TextureImage *texture, char *filename);

MVC_Model::MVC_Model(void) : theCamera()
	, theFrustum(NULL)
{
	m_timer=MVCTime::GetInstance();
	x = 0; y = 0; z = 0;
	distance = 10;
	theFrustum = new CFrustum();
}

MVC_Model::~MVC_Model(void)
{
	if (theFrustum != NULL)
	{
		delete theFrustum;
		theFrustum = NULL;
	}
}

bool MVC_Model::Init(float fpsLimit)
{
	m_timer->Init(true,int(fpsLimit));
	m_moveX=m_moveY=0;
	return true;
}

bool MVC_Model::InitPhase2(void)
{
	m_testX=m_worldSizeX*0.5f;
	m_testY=m_worldSizeY*0.5f;

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	
	//if (!LoadTGA(&SkyBoxTextures[0], "SkyBox/north.tga"))				// Load The Font Texture
	//	return false;	// If Loading Failed, Return False
	//if (!LoadTGA(&SkyBoxTextures[1], "SkyBox/red_south.tga"))				// Load The Font Texture
	//	return false;										// If Loading Failed, Return False
	//if (!LoadTGA(&SkyBoxTextures[2], "SkyBox/red_west.tga"))				// Load The Font Texture
	//	return false;										// If Loading Failed, Return False
	//if (!LoadTGA(&SkyBoxTextures[3], "SkyBox/red_east.tga"))				// Load The Font Texture
	//	return false;										// If Loading Failed, Return False
	//if (!LoadTGA(&SkyBoxTextures[4], "SkyBox/red_top.tga"))				// Load The Font Texture
	//	return false;										// If Loading Failed, Return False
	//if (!LoadTGA(&SkyBoxTextures[5], "SkyBox/red_down.tga"))				// Load The Font Texture
	//	return false;										// If Loading Failed, Return False

	if (!LoadTGA(&SkyBoxTextures[0], "SkyBox/sky.tga"))				// Load The Font Texture
		return false;	// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[1], "SkyBox/sky.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[2], "SkyBox/sky.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[3], "SkyBox/sky.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[4], "SkyBox/sky.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[5], "SkyBox/sky.tga"))				// Load The Font Texture
		return false;	
	if (!LoadTGA(&theHUD.theMinimap, "SkyBox/sky.tga"))				// Load The Font Texture
		return false;	


	glDisable(GL_TEXTURE_2D);								// Disable Texture Mapping ( NEW )

	for (int i = 0; i < 5; i++)
	{
		theBox.textureID[i] = SkyBoxTextures[i].texID;//Set the TEX ID into the SkyBox itself
	}

	return true;
}

// Update the model
void MVC_Model::Update(void)
{
	m_timer->UpdateTime();
	if(m_timer->TestFramerate())
	{
		m_testX+=m_moveX*m_timer->GetDelta();
		m_testY+=m_moveY*m_timer->GetDelta();
	}
	if (theFrustum)
	{
		theFrustum->Update();
	}
	//theCamera.Update();
	//theCamera.Update();
}

