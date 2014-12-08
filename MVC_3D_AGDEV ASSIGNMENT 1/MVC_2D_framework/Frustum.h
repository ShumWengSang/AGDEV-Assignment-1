#ifndef __CFRUSTUM_H__
#define __CFRUSTUM_H__

#ifndef __WINDOWS_H__
#include <windows.h> // Header File For Windows_
#endif
#ifndef __GL_H__
#include <gl\gl.h> // Header File For The OpenGL32 Library
#pragma comment(lib, "glu32.lib")
#endif
#ifndef __GLU_H__
#include <gl\glu.h> // Header File For The GLu32 Library
#endif
#ifndef __VECTOR_H__
#include "vector3D.h"
#endif

#ifndef __MATH_H__
#include <math.h>
#define __MATH_H__
#endif


#define FOVY 45
#define ASPECT_RATIO 1.33f

class CFrustum
{
private:
	GLfloat angle, farDist, nearDist, heightNear, heightFar, widthNear, widthFar;

	Vector3D farC,nearC;
	Vector3D fPosition, fDirection, fUp;
	Vector3D up, right;

	Vector3D ftl,ftr,fbl,fbr;
	Vector3D ntl,ntr,nbl,nbr;
	Vector3D farV,nearV,leftV,rightV,topV,btmV;

public:
	CFrustum(void);
	~CFrustum(void);
	// Update the frustum
	void Update();
	// Draw the frustum
	void Update(Vector3D newPos, Vector3D  newDir);
	// Draw the frustum
	void Draw(void);
	// Perform containment check for a position with respect to the Frustum
	bool ContainmentCheck(const Vector3D position);
	int ContainmentCheckSpheres(Vector3D position, float radius);
};
#endif;