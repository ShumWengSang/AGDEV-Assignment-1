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

MVC_Model::MVC_Model(void) :
thirdpersoncamera(),
theFrustum(NULL)
{
	m_timer=MVCTime::GetInstance();
	x = 0; y = 0; z = 0;
	distance = 10;
	theFrustum = new CFrustum();
	thirdpersoncamera = new ThirdPersonCamera();
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

	// Scene Graph
	theRoot = new CSceneNode();
	CModel* newModel = new CModel();
	newModel->SetColor(0.0, 0.0, 1.0);
	cout << theRoot->SetNode(new CTransform(3.5, 0, 0), newModel) << endl;

	newModel = new CModel();
	newModel->SetColor(0.0, 1.0, 1.0);
	cout << theRoot->AddChild(new CTransform(0, 2, 0), newModel) << endl;

	newModel = new CModel();
	newModel->SetColor(1.0, 1.0, 0.0);
	cout << theRoot->AddChild(new CTransform(0, 2, -2), newModel) << endl;

	newModel = new CModel();
	newModel->SetColor(1.0, 0.0, 1.0);
	cout << theRoot->AddChild(new CTransform(0, 2, -4), newModel) << endl;

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

	if (!LoadTGA(&SkyBoxTextures[0], "SkyBox/bleached_front.tga"))				// Load The Font Texture
		return false;	// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[1], "SkyBox/bleached_back.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[2], "SkyBox/bleached_left.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[3], "SkyBox/bleached_right.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[4], "SkyBox/bleached_top.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[5], "SkyBox/red_down.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False


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
	//theCamera.calculations(diffX, diffY);

	m_timer->UpdateTime();
	thirdpersoncamera->Update();
	if (m_timer->TestFramerate())
	{
		m_testX += m_moveX*m_timer->GetDelta();
		m_testY += m_moveY*m_timer->GetDelta();
	}
	if (theFrustum)
	{
		theFrustum->Update();
		FrustumChecking();

		if (theRoot)
		{
			theRoot->ApplyRotate(0.5f, 0, 1, 0);
		}
	}
}

void MVC_Model::FrustumChecking()
{
	bool m_bContainmentCheck_TopLeft = theFrustum->ContainmentCheck(theRoot->GetTopLeft());
	bool m_bContainmentCheck_BottomRight = theFrustum->ContainmentCheck(theRoot->GetBottomRight());

	bool m_bContainmentCheck_NearTopLeft = theFrustum->ContainmentCheck(theRoot->GetNearTopLeft());
	bool m_bContainmentCheck_NearBottomRight = theFrustum->ContainmentCheck(theRoot->GetNearTopRight());
	bool m_bContainmentCheck_NearTopRight = theFrustum->ContainmentCheck(theRoot->GetNearBottomLeft());
	bool m_bContainmentCheck_NearBottomLeft = theFrustum->ContainmentCheck(theRoot->GetNearBottomRight());

	bool m_bContainmentCheck_FarTopLeft = theFrustum->ContainmentCheck(theRoot->GetFarTopLeft());
	bool m_bContainmentCheck_FarBottomRight = theFrustum->ContainmentCheck(theRoot->GetFarTopRight());
	bool m_bContainmentCheck_FarTopRight = theFrustum->ContainmentCheck(theRoot->GetFarBottomLeft());
	bool m_bContainmentCheck_FarBottomLeft = theFrustum->ContainmentCheck(theRoot->GetFarBottomRight());

	if (m_bContainmentCheck_NearTopLeft && m_bContainmentCheck_NearTopRight
		&& m_bContainmentCheck_NearBottomLeft && m_bContainmentCheck_NearBottomRight
		&& m_bContainmentCheck_FarTopLeft && m_bContainmentCheck_FarTopRight
		&& m_bContainmentCheck_FarBottomLeft && m_bContainmentCheck_FarBottomRight)
	{
		// The scene graph is inside the frustum!
		theRoot->SetColor(1.0f, 1.0f, 1.0f);
	}
	else
	{
		if (!(m_bContainmentCheck_NearTopLeft || m_bContainmentCheck_NearTopRight
			|| m_bContainmentCheck_NearBottomLeft || m_bContainmentCheck_NearBottomRight
			|| m_bContainmentCheck_FarTopLeft || m_bContainmentCheck_FarTopRight
			|| m_bContainmentCheck_FarBottomLeft || m_bContainmentCheck_FarBottomRight))
		{
			//The scene graph is not inside the frustum
			theRoot->SetColor(0, 0, 0);

		}

		else
		{
			theRoot->SetColor(1, 0, 0);
			//Scene graph halfway in.
		}
		for (int i = 0; i < theRoot->GetNumOfChild(); i++)
		{
			Vector3D NearTopLeft, NearTopRight, NearBottomLeft, NearBottomRight;
			Vector3D FarTopLeft, FarTopRight, FarBottomLeft, FarBottomRight;
			const int childID = theRoot->GetSceneNodeID() * 10 + i + 1;
			if (
				(theRoot->GetNearTopLeft(childID, NearTopLeft))
				&& (theRoot->GetNearTopRight(childID, NearTopRight))
				&& (theRoot->GetNearBottomLeft(childID, NearBottomLeft))
				&& (theRoot->GetNearBottomRight(childID, NearBottomRight))

				&& (theRoot->GetFarTopLeft(childID, FarTopLeft))
				&& (theRoot->GetFarTopRight(childID, FarTopRight))
				&& (theRoot->GetFarBottomLeft(childID, FarBottomLeft))
				&& (theRoot->GetFarBottomRight(childID, FarBottomRight))
				)
			{
				bool m_bCheckNearTopLeft = theFrustum->ContainmentCheck(NearTopLeft);
				bool m_bCheckNearTopRight = theFrustum->ContainmentCheck(NearTopRight);
				bool m_bCheckNearBottomLeft = theFrustum->ContainmentCheck(NearBottomLeft);
				bool m_bCheckNearBottomRight = theFrustum->ContainmentCheck(NearBottomRight);

				bool m_bCheckFarTopLeft = theFrustum->ContainmentCheck(FarTopLeft);
				bool m_bCheckFarTopRight = theFrustum->ContainmentCheck(FarTopRight);
				bool m_bCheckFarBottomLeft = theFrustum->ContainmentCheck(FarBottomLeft);
				bool m_bCheckFarBottomRight = theFrustum->ContainmentCheck(FarBottomRight);

				if ((m_bCheckNearTopLeft) &&
					(m_bCheckNearTopRight) &&
					(m_bCheckNearBottomLeft) &&
					(m_bCheckNearBottomRight) &&

					(m_bCheckFarTopLeft) &&
					(m_bCheckFarTopRight) &&
					(m_bCheckFarBottomLeft) &&
					(m_bCheckFarBottomRight)
					)
				{
					// The child is INSIDE THE FRUSTUM
					theRoot->SetColorForChild(childID, 1, 1.0f, 1);
				}
				else if (!
					((m_bCheckNearTopLeft) ||
					(m_bCheckNearTopRight) ||
					(m_bCheckNearBottomLeft) ||
					(m_bCheckNearBottomRight) ||

					(m_bCheckFarTopLeft) ||
					(m_bCheckFarTopRight) ||
					(m_bCheckFarBottomLeft) ||
					(m_bCheckFarBottomRight)
					))
				{
					// The child is OUTSIDE of the frustum!
					theRoot->SetColorForChild(childID, 0, 0, 0);
				}
				else
				{
					theRoot->SetColorForChild(childID, 1, 0, 0.0f);
				}
			}
		}
	}
}
