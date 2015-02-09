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
thirdpersoncamera()
{
	Rotate = 0;
	m_timer=MVCTime::GetInstance();
	x = 0; y = 0; z = 0;
	distance = 10;
	thirdpersoncamera = new ThirdPersonCamera();
	ObjectAngle = 0;
	PlayerID = 0;
	thePlayerData.theFrustum = &theFrustum;
	ChooseCamera = 0;
	theExits = NULL;
}

MVC_Model::~MVC_Model(void)
{
	if (thirdpersoncamera != NULL)
	{
		delete thirdpersoncamera;
		thirdpersoncamera = NULL;
	}
	delete[] theExits;
	theExits = NULL;
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
	

	theExits = new Exit [theMaze.PossibleExits.size()];


	if (!LoadTGA(&SkyBoxTextures[0], "SkyBox/front.tga"))				// Load The Font Texture
		return false;	// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[1], "SkyBox/back.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[2], "SkyBox/left.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[3], "SkyBox/right.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[4], "SkyBox/top.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False
	if (!LoadTGA(&SkyBoxTextures[5], "SkyBox/bottom.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False

	if (!LoadTGA(&ExitTexture[0], "exit.tga"))				// Load The Font Texture
		return false;	// If Loading Failed, Return False

	//////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
					TEXTURE FOR EXIT
	for (int i = 1; i < 6; i++)
	{
		ExitTexture[i] = ExitTexture[0];
	}
	for (int i = 0; i < theMaze.PossibleExits.size(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			theExits[i].textureID[j] = ExitTexture[j].texID;
		}
	}
	///////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	
	if (!LoadTGA(&theImageDebugger, "steel.tga"))				// Load The Font Texture
		return false;										// If Loading Failed, Return False

	glDisable(GL_TEXTURE_2D);								



	for (int i = 0; i < 6; i++)
	{
		theBox.textureID[i] = SkyBoxTextures[i].texID;//Set the TEX ID into the SkyBox itself
	}

	CModel* newModel = new CModel();
	newModel->SetColor(0.0, 0.0, 1.0);
	newModel->states = WhatToDraw::Nothing;
	std::cout << theRoot.SetNode(new CTransform(0, 0, 0), newModel) << endl;


	//Find the ratio between skybox width and height and maze width and height.
	//We need this to fully fill our skybox with the maze.
	float ratiox = theBox.Width / WIDTH;
	float ratioy = theBox.Height / HEIGHT;
	//DEBUG
	int theCounter = 0;
	//DEBUG
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
				newModel->SetColor(1.0, 1.0, 1.0);
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


				std::cout << theRoot.AddChild(theTransform, newModel) << endl;
				
				//if (counter % 10 == 0)
				//{
				//	counter++;
				//}
				newModel = new CModel();
				CSceneNode * temp = theRoot.GetNode(10 + 1 * counter );
				std::cout << temp->AddChild(new CTransform(0, 2, 0), newModel) << endl;

				newModel = new CModel();
				temp = theRoot.GetNode(100 + 1 + 10 * counter);
				//theRoot.GetNode(100 + 1 + 10 * counter)
				ArrayofIDs.push_back(temp->AddChild(new CTransform(Vector3D(0,2,0),Vector3D(1,3,1)), newModel));
				//ArrayofIDs.push_back(temp->AddChild(new CTransform(0, 2, 0), newModel));
				counter++;
				theCounter++;
			}
		}
	}

	//Set up the Player
	thePlayer = new CSceneNode();
	newModel = new CModel();
	thePlayerData.SetPos((theMaze.x - WIDTH / 2) * ratiox, 2, (theMaze.z - HEIGHT / 2)* ratioy);
	CTransform * theTransform = new CTransform(thePlayerData.GetPos(), Vector3D(1, 1, 1));
	thePlayer->SetNode(theTransform, newModel);
	thePlayer->SetColor(1, 1, 1);
	newModel->InitObj();
	LoadTGA(&newModel->theObj->theTexture, "portal.tga");
	PlayerID = theRoot.AddChild(thePlayer);

	//LeftSphere
	newModel = new CModel();
	newModel->InitObj();
	newModel->SetColor(1.0, 0.0, 1.0);
	newModel->states = WhatToDraw::Sphere;
	LoadTGA(&newModel->theObj->theTexture,"wheel.tga");
	PlayerParts[0] = theRoot.GetNode(PlayerID)->AddChild(new CTransform(0, 0, 2), newModel);

	//Right Sphere
	newModel = new CModel();
	newModel->InitObj();
	newModel->SetColor(1.0, 0.0, 1.0);
	newModel->states = WhatToDraw::Sphere;
	LoadTGA(&newModel->theObj->theTexture, "wheel.tga");
	PlayerParts[1] = theRoot.GetNode(PlayerID)->AddChild(new CTransform(0, 0, -2), newModel);

	for (int i = 0; i < theMaze.PossibleExits.size(); i++)
	{
		theExits[i].SetPos((theMaze.PossibleExits[i].x - WIDTH/2) * ratiox, 0 ,(theMaze.PossibleExits[i].y - HEIGHT / 2)* ratioy);
	}
	//delete newModel;
//	delete theTransform;



	return true;
}

// Update the model
void MVC_Model::Update(void)
{
	m_timer->UpdateTime();
	
	if (m_timer->TestFramerate())
	{
		m_testX += m_moveX*m_timer->GetDelta();
		m_testY += m_moveY*m_timer->GetDelta();
	}

	if (m_timer->TestFramerate())
	{
		PlayerAgainstExit(PlayerID, theExits, theMaze.PossibleExits.size());
		CheckCollision();
	}
}

//Checking specific to the root.
void MVC_Model::FrustumChecking()
{
	for (int i = 0; i < theRoot.GetNumOfChild(); i++)
	{
		const int ID = theRoot.GetSceneNodeID() * 10 + i + 1;
		FrustumChecking(theRoot.GetNode(ID), theRoot.GetSceneNodeID(), ID);
	}
}

void MVC_Model::FrustumChecking(CSceneNode * thisNode, const int ParentID, const int thisID)
{
	Vector3D NearTopLeft, NearTopRight, NearBottomLeft, NearBottomRight;
	Vector3D FarTopLeft, FarTopRight, FarBottomLeft, FarBottomRight;

	NearTopLeft = thisNode ->GetNearTopLeft();
	NearTopRight = thisNode->GetNearTopRight();
	NearBottomLeft = thisNode->GetNearBottomLeft();
	NearBottomRight = thisNode->GetNearBottomRight();

	FarTopLeft = thisNode->GetFarTopLeft();
	FarTopRight = thisNode->GetFarTopRight();
	FarBottomLeft = thisNode->GetFarBottomLeft();
	FarBottomRight = thisNode->GetFarBottomRight();
	{

		bool m_bCheckNearTopLeft = theFrustum.ContainmentCheck(NearTopLeft);
		bool m_bCheckNearTopRight = theFrustum.ContainmentCheck(NearTopRight);
		bool m_bCheckNearBottomLeft = theFrustum.ContainmentCheck(NearBottomLeft);
		bool m_bCheckNearBottomRight = theFrustum.ContainmentCheck(NearBottomRight);

		bool m_bCheckFarTopLeft = theFrustum.ContainmentCheck(FarTopLeft);
		bool m_bCheckFarTopRight = theFrustum.ContainmentCheck(FarTopRight);
		bool m_bCheckFarBottomLeft = theFrustum.ContainmentCheck(FarBottomLeft);
		bool m_bCheckFarBottomRight = theFrustum.ContainmentCheck(FarBottomRight);


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


//Check Collision. Since only the player is moving, we only need to check the player
//against the world. All other collision  settings will only add to processing memory.
void MVC_Model::CheckCollision()
{
	for (int i = 0; i < theRoot.GetNumOfChild(); i++)
	{
		const int ID = theRoot.GetSceneNodeID() * 10 + i + 1;
		if (ID != PlayerID)
			CheckCollision(theRoot.GetNode(PlayerID), theRoot.GetNode(ID));
	}
}

void MVC_Model::CheckCollision(CSceneNode * otherNode, CSceneNode * thisNode)
{
	//We only need to check 4 sides, since we don't move along the Y axis.
	//(x,z) to (-x,z)
	//(x,z) to (x,-z)
	//(-x,z) to (-x,-z)
	//(x,-z) to (-x,-z)
	Vector3D NearTopRight;
	Vector3D FarBottomLeft;
	Vector3D FarTopRight;
	Vector3D NearBottomLeft;

	Vector3D OtherVectors[4];

	NearTopRight = thisNode->GetNearTopRight();
	FarBottomLeft = thisNode->GetFarBottomLeft();
	NearBottomLeft = thisNode->GetNearBottomLeft();
	FarTopRight = thisNode->GetFarTopRight();

	//Check Collision with the root.
	OtherVectors[0] = otherNode->GetNearTopRight();
	OtherVectors[1] = otherNode->GetFarBottomLeft();
	OtherVectors[2] = otherNode->GetNearBottomLeft();
	OtherVectors[3] = otherNode->GetFarTopRight();

	for (int i = 0; i < 4; i++)
	{
		if (IsPointInside(OtherVectors[i], FarTopRight, NearBottomLeft)
			|| IsPointInside(OtherVectors[i], NearBottomLeft, FarTopRight))
		{
			cout << "COLLIDED" << i << endl;
		}
	}

	for (int i = 0; i < theRoot.GetNode(PlayerID)->GetNumOfChild(); i++)
	{
		const int childID = PlayerID * 10 + i + 1;
		otherNode->GetNearTopRight(childID,OtherVectors[0]);
		otherNode->GetFarBottomLeft(childID, OtherVectors[1]);
		otherNode->GetNearBottomLeft(childID, OtherVectors[2]);
		otherNode->GetFarTopRight(childID, OtherVectors[3]);

		for (int j = 0; j < 4; j++)
		{
			if (IsPointInside(OtherVectors[j], FarTopRight, NearBottomLeft)
				|| IsPointInside(OtherVectors[j], NearBottomLeft, FarTopRight))
			{
				cout << "COLLIDED " << "Child: "<< childID << " Collide: "<< j << endl;
				theRoot.GetNode(childID)->SetColor(1, 1, 1);
			}
		}
	}

	//TEST
	//OtherVectors[0] = otherNode->GetNearTopRight();
	//OtherVectors[1] = otherNode->GetFarBottomLeft();
	//OtherVectors[2] = otherNode->GetNearBottomLeft();
	//OtherVectors[3] = otherNode->GetFarTopRight();

	//for (int i = 0; i < 4; i++)
	//{
	//	if (IsPointInside(OtherVectors[i], FarTopRight, NearBottomLeft)
	//		|| IsPointInside(OtherVectors[i], NearBottomLeft, FarTopRight))
	//	{
	//		cout << "COLLIDED" << i << endl;
	//	}
	//}

	//OtherVectors[0] = otherNode->GetNearTopLeft();
	//OtherVectors[1] = otherNode->GetNearTopRight();
	//OtherVectors[2] = otherNode->GetNearBottomLeft();
	//OtherVectors[3] = otherNode->GetNearBottomRight();

	//OtherVectors[4] = otherNode->GetFarTopLeft();
	//OtherVectors[5] = otherNode->GetFarTopRight();
	//OtherVectors[6] = otherNode->GetFarBottomLeft();
	//OtherVectors[7] = otherNode->GetFarBottomRight();
	//

	
}

bool MVC_Model::IsPointInside(Vector3D thePoint, Vector3D Min, Vector3D Max)
{
	if (thePoint.m_x > Min.m_x && thePoint.m_x < Max.m_x &&
		thePoint.m_z > Min.m_z && thePoint.m_z < Max.m_z)
	{
		return true;
	}
	return false;
}

void MVC_Model::PlayerAgainstExit(int PlayerID, Entity Exit[], int size)
{
	for (int i = 0; i < size; i++)
	{

		Vector3D NearTopRight (-1,1,-1);
		Vector3D FarBottomLeft(1, -1, 1);
		Vector3D FarTopRight(1, 1, -1);
		Vector3D NearBottomLeft(-1, -1, 1);

		NearTopRight += Exit[i].GetPos();
		FarBottomLeft += Exit[i].GetPos();
		FarTopRight += Exit[i].GetPos();
		NearBottomLeft += Exit[i].GetPos();

		CSceneNode * thePlayer = theRoot.GetNode(PlayerID);

		Vector3D OtherVectors[4];
		//Check Collision with the root.
		OtherVectors[0] = thePlayer->GetNearTopRight();
		OtherVectors[1] = thePlayer->GetFarBottomLeft();
		OtherVectors[2] = thePlayer->GetNearBottomLeft();
		OtherVectors[3] = thePlayer->GetFarTopRight();

		for (int j = 0; j < 4; j++)
		{
			if (IsPointInside(OtherVectors[j], FarTopRight, NearBottomLeft)
				|| IsPointInside(OtherVectors[j], NearBottomLeft, FarTopRight))
			{
				cout << "COLLIDED WITH EXIT" << endl;
			}
		}
	}
}