//Vector3D NearTopLeft, NearTopRight, NearBottomLeft, NearBottomRight;
//Vector3D FarTopLeft, FarTopRight, FarBottomLeft, FarBottomRight;
//const int childID = theRoot->GetSceneNodeID() * 10 + i + 1;
//if (
//	(theRoot->GetNearTopLeft(childID, NearTopLeft))
//	&& (theRoot->GetNearTopRight(childID, NearTopRight))
//	&& (theRoot->GetNearBottomLeft(childID, NearBottomLeft))
//	&& (theRoot->GetNearBottomRight(childID, NearBottomRight))
//
//	&& (theRoot->GetFarTopLeft(childID, FarTopLeft))
//	&& (theRoot->GetFarTopRight(childID, FarTopRight))
//	&& (theRoot->GetFarBottomLeft(childID, FarBottomLeft))
//	&& (theRoot->GetFarBottomRight(childID, FarBottomRight))
//	)
//{
//	bool m_bCheckNearTopLeft = theFrustum->ContainmentCheck(NearTopLeft);
//	bool m_bCheckNearTopRight = theFrustum->ContainmentCheck(NearTopRight);
//	bool m_bCheckNearBottomLeft = theFrustum->ContainmentCheck(NearBottomLeft);
//	bool m_bCheckNearBottomRight = theFrustum->ContainmentCheck(NearBottomRight);
//
//	bool m_bCheckFarTopLeft = theFrustum->ContainmentCheck(FarTopLeft);
//	bool m_bCheckFarTopRight = theFrustum->ContainmentCheck(FarTopRight);
//	bool m_bCheckFarBottomLeft = theFrustum->ContainmentCheck(FarBottomLeft);
//	bool m_bCheckFarBottomRight = theFrustum->ContainmentCheck(FarBottomRight);
//
//	if ((m_bCheckNearTopLeft) &&
//		(m_bCheckNearTopRight) &&
//		(m_bCheckNearBottomLeft) &&
//		(m_bCheckNearBottomRight) &&
//
//		(m_bCheckFarTopLeft) &&
//		(m_bCheckFarTopRight) &&
//		(m_bCheckFarBottomLeft) &&
//		(m_bCheckFarBottomRight)
//		)
//	{
//		// The child is INSIDE THE FRUSTUM
//		theRoot->SetColorForChild(childID, 1, 1.0f, 1);
//	}
//	else if (!
//		((m_bCheckNearTopLeft) ||
//		(m_bCheckNearTopRight) ||
//		(m_bCheckNearBottomLeft) ||
//		(m_bCheckNearBottomRight) ||
//
//		(m_bCheckFarTopLeft) ||
//		(m_bCheckFarTopRight) ||
//		(m_bCheckFarBottomLeft) ||
//		(m_bCheckFarBottomRight)
//		))
//	{
//		// The child is OUTSIDE of the frustum!
//		theRoot->SetColorForChild(childID, 0, 0, 0);
//	}
//	else
//	{
//		theRoot->SetColorForChild(childID, 1, 0, 0.0f);
//	}
//}

//void MVC_Model::FrustumChecking()
//{
//	bool m_bContainmentCheck_NearTopLeft = theFrustum->ContainmentCheck(theRoot->GetNearTopLeft());
//	bool m_bContainmentCheck_NearBottomRight = theFrustum->ContainmentCheck(theRoot->GetNearTopRight());
//	bool m_bContainmentCheck_NearTopRight = theFrustum->ContainmentCheck(theRoot->GetNearBottomLeft());
//	bool m_bContainmentCheck_NearBottomLeft = theFrustum->ContainmentCheck(theRoot->GetNearBottomRight());
//
//	bool m_bContainmentCheck_FarTopLeft = theFrustum->ContainmentCheck(theRoot->GetFarTopLeft());
//	bool m_bContainmentCheck_FarBottomRight = theFrustum->ContainmentCheck(theRoot->GetFarTopRight());
//	bool m_bContainmentCheck_FarTopRight = theFrustum->ContainmentCheck(theRoot->GetFarBottomLeft());
//	bool m_bContainmentCheck_FarBottomLeft = theFrustum->ContainmentCheck(theRoot->GetFarBottomRight());
//
//	if (!(m_bContainmentCheck_NearTopLeft || m_bContainmentCheck_NearTopRight
//		|| m_bContainmentCheck_NearBottomLeft || m_bContainmentCheck_NearBottomRight
//		|| m_bContainmentCheck_FarTopLeft || m_bContainmentCheck_FarTopRight
//		|| m_bContainmentCheck_FarBottomLeft || m_bContainmentCheck_FarBottomRight))
//	{
//		//The scene graph is not inside the frustum
//		theRoot->SetColor(0, 0, 0);
//
//	}
//	else
//	{
//		if (m_bContainmentCheck_NearTopLeft && m_bContainmentCheck_NearTopRight
//			&& m_bContainmentCheck_NearBottomLeft && m_bContainmentCheck_NearBottomRight
//			&& m_bContainmentCheck_FarTopLeft && m_bContainmentCheck_FarTopRight
//			&& m_bContainmentCheck_FarBottomLeft && m_bContainmentCheck_FarBottomRight)
//		{
//			// The scene graph is inside the frustum!
//			theRoot->SetColor(1.0f, 1.0f, 1.0f);
//		}
//		else
//		{
//			theRoot->SetColor(1, 0, 0);
//			//Scene graph halfway in.
//		}
//		for (int i = 0; i < theRoot->GetNumOfChild(); i++)
//		{
//			const int ID = theRoot->GetSceneNodeID() * 10 + i + 1;
//			FrustumChecking(theRoot->GetNode(ID), theRoot->GetSceneNodeID(), ID);
//		}
//	}
//}

//glPushMatrix();
//glColor3f(1, 1, 1);
//glLineWidth(2.5);
//glBegin(GL_LINES);
//glVertex3f(m_theModel->theCamera.GetPosition().m_x, m_theModel->theCamera.GetPosition().m_y, m_theModel->theCamera.GetPosition().m_z);
//glVertex3f(m_theModel->theCamera.GetPosition().m_x + (m_theModel->theCamera.GetDirection().m_x * 10), m_theModel->theCamera.GetPosition().m_y + (m_theModel->theCamera.GetDirection().m_y * 10), m_theModel->theCamera.GetPosition().m_z + (m_theModel->theCamera.GetDirection().m_z * 10));
//glEnd();
//DrawObject();
//glLineWidth(1);
//glPopMatrix();