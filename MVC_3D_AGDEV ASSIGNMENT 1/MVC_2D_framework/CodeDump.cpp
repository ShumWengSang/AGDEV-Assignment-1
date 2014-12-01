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