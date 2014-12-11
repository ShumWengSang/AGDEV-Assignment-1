#ifndef __SCENENODE_H_
#define __SCENENODE_H__


#ifndef __NODE_H__
#include "node.h"
#endif

#ifndef __MODEL_H__
#include "Model.h"
#endif

#ifndef __TRANSFORM_H__
#include "Transform.h"
#endif


#ifndef __MATRIX4X4_H__
#include "Matrix4x4.h"
#endif

#include <cstdlib>
#include <vector>
#include "../Player.h"

using namespace std;

class CSceneNode :
	public CNode
{
private:
	vector<CNode*> theChildren;

	CModel* theModel;
	CTransform* theTransform;
	//Entity* theEntity;

	int sceneNodeID;

public:
	CSceneNode(void);
	CSceneNode(const int sceneNodeID);
	~CSceneNode(void);

	// Draw this Node and its children
	void Draw(void);

	// Set model and other info to this Node
	void SetModel(CModel* theModel);
	int SetNode(CTransform* aNewTransform, CModel* aNewModel);
	void SetSceneNodeID(const int sceneNodeID);

	int AddChild(CTransform* aNewTransform, CModel* aNewModel);
	int AddChild(const int sceneNodeID, CTransform* aNewTransform, CModel* aNewModel);
	int AddChild(CSceneNode*);

	// Get methods
	int GetSceneNodeID(void);
	CSceneNode* GetNode(const int sceneNodeID, const int depth = 1);

	// Apply transformation to this Node and its children
	void ApplyTranslate( const float dx, const float dy, const float dz );
	void ApplyRotate( const float angle, const float rx, const float ry, const float rz );

	// Get top left corner of the group
	Vector3D GetTopLeft(void);
	// Get bottom right corner of the group
	Vector3D GetBottomRight(void);

	Vector3D GetNearTopLeft();
	Vector3D GetNearTopRight();
	Vector3D GetNearBottomLeft();
	Vector3D GetNearBottomRight();

	Vector3D GetFarTopLeft();
	Vector3D GetFarTopRight();
	Vector3D GetFarBottomLeft();
	Vector3D GetFarBottomRight();

	// Set colour of the instance
	void SetColor(const float red, const float green, const float blue);

	// Return the number of children in this group
	int GetNumOfChild(void);
	// Get top left corner of a child
	bool GetTopLeft(const int m_iChildIndex, Vector3D& vector3D_TopLeft);
	// Get bottom right corner of a child
	bool GetBottomRight(const int m_iChildIndex, Vector3D& vector3D_BottomRight);

	bool GetNearTopLeft(const int m_iChildIndex, Vector3D& vector3D_NearTopLeft);
	bool GetNearTopRight(const int m_iChildIndex, Vector3D& vector3D_NearTopRight);
	bool GetNearBottomLeft(const int m_iChildIndex, Vector3D& vector3D_NearBottomLeft);
	bool GetNearBottomRight(const int m_iChildIndex, Vector3D& vector3D_NearBottomRight);

	bool GetFarTopLeft(const int m_iChildIndex, Vector3D& vector3D_FarTopLeft);
	bool GetFarTopRight(const int m_iChildIndex, Vector3D& vector3D_FarTopRight);
	bool GetFarBottomLeft(const int m_iChildIndex, Vector3D& vector3D_FarBottomLeft);
	bool GetFarBottomRight(const int m_iChildIndex, Vector3D& vector3D_FarBottomRight);

	// Set the Colour of a child
	void SetColorForChild(const int m_iChildIndex, const float red, const float green, const float blue);
};

#endif