#include "Frustum.h"

CFrustum::CFrustum(void)
{
	up.m_x = 0.0f;
	up.m_y = 1.0f;
	up.m_z = 0.0f;
	angle = 0;

	farDist = 15;
	nearDist = 0.1f;

	fPosition = Vector3D(0,0,-5);
	fDirection = Vector3D(0,0,3.14159f);
	fUp = Vector3D(0,1,0);
}

CFrustum::~CFrustum(void)
{
}

// Update the frustum
void CFrustum::Update(void)
{
	heightNear = 2 * tan(FOVY*0.5f) * nearDist;
	heightFar  = 2 * tan(FOVY*0.5f) * farDist;

	widthNear = heightNear* ASPECT_RATIO;
	widthFar  = heightFar * ASPECT_RATIO;

	farC = fPosition + (fDirection.NormalizedVector3D() * farDist);
	nearC = fPosition + (fDirection.NormalizedVector3D() * nearDist);

	right = (fDirection.NormalizedVector3D()).CrossVector3D( up );

	ftl = farC + up * (heightFar*0.5f) - right * (widthFar * 0.5f);
	ftr = farC + up * (heightFar*0.5f) + right * (widthFar * 0.5f);
	fbl = farC - up * (heightFar*0.5f) - right * (widthFar * 0.5f);
	fbr = farC - up * (heightFar*0.5f) + right * (widthFar * 0.5f);

	ntl = nearC + up * (heightNear*0.5f) - right * (widthNear * 0.5f);
	ntr = nearC + up * (heightNear*0.5f) + right * (widthNear * 0.5f);
	nbl = nearC - up * (heightNear*0.5f) - right * (widthNear * 0.5f);
	nbr = nearC - up * (heightNear*0.5f) + right * (widthNear * 0.5f);

	Vector3D vector1,vector2;

	//updating farplane Vector
	vector1 = fbl - ftl;
	vector2 = ftr - ftl;
	farV = vector1.CrossVector3D( vector2 );
	farV.NormalizeVector3D();
	

	//updating nearplane Vector
	vector1 = nbl - ntl;
	vector2 = ntr - ntl;
	nearV = vector1.CrossVector3D( vector2 );
	nearV.NormalizeVector3D();

	//updating btmplane Vector
	vector1 = nbl - fbl;
	vector2 = fbr - fbl;
	btmV = vector1.CrossVector3D( vector2 );
	btmV.NormalizeVector3D();

	//updating topplane Vector
	vector1 = ntl - ftl;
	vector2 = ftr - ftl;
	topV = vector1.CrossVector3D( vector2 );
	topV.NormalizeVector3D();

	//updating leftPlane Vector
	vector1 = nbl - ntl;
	vector2 = ftl - ntl;
	leftV = vector1.CrossVector3D( vector2 );
	leftV.NormalizeVector3D();

	//updating rightPlaneVector
	vector1 = ftr - ntr;
	vector2 = nbr - ntr;
	rightV = vector1.CrossVector3D( vector2 );
	rightV.NormalizeVector3D();
}

// Draw the frustum
void CFrustum::Draw(void)
{
//	glPushMatrix();
	glPushAttrib(GL_ENABLE_BIT);
		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
		glColor4f( 0.0f, 0.0f, 1.0f, 0.6f);
		glBegin( GL_QUADS );
			glVertex3f(nbl.m_x, nbl.m_y, nbl.m_z);
			glVertex3f(ntl.m_x, ntl.m_y, ntl.m_z);

			glVertex3f(ntl.m_x, ntl.m_y, ntl.m_z);
			glVertex3f(ftl.m_x, ftl.m_y, ftl.m_z);
			
			glVertex3f(ftl.m_x, ftl.m_y, ftl.m_z);
			glVertex3f(fbl.m_x, fbl.m_y, fbl.m_z);
			
			glVertex3f(fbl.m_x, fbl.m_y, fbl.m_z);
			glVertex3f(nbl.m_x, nbl.m_y, nbl.m_z);

			
			glVertex3f(nbr.m_x, nbr.m_y, nbr.m_z);
			glVertex3f(ntr.m_x, ntr.m_y, ntr.m_z);

			glVertex3f(ntr.m_x, ntr.m_y, ntr.m_z);
			glVertex3f(ftr.m_x, ftr.m_y, ftr.m_z);
			
			glVertex3f(ftr.m_x, ftr.m_y, ftr.m_z);
			glVertex3f(fbr.m_x, fbr.m_y, fbr.m_z);
			
			glVertex3f(fbr.m_x, fbr.m_y, fbr.m_z);
			glVertex3f(nbr.m_x, nbr.m_y, nbr.m_z);


			glVertex3f(ftl.m_x, ftl.m_y, ftl.m_z);
			glVertex3f(ftr.m_x, ftr.m_y, ftr.m_z);

			glVertex3f(ftr.m_x, ftr.m_y, ftr.m_z);
			glVertex3f(fbr.m_x, fbr.m_y, fbr.m_z);

			glVertex3f(fbr.m_x, fbr.m_y, fbr.m_z);
			glVertex3f(fbl.m_x, fbl.m_y, fbl.m_z);

			glVertex3f(fbl.m_x, fbl.m_y, fbl.m_z);
			glVertex3f(ftl.m_x, ftl.m_y, ftl.m_z);

			
			glVertex3f(ntl.m_x, ntl.m_y, ntl.m_z);
			glVertex3f(ntr.m_x, ntr.m_y, ntr.m_z);
			
			glVertex3f(ntr.m_x, ntr.m_y, ntr.m_z);
			glVertex3f(ftr.m_x, ftr.m_y, ftr.m_z);
			
			glVertex3f(ftr.m_x, ftr.m_y, ftr.m_z);
			glVertex3f(ftl.m_x, ftl.m_y, ftl.m_z);
			
			glVertex3f(ftl.m_x, ftl.m_y, ftl.m_z);
			glVertex3f(ntl.m_x, ntl.m_y, ntl.m_z);

			
			glVertex3f(nbl.m_x, nbl.m_y, nbl.m_z);
			glVertex3f(nbr.m_x, nbr.m_y, nbr.m_z);
			
			glVertex3f(nbr.m_x, nbr.m_y, nbr.m_z);
			glVertex3f(fbr.m_x, fbr.m_y, fbr.m_z);
			
			glVertex3f(fbr.m_x, fbr.m_y, fbr.m_z);
			glVertex3f(fbl.m_x, fbl.m_y, fbl.m_z);
			
			glVertex3f(fbl.m_x, fbl.m_y, fbl.m_z);
			glVertex3f(nbl.m_x, nbl.m_y, nbl.m_z);
			
		glEnd();
		glDisable( GL_BLEND );
	glPopAttrib();

		// Draw the lines of the Frustum
		glColor3f(1.0f, 1.0f, 1.0f);
		glLineWidth(10);
		glBegin( GL_LINES );
			glVertex3f(ntl.m_x, ntl.m_y, ntl.m_z);
			glVertex3f(ntr.m_x, ntr.m_y, ntr.m_z);

			glVertex3f(ntr.m_x, ntr.m_y, ntr.m_z);
			glVertex3f(nbr.m_x, nbr.m_y, nbr.m_z);

			glVertex3f(nbr.m_x, nbr.m_y, nbr.m_z);
			glVertex3f(nbl.m_x, nbl.m_y, nbl.m_z);

			glVertex3f(nbl.m_x, nbl.m_y, nbl.m_z);
			glVertex3f(ntl.m_x, ntl.m_y, ntl.m_z);

			
			glVertex3f(ftl.m_x, ftl.m_y, ftl.m_z);
			glVertex3f(ftr.m_x, ftr.m_y, ftr.m_z);

			glVertex3f(ftr.m_x, ftr.m_y, ftr.m_z);
			glVertex3f(fbr.m_x, fbr.m_y, fbr.m_z);

			glVertex3f(fbr.m_x, fbr.m_y, fbr.m_z);
			glVertex3f(fbl.m_x, fbl.m_y, fbl.m_z);

			glVertex3f(fbl.m_x, fbl.m_y, fbl.m_z);
			glVertex3f(ftl.m_x, ftl.m_y, ftl.m_z);


			glVertex3f(ntl.m_x, ntl.m_y, ntl.m_z);
			glVertex3f(ftl.m_x, ftl.m_y, ftl.m_z);
			
			glVertex3f(ntr.m_x, ntr.m_y, ntr.m_z);
			glVertex3f(ftr.m_x, ftr.m_y, ftr.m_z);

			glVertex3f(nbl.m_x, nbl.m_y, nbl.m_z);
			glVertex3f(fbl.m_x, fbl.m_y, fbl.m_z);

			glVertex3f(nbr.m_x, nbr.m_y, nbr.m_z);
			glVertex3f(fbr.m_x, fbr.m_y, fbr.m_z);
		glEnd();
		glLineWidth(1);
//	glPopMatrix();
}

// Perform containment check for a position with respect to the Frustum
bool CFrustum::ContainmentCheck(const Vector3D position)
{
	Vector3D pointToPos;
	float angle;

	//checking against far plane
	pointToPos = position - ftl;
	angle = (pointToPos.NormalizedVector3D()).DotVector3D( farV );
	
	if (angle < 0)
	{
		return false;
	}

	//checking against near plane
	pointToPos = position - ntl;
	angle = (pointToPos.NormalizedVector3D()).DotVector3D( nearV );

	if (angle > 0)
	{
		return false;
	}

	//checking against btm plane
	pointToPos = position - fbl;
	angle = (pointToPos.NormalizedVector3D()).DotVector3D( btmV );

	if (angle < 0)
	{
		return false;
	}

	//checking against top plane
	pointToPos = position - ftl;
	angle = (pointToPos.NormalizedVector3D()).DotVector3D( topV );

	if (angle > 0)
	{
		return false;
	}

	//checking against left plane
	pointToPos = position - ntl;
	angle = (pointToPos.NormalizedVector3D()).DotVector3D( leftV );

	if (angle < 0)
	{
		return false;
	}
	
	//checking against right plane
	pointToPos = position - ntr;
	angle = (pointToPos.NormalizedVector3D()).DotVector3D( rightV );

	if (angle < 0)
	{
		return false;
	}
	return true;
}
