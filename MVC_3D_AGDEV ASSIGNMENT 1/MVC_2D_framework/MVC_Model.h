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

#ifndef __THIRDPERSONCAMERA_H__
#include "ThirdPersonCamera.h"
#endif

#include "MazeGenerator.h"

#include "SceneGraph\\SceneNode.h"

#include "Math.h"

#include "Exit.h"

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
	float Rotate;
	
	float m_worldSizeX;
	float m_worldSizeY;

	float m_testX;
	float m_testY;
	float m_moveX,m_moveY;

	Vector3D FrustumPosition;
	Vector3D FrustumDirection;

	TextureImage SkyBoxTextures[6];
	TextureImage ExitTexture[6];

	Exit * theExits;

	MVCTime* m_timer;
	CFrustum theFrustum;
	ThirdPersonCamera* thirdpersoncamera;
	CSceneNode theRoot;

	CSceneNode * thePlayer;
	int PlayerID;

	Player thePlayerData;

	Camera theCamera;
	Camera Camera2;

	HUD theHUD;
	SkyBox theBox;

	void FrustumChecking();
	void FrustumChecking(CSceneNode* thisNode, const int ParentID, const int thisID);

	void CheckCollision();
	void CheckCollision(CSceneNode * otherNode, CSceneNode * thisNode);
	bool IsPointInside(Vector3D, Vector3D, Vector3D);

	//A function just for checking the exits against the player in the scene graph
	void PlayerAgainstExit(int PlayerID, Entity Exit[], int size);

	//A vector to hold the IDs of the parts to rotate.
	std::vector<int> ArrayofIDs;

	//DISTANCE FROM OBJECT TO CAMERA
	int distance;

	//TESTING CODES
	float x, y, z;

	//MAZE
	MazeGenerator theMaze;
	TextureImage theImageDebugger;

	//Rotate the object
	float ObjectAngle;

	//Choose camera debug purposes
	int ChooseCamera;

	int PlayerParts[4];
private: 
};

#endif