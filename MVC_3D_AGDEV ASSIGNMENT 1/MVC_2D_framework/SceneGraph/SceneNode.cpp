#ifndef __SCENENODE_H_
#include "SceneNode.h"
#endif

CSceneNode::CSceneNode(void)
: theModel( NULL )
, theChildren( NULL )
, theTransform ( NULL )
, sceneNodeID (-1)
{
}

CSceneNode::CSceneNode(const int sceneNodeID)
{
	CSceneNode();
	SetSceneNodeID( sceneNodeID );
	//theChildren = new std::vector<CNode*>();
}


CSceneNode::~CSceneNode(void)
{
	if (theChildren.size() != 0)
	{
		CNode* aChild = NULL;
		for (unsigned i=0; i<theChildren.size(); i++)
		{
			aChild = theChildren[i];
			delete aChild;
			aChild = NULL;
		}
		theChildren.clear();
	}

	if (theModel != NULL)
	{
		delete theModel;
		theModel = NULL;
	}

	if (theTransform != NULL)
	{
		delete theTransform;
		theTransform = NULL;
	}
}

void CSceneNode::Draw(void)
{
	if (theTransform)
	{
		theTransform->PreRendering();
		if (theModel)
			theModel->Draw();

		if (theChildren.size() != 0)
		{
			CNode* aChild = NULL;
			for (unsigned i=0; i<theChildren.size(); i++)
			{
				aChild = theChildren[i];
				aChild->Draw();
			}
		}

		theTransform->PostRendering();
	}
}

void CSceneNode::SetModel(CModel* theModel)
{
	this->theModel = theModel;
}

int CSceneNode::SetNode(CTransform* aNewTransform, CModel* aNewModel)
{
	this->theModel = aNewModel;
	this->theTransform = aNewTransform;

	// Set sceneNodeID to 1 as this is the root node
	sceneNodeID = 1;
	return sceneNodeID;
}

void CSceneNode::SetSceneNodeID(const int sceneNodeID)
{
	this->sceneNodeID = sceneNodeID;
}

int CSceneNode::AddChild(CTransform* aNewTransform, CModel* aNewModel)
{
	CSceneNode* aNewNode = new CSceneNode();
	aNewNode->SetNode( aNewTransform, aNewModel );
	//if ((sceneNodeID * 10 + theChildren.size() + 1) % 10 == 0)
	//{
		//aNewNode->SetSceneNodeID(sceneNodeID * 10 + (theChildren.size() + 2));
	//}
	//else
	//{
		aNewNode->SetSceneNodeID(sceneNodeID * 10 + (theChildren.size() + 1));
	//}
	theChildren.push_back( aNewNode );

	return aNewNode->GetSceneNodeID();
}

int CSceneNode::AddChild(CSceneNode * aNewNode)
{
	aNewNode->SetSceneNodeID(sceneNodeID * 10 + (theChildren.size() + 1));
	theChildren.push_back(aNewNode);

	return aNewNode->GetSceneNodeID();
}

int CSceneNode::AddChild(const int sceneNodeID, CTransform* aNewTransform, CModel* aNewModel)
{
	CSceneNode* aNewNode = new CSceneNode( sceneNodeID );
	aNewNode->SetNode( aNewTransform, aNewModel );
	theChildren.push_back( aNewNode );

	return aNewNode->GetSceneNodeID();
}

int CSceneNode::GetSceneNodeID(void)
{
	return sceneNodeID;
}

CSceneNode* CSceneNode::GetNode(const int sceneNodeID, const int depth)
{

	if (this->sceneNodeID == sceneNodeID)
		return this;

	//int DigitCounter = 1;
	//int ThisID = sceneNodeID;
	//int ID = sceneNodeID;

	//if ((ThisID > 10))
	//{
	//	while (true)
	//	{
	//		
	//		if (ThisID < 10)
	//		{
	//			break;
	//		}
	//		ThisID /= 10;
	//		DigitCounter++;
	//	}
	//}
	//int DepthCounter = DigitCounter - depth;

	//while (DigitCounter > DepthCounter)
	//{
	//	int theInt = 0;
	//	for (int theInte = 0; theInte != DigitCounter; theInte++)
	//	{
	//		if (theInt == 0)
	//		{
	//			theInt = 1;
	//		}
	//		else
	//		{
	//			theInt *= 10;
	//		}
	//	}

	//	ID %= theInt;
	//	DigitCounter--;
	//}
	//while (ID > 10)
	//{
	//	ID /= 10;
	//}



	CSceneNode* theTarget = NULL;



	if (theChildren.size() != 0)
	{
		//ID--;
		CSceneNode* aChild = NULL;
		for (unsigned i = 0; i<theChildren.size(); i++)
		{
			aChild = (CSceneNode*)theChildren[i];

			theTarget = ((CSceneNode*)aChild)->GetNode(sceneNodeID);
			if (theTarget != NULL)
				break;
		}
	}

	return theTarget;
}

void CSceneNode::ApplyTranslate( const float dx, const float dy, const float dz )
{
	if (theTransform)
		theTransform->SetTranslate( dx, dy, dz );
}


void CSceneNode::ApplyRotate( const float angle, const float rx, const float ry, const float rz )
{
	if (theTransform)
	{
		// Then rotate the children
		theTransform->SetRotate( angle, rx, ry, rz );
	}
}


// Get top left corner of the group
Vector3D CSceneNode::GetTopLeft(void)
{
	if (theTransform == NULL)
		return Vector3D( theModel->GetTopLeft().m_x, 
						 theModel->GetTopLeft().m_y, 
						 theModel->GetTopLeft().m_z);
	else
	{
		return (theModel->GetTopLeft() * theTransform->GetTransform());
	}
		//return Vector3D( theModel->GetTopLeft().m_x + theTransform->GetTransform().matrix[theTransform->GetTransform().INDEX4(0,3)], 
		//				 theModel->GetTopLeft().m_y + theTransform->GetTransform().matrix[theTransform->GetTransform().INDEX4(1,3)], 
		//				 theModel->GetTopLeft().m_z + theTransform->GetTransform().matrix[theTransform->GetTransform().INDEX4(2,3)]);
}

// Get bottom right corner of the group
Vector3D CSceneNode::GetBottomRight(void)
{
	if (theTransform == NULL)
		return Vector3D( theModel->GetBottomRight().m_x, 
						 theModel->GetBottomRight().m_y, 
						 theModel->GetBottomRight().m_z);
	else
		return (theModel->GetBottomRight() * theTransform->GetTransform());
	/*
		return Vector3D( theModel->GetBottomRight().m_x + theTransform->GetTransform().matrix[theTransform->GetTransform().INDEX4(0,3)], 
						 theModel->GetBottomRight().m_y + theTransform->GetTransform().matrix[theTransform->GetTransform().INDEX4(1,3)], 
						 theModel->GetBottomRight().m_z + theTransform->GetTransform().matrix[theTransform->GetTransform().INDEX4(2,3)]);
						 */
}

void CSceneNode::SetColor(const float red, const float green, const float blue)
{
	theModel->SetColor(red, green, blue);
}

// Return the number of children in this group
int CSceneNode::GetNumOfChild(void)
{
	return (int)theChildren.size();
}

// Get top left corner of a child
bool CSceneNode::GetTopLeft(const int m_iChildIndex, Vector3D& vector3D_TopLeft)
{
	vector3D_TopLeft = Vector3D( -999, -999, -999 );
	CSceneNode* aChild = NULL;
	for (unsigned i=0; i<theChildren.size(); i++)
	{
		aChild = (CSceneNode*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			vector3D_TopLeft = aChild->GetTopLeft() * theTransform->GetTransform();
			return true;
		}
	}
	return false;
}

// Get bottom right corner of a child
bool CSceneNode::GetBottomRight(const int m_iChildIndex, Vector3D& vector3D_BottomRight)
{
	vector3D_BottomRight = Vector3D( -999, -999, -999 );
	CSceneNode* aChild = NULL;
	for (unsigned i=0; i<theChildren.size(); i++)
	{
		aChild = (CSceneNode*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			vector3D_BottomRight = aChild->GetBottomRight() * theTransform->GetTransform();
			return true;
		}
	}
	return false;
}

void CSceneNode::SetColorForChild(const int m_iChildIndex, const float red, const float green, const float blue)
{
	CSceneNode* aChild = NULL;
	for (unsigned i=0; i<theChildren.size(); i++)
	{
		aChild = (CSceneNode*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			aChild->SetColor(red, green, blue);
		}
	}
}
