#include "SceneGraph\SceneNode.h"

Vector3D CSceneNode::GetNearTopLeft(void)
{
	if (theTransform == NULL)
		return Vector3D(theModel->NearTopLeft);
	else
		return (theModel->NearTopLeft * theTransform->GetTransform());

}
Vector3D CSceneNode::GetNearTopRight(void)
{
	if (theTransform == NULL)
		return Vector3D(theModel->NearTopRight);
	else
		return (theModel->NearTopRight * theTransform->GetTransform());
}
Vector3D CSceneNode::GetNearBottomLeft(void)
{
	if (theTransform == NULL)
		return Vector3D(theModel->NearBottomLeft);
	else
		return (theModel->NearBottomLeft * theTransform->GetTransform());
}
Vector3D CSceneNode::GetNearBottomRight(void)
{
	if (theTransform == NULL)
		return Vector3D(theModel->NearBottomRight);
	else
		return (theModel->NearBottomRight * theTransform->GetTransform());
}

Vector3D CSceneNode::GetFarTopLeft(void)
{
	if (theTransform == NULL)
		return Vector3D(theModel->FarTopLeft);
	else
		return (theModel->FarTopLeft * theTransform->GetTransform());

}
Vector3D CSceneNode::GetFarTopRight(void)
{
	if (theTransform == NULL)
		return Vector3D(theModel->FarTopRight);
	else
		return (theModel->FarTopRight * theTransform->GetTransform());
}
Vector3D CSceneNode::GetFarBottomLeft(void)
{
	if (theTransform == NULL)
		return Vector3D(theModel->FarBottomLeft);
	else
		return (theModel->FarBottomLeft * theTransform->GetTransform());
}
Vector3D CSceneNode::GetFarBottomRight(void)
{
	if (theTransform == NULL)
		return Vector3D(theModel->FarBottomRight);
	else
		return (theModel->FarBottomRight * theTransform->GetTransform());
}

bool CSceneNode::GetNearTopLeft(const int m_iChildIndex, Vector3D& vector3D_NearTopLeft)
{
	vector3D_NearTopLeft = Vector3D(-999, -999, 999);
	CSceneNode* aChild = NULL;
	for (unsigned i = 0; i<theChildren.size(); i++)
	{
		aChild = (CSceneNode*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			vector3D_NearTopLeft = aChild->GetNearTopLeft() * theTransform->GetTransform();
			return true;
		}
	}
	return false;
}

bool CSceneNode::GetNearTopRight(const int m_iChildIndex, Vector3D& vector3D_NearTopRight)
{
	vector3D_NearTopRight = Vector3D(999, -999, 999);
	CSceneNode* aChild = NULL;
	for (unsigned i = 0; i<theChildren.size(); i++)
	{
		aChild = (CSceneNode*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			vector3D_NearTopRight = aChild->GetNearTopRight() * theTransform->GetTransform();
			return true;
		}
	}
	return false;
}

bool CSceneNode::GetNearBottomLeft(const int m_iChildIndex, Vector3D& vector3D_NearBottomLeft)
{
	vector3D_NearBottomLeft = Vector3D(-999, -999, -999);
	CSceneNode* aChild = NULL;
	for (unsigned i = 0; i<theChildren.size(); i++)
	{
		aChild = (CSceneNode*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			vector3D_NearBottomLeft = aChild->GetNearBottomLeft() * theTransform->GetTransform();
			return true;
		}
	}
	return false;
}

bool CSceneNode::GetNearBottomRight(const int m_iChildIndex, Vector3D& vector3D_NearBottomRight)
{
	vector3D_NearBottomRight = Vector3D(-999, -999, -999);
	CSceneNode* aChild = NULL;
	for (unsigned i = 0; i<theChildren.size(); i++)
	{
		aChild = (CSceneNode*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			vector3D_NearBottomRight = aChild->GetNearBottomRight() * theTransform->GetTransform();
			return true;
		}
	}
	return false;
}

bool CSceneNode::GetFarTopLeft(const int m_iChildIndex, Vector3D& vector3D_FarTopLeft)
{
	vector3D_FarTopLeft = Vector3D(-999, -999, -999);
	CSceneNode* aChild = NULL;
	for (unsigned i = 0; i<theChildren.size(); i++)
	{
		aChild = (CSceneNode*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			vector3D_FarTopLeft = aChild->GetFarTopLeft() * theTransform->GetTransform();
			return true;
		}
	}
	return false;
}

bool CSceneNode::GetFarTopRight(const int m_iChildIndex, Vector3D& vector3D_FarTopRight)
{
	vector3D_FarTopRight = Vector3D(-999, -999, -999);
	CSceneNode* aChild = NULL;
	for (unsigned i = 0; i<theChildren.size(); i++)
	{
		aChild = (CSceneNode*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			vector3D_FarTopRight = aChild->GetFarTopRight() * theTransform->GetTransform();
			return true;
		}
	}
	return false;
}

bool CSceneNode::GetFarBottomLeft(const int m_iChildIndex, Vector3D& vector3D_FarBottomLeft)
{
	vector3D_FarBottomLeft = Vector3D(-999, -999, -999);
	CSceneNode* aChild = NULL;
	for (unsigned i = 0; i<theChildren.size(); i++)
	{
		aChild = (CSceneNode*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			vector3D_FarBottomLeft = aChild->GetFarBottomLeft() * theTransform->GetTransform();
			return true;
		}
	}
	return false;
}

bool CSceneNode::GetFarBottomRight(const int m_iChildIndex, Vector3D& vector3D_FarBottomRight)
{
	vector3D_FarBottomRight = Vector3D(-999, -999, -999);
	CSceneNode* aChild = NULL;
	for (unsigned i = 0; i<theChildren.size(); i++)
	{
		aChild = (CSceneNode*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			vector3D_FarBottomRight = aChild->GetFarBottomRight() * theTransform->GetTransform();
			return true;
		}
	}
	return false;
}