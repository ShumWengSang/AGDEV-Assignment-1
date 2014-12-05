#ifndef __TRANSFORM_H__
#include "Transform.h"
#endif


CTransform::CTransform(void)
{
	Mtx.Clear();
	Update_Mtx.Clear();
}

CTransform::CTransform( const float dx, const float dy, const float dz )
{
	Mtx.Translatef( dx, dy, dz );
}

CTransform::CTransform(Vector3D Translate, Vector3D Scale)
{
	Mtx.Translatef(Translate.m_x, Translate.m_y, Translate.m_z);
	Mtx.Scalef(Scale.m_x, Scale.m_y, Scale.m_z);
}


CTransform::~CTransform(void)
{
}

void CTransform::PreRendering()
{
	glPushMatrix();
		glMultMatrixf(Mtx.matrix);
}

void CTransform::Draw(void)
{
}

void CTransform::PostRendering()
{
	glPopMatrix();
}

void CTransform::SetTranslate( const float dx, const float dy, const float dz  )
{
	Matrix4x4 TempMtx;
	TempMtx.Translatef( dx, dy, dz );

	Mtx = Mtx * TempMtx;
}

void CTransform::SetRotate( const float angle, const float rx, const float ry, const float rz  )
{
	Matrix4x4 TempMtx;
	TempMtx.Rotatef( angle, rx, ry, rz );
	
	Matrix4x4 MtxBackToOrigin;

	MtxBackToOrigin.matrix[ MtxBackToOrigin.INDEX4( 0, 3 ) ] = -Mtx.matrix[ Mtx.INDEX4( 0, 3 ) ];
	MtxBackToOrigin.matrix[ MtxBackToOrigin.INDEX4( 1, 3 ) ] = -Mtx.matrix[ Mtx.INDEX4( 1, 3 ) ];
	MtxBackToOrigin.matrix[ MtxBackToOrigin.INDEX4( 2, 3 ) ] = -Mtx.matrix[ Mtx.INDEX4( 2, 3 ) ];

	Matrix4x4 MtxBackToPosition;
	MtxBackToPosition.matrix[ MtxBackToPosition.INDEX4( 0, 3 ) ] = Mtx.matrix[ Mtx.INDEX4( 0, 3 ) ];
	MtxBackToPosition.matrix[ MtxBackToPosition.INDEX4( 1, 3 ) ] = Mtx.matrix[ Mtx.INDEX4( 1, 3 ) ];
	MtxBackToPosition.matrix[ MtxBackToPosition.INDEX4( 2, 3 ) ] = Mtx.matrix[ Mtx.INDEX4( 2, 3 ) ];

	Mtx = Mtx * MtxBackToOrigin;
	Mtx = Mtx * TempMtx;
	Mtx = Mtx * MtxBackToPosition;
}

//void CTransform::SetRotate2( const float angle, const float rx, const float ry, const float rz, 
//							 const float offset_x, const float offset_y, const float offset_z )
//{
//	Matrix4x4 TempMtx;
//	TempMtx.Rotatef( angle, rx, ry, rz );
//	
//	Matrix4x4 MtxBackToOrigin;
//
//	MtxBackToOrigin.matrix[ MtxBackToOrigin.INDEX4( 0, 3 ) ] = -offset_x;
//	MtxBackToOrigin.matrix[ MtxBackToOrigin.INDEX4( 1, 3 ) ] = -offset_y;
//	MtxBackToOrigin.matrix[ MtxBackToOrigin.INDEX4( 2, 3 ) ] = -offset_z;
//
//	Matrix4x4 MtxBackToPosition;
//	MtxBackToPosition.matrix[ MtxBackToPosition.INDEX4( 0, 3 ) ] = offset_x;
//	MtxBackToPosition.matrix[ MtxBackToPosition.INDEX4( 1, 3 ) ] = offset_y;
//	MtxBackToPosition.matrix[ MtxBackToPosition.INDEX4( 2, 3 ) ] = offset_z;
//
//	Mtx = Mtx * MtxBackToOrigin;
//	Mtx = Mtx * TempMtx;
//	Mtx = Mtx * MtxBackToPosition;
//}

void CTransform::SetScale( const float sx, const float sy, const float sz , bool Inherited )
{
	if (Inherited)
		Mtx.InheritedScalef(sx, sy, sz);
	else
		Mtx.Scalef( sx, sy, sz );
}

void CTransform::ApplyTransform( Matrix4x4 newMTX )
{
	Mtx = Mtx * newMTX;
}

void CTransform::GetOffset( float& x, float& y, float& z )
{
	x = Mtx.matrix[ Mtx.INDEX4( 0, 3 ) ];
	y = Mtx.matrix[ Mtx.INDEX4( 1, 3 ) ];
	z = Mtx.matrix[ Mtx.INDEX4( 2, 3 ) ];
}

// Get the transformation matrix
Matrix4x4 CTransform::GetTransform(void)
{
	return Mtx;
}