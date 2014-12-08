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
	Rotate = 0;
	m_timer=MVCTime::GetInstance();
	x = 0; y = 0; z = 0;
	distance = 10;
	theFrustum = new CFrustum();
	thirdpersoncamera = new ThirdPersonCamera();
	ObjectAngle = 270;
	PlayerID = 0;
	thePlayerData.theFrustum = theFrustum;
}

MVC_Model::~MVC_Model(void)
{
	if (theFrustum != NULL)
	{
		delete theFrustum;
		theFrustum = NULL;
	}
	if (thirdpersoncamera != NULL)
	{
		delete thirdpersoncamera;
		thirdpersoncamera = NULL;
	}
}

bool MVC_Model::Init(float fpsLimit)
{
	m_timer->Init(true,int(fpsLimit));
	m_moveX=m_moveY=0;

	theMaze.Draw();

	return true;
}

bool MVC_Model::InitPhase2(void)
{
	m_testX=m_worldSizeX*0.5f;
	m_testY=m_worldSizeY*0.5f;

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	

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

	if (!LoadTGA(&theImageDebugger, "button.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False


	glDisable(GL_TEXTURE_2D);								// Disable Texture Mapping ( NEW )



	for (int i = 0; i < 5; i++)
	{
		theBox.textureID[i] = SkyBoxTextures[i].texID;//Set the TEX ID into the SkyBox itself
	}
	// Scene Graph
	theRoot = new CSceneNode();

	CModel* newModel = new CModel();
	newModel->SetColor(0.0, 0.0, 1.0);
	newModel->states = WhatToDraw::Nothing;
	std::cout << theRoot->SetNode(new CTransform(0, 0, 0), newModel) << endl;


	//Find the ratio between skybox width and height and maze width and height.
	//We need this to fully fill our skybox with the maze.
	float ratiox = theBox.Width / WIDTH;
	float ratioy = theBox.Height / HEIGHT;

	int counter = 1;
	for (int MazeWidth = -0; MazeWidth < WIDTH; MazeWidth++)
	{
		for (int MazeHeight = -0; MazeHeight < HEIGHT; MazeHeight++)
		{
			if (theMaze.theMaze[MazeWidth][MazeHeight] == 0)
			{
				//This is a path, so don't make a wall here.
				cout << "EMPTY SPACE" << endl;
			}
			else if (theMaze.theMaze[MazeWidth][MazeHeight] == 1)
			{
				newModel = new CModel();
				newModel->InitObj();
				newModel->SetColor(1.0, 1.0, 0.0);
				newModel->theObj->theTexture = theImageDebugger;

				CTransform * theTransform = new CTransform((float)(MazeWidth - WIDTH / 2) * ratiox, 0, (float)(MazeHeight - HEIGHT / 2)* ratioy);

				if (theMaze.theMaze[MazeWidth + 1][MazeHeight] == 1)
				{
					theTransform->SetScale(ratiox/2, 1, 1, true);
				}
				else if (theMaze.theMaze[MazeWidth - 1][MazeHeight] == 1)
				{
					theTransform->SetScale(ratiox/2, 1, 1, true);
				}
				if (theMaze.theMaze[MazeWidth][MazeHeight + 1])
				{
					theTransform->SetScale(1, 1, ratioy/2, true);
				}
				else if (theMaze.theMaze[MazeWidth][MazeHeight - 1] == 1)
				{
					theTransform->SetScale(1, 1, ratioy/2, true);
				}
				//This is the wall, so draw a cube here.


				std::cout << theRoot->AddChild(theTransform, newModel) << endl;
				

				newModel = new CModel();
				newModel->SetColor(1.0, 0.0, 1.0);
				std::cout << theRoot->GetNode(10 + 1 * counter)->AddChild(new CTransform(0, 2, 0), newModel) << endl;

				newModel = new CModel();
				newModel->SetColor(0.0, 1.0, 1.0);
				ArrayofIDs.push_back(theRoot->GetNode(100 + 1 + 10 * counter)->AddChild(new CTransform(0, 2, 0), newModel));
				counter++;
			}
		}
	}

	//Set up the Player
	thePlayer = new CSceneNode();
	newModel = new CModel();
	thePlayerData.SetPos((theMaze.x - WIDTH / 2) * ratiox, 2, (theMaze.z - HEIGHT / 2)* ratioy);
	CTransform * theTransform = new CTransform(thePlayerData.GetPos(), Vector3D(1, 1, 1));
	thePlayer->SetNode(theTransform, newModel);
	thePlayer->SetColor(1, 0, 1);
	PlayerID = theRoot->AddChild(thePlayer);



	return true;
}

// Update the model
void MVC_Model::Update(void)
{
	m_timer->UpdateTime();
	//thirdpersoncamera->Update();
	
	if (m_timer->TestFramerate())
	{
		m_testX += m_moveX*m_timer->GetDelta();
		m_testY += m_moveY*m_timer->GetDelta();
	}

	if (theRoot)
	{
		for (int i = 0; i < ArrayofIDs.size(); i++)
		{
			theRoot->GetNode(ArrayofIDs[i])->ApplyRotate(100 * m_timer->GetDelta(), 0, 1, 0);
		}
	}
	//theFrustum->Update();
}

//Checking specific to the root.
void MVC_Model::FrustumChecking()
{
	for (int i = 0; i < theRoot->GetNumOfChild(); i++)
	{
		const int ID = theRoot->GetSceneNodeID() * 10 + i + 1;
		FrustumChecking(theRoot->GetNode(ID), theRoot->GetSceneNodeID(), ID);
	}
}

//Not a fully soft-coded and recursive method. Will change if got time.

void MVC_Model::FrustumChecking(CSceneNode * thisNode, const int ParentID, const int thisID)
{
	Vector3D NearTopLeft, NearTopRight, NearBottomLeft, NearBottomRight;
	Vector3D FarTopLeft, FarTopRight, FarBottomLeft, FarBottomRight;

	if (
		(theRoot->GetNode(ParentID)->GetNearTopLeft(thisID, NearTopLeft))
		&& (theRoot->GetNode(ParentID)->GetNearTopRight(thisID, NearTopRight))
		&& (theRoot->GetNode(ParentID)->GetNearBottomLeft(thisID, NearBottomLeft))
		&& (theRoot->GetNode(ParentID)->GetNearBottomRight(thisID, NearBottomRight))

		&& (theRoot->GetNode(ParentID)->GetFarTopLeft(thisID, FarTopLeft))
		&& (theRoot->GetNode(ParentID)->GetFarTopRight(thisID, FarTopRight))
		&& (theRoot->GetNode(ParentID)->GetFarBottomLeft(thisID, FarBottomLeft))
		&& (theRoot->GetNode(ParentID)->GetFarBottomRight(thisID, FarBottomRight))
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


		if (!(m_bCheckNearTopLeft || m_bCheckNearTopRight
			|| m_bCheckNearBottomLeft || m_bCheckNearBottomRight
			|| m_bCheckFarTopLeft || m_bCheckFarTopRight
			|| m_bCheckFarBottomLeft || m_bCheckFarBottomRight))
		{
			//The scene graph is not inside the frustum
			//thisNode->SetColor(0, 0, 0);
			thisNode->Draw();
		}

		else
		{
			if (m_bCheckNearTopLeft && m_bCheckNearTopRight
				&& m_bCheckNearBottomLeft && m_bCheckNearBottomRight
				&& m_bCheckFarTopLeft && m_bCheckFarTopRight
				&& m_bCheckFarBottomLeft && m_bCheckFarBottomRight)
			{
				// The scene graph is inside the frustum!
				//thisNode->SetColor(1.0f, 1.0f, 1.0f);
				//thisNode->Draw();
			}

			else
			{
				//thisNode->Draw();
				//thisNode->SetColor(1, 0, 0);
				//Scene graph halfway in.
			}
			for (int i = 0; i < thisNode->GetNumOfChild(); i++)
			{
				const int ID = thisNode->GetSceneNodeID() * 10 + i + 1;
				FrustumChecking(thisNode->GetNode(ID), thisID, ID);
			}
		}
	}
}
