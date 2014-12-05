#include "ThirdPersonCamera.h"


ThirdPersonCamera::ThirdPersonCamera()
{
	m_vPosition.Set(0,1.5,6);					// Init the position to zero
	m_vView.Set(0,1.5,0);					// Init the view to a std starting view
	m_vUpVector.Set(0,1,0);						// Init the UpVector
}


ThirdPersonCamera::~ThirdPersonCamera()
{
}


///////////////////////////////// POSITION CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function sets the camera's position and view and up vVector.
/////
///////////////////////////////// POSITION CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ThirdPersonCamera::PositionCamera(float positionX, float positionY, float positionZ,
	float viewX, float viewY, float viewZ,
	float upVectorX, float upVectorY, float upVectorZ)
{
	Vector3D vPosition = Vector3D(positionX, positionY, positionZ);
	Vector3D vView = Vector3D(viewX, viewY, viewZ);
	Vector3D vUpVector = Vector3D(upVectorX, upVectorY, upVectorZ);

	// The code above just makes it cleaner to set the variables.
	// Otherwise we would have to set each variable x y and z.

	m_vPosition = vPosition;					// Assign the position
	m_vView = vView;						// Assign the view
	m_vUpVector = vUpVector;					// Assign the up vector
}


///////////////////////////////// ROTATE VIEW \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This rotates the view around the position using an axis-angle rotation
/////
///////////////////////////////// ROTATE VIEW \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ThirdPersonCamera::RotateView(float angle, float x, float y, float z)
{
	Vector3D vNewView;

	// Get the view vector (The direction we are facing)
	Vector3D vView = m_vView - m_vPosition;

	// Calculate the sine and cosine of the angle once
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	// Find the new x position for the new rotated point
	vNewView.m_x = (cosTheta + (1 - cosTheta) * x * x)		* vView.m_x;
	vNewView.m_x += ((1 - cosTheta) * x * y - z * sinTheta)	* vView.m_y;
	vNewView.m_x += ((1 - cosTheta) * x * z + y * sinTheta)	* vView.m_z;

	// Find the new y position for the new rotated point
	vNewView.m_y = ((1 - cosTheta) * x * y + z * sinTheta)	* vView.m_x;
	vNewView.m_y += (cosTheta + (1 - cosTheta) * y * y)		* vView.m_y;
	vNewView.m_y += ((1 - cosTheta) * y * z - x * sinTheta)	* vView.m_z;

	// Find the new z position for the new rotated point
	vNewView.m_z = ((1 - cosTheta) * x * z - y * sinTheta)	* vView.m_x;
	vNewView.m_z += ((1 - cosTheta) * y * z + x * sinTheta)	* vView.m_y;
	vNewView.m_z += (cosTheta + (1 - cosTheta) * z * z)		* vView.m_z;

	// Now we just add the newly rotated vector to our position to set
	// our new rotated view of our camera.
	m_vView = m_vPosition + vNewView;
}

///////////////////////////////// ROTATE AROUND POINT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This rotates the position around a given point
/////
///////////////////////////////// ROTATE AROUND POINT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ThirdPersonCamera::RotateAroundPoint(Vector3D vCenter, float angle, float x, float y, float z)
{
	Vector3D vNewPosition;

	// To rotate our position around a point, what we need to do is find
	// a vector from our position to the center point we will be rotating around.
	// Once we get this vector, then we rotate it along the specified axis with
	// the specified degree.  Finally the new vector is added center point that we
	// rotated around (vCenter) to become our new position. Why so much math?

	// Get the vVector from our position to the center we are rotating around
	Vector3D vPos = m_vPosition - vCenter;

	// Calculate the sine and cosine of the angle once
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	// Find the new x position for the new rotated point
	vNewPosition.m_x = (cosTheta + (1 - cosTheta) * x * x)		* vPos.m_x;
	vNewPosition.m_x += ((1 - cosTheta) * x * y - z * sinTheta)	* vPos.m_y;
	vNewPosition.m_x += ((1 - cosTheta) * x * z + y * sinTheta)	* vPos.m_z;

	// Find the new y position for the new rotated point
	vNewPosition.m_y = ((1 - cosTheta) * x * y + z * sinTheta)	* vPos.m_x;
	vNewPosition.m_y += (cosTheta + (1 - cosTheta) * y * y)		* vPos.m_y;
	vNewPosition.m_y += ((1 - cosTheta) * y * z - x * sinTheta)	* vPos.m_z;

	// Find the new z position for the new rotated point
	vNewPosition.m_z = ((1 - cosTheta) * x * z - y * sinTheta)	* vPos.m_x;
	vNewPosition.m_z += ((1 - cosTheta) * y * z + x * sinTheta)	* vPos.m_y;
	vNewPosition.m_z += (cosTheta + (1 - cosTheta) * z * z)		* vPos.m_z;

	// Now we just add the newly rotated vector to our position to set
	// our new rotated position of our camera.
	m_vPosition = vCenter + vNewPosition;
}

///////////////////////////////// MOVE CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This will move the camera forward or backward depending on the speed
/////
///////////////////////////////// MOVE CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ThirdPersonCamera::MoveCamera(float speed)
{
	// Get our view vector (The direciton we are facing)
	Vector3D vVector = m_vView - m_vPosition;

	vVector.NormalizeVector3D();			//Normalize the vector so you don't move too fast

	m_vPosition.m_x += vVector.m_x * speed;		// Add our acceleration to our position's X
	m_vPosition.m_z += vVector.m_z * speed;		// Add our acceleration to our position's Z
	m_vView.m_x += vVector.m_x * speed;			// Add our acceleration to our view's X
	m_vView.m_z += vVector.m_z * speed;			// Add our acceleration to our view's Z
}

///////////////////////////////// MOVE CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This will move the camera upward or downward depending on the speed
/////
///////////////////////////////// MOVE CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ThirdPersonCamera::MoveUpCamera(float speed)
{
	Vector3D vVector = m_vView - m_vPosition;
}

///////////////////////////////// LOOK AT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This updates the lookat when you call on it every frame.
/////
///////////////////////////////// LOOK AT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ThirdPersonCamera::UpdateLookAt()
{
	gluLookAt(m_vPosition.m_x , m_vPosition.m_y, m_vPosition.m_z,
		m_vView.m_x , m_vView.m_y, m_vView.m_z,
		m_vUpVector.m_x, m_vUpVector.m_y, m_vUpVector.m_z);
}

///////////////////////////////// STRAFE CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This strafes the camera left and right depending on the speed (-/+)
/////
///////////////////////////////// STRAFE CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ThirdPersonCamera::StrafeCamera(float speed)
{
	// Add the strafe vector to our position
	m_vPosition.m_x += m_vStrafe.m_x * speed;
	m_vPosition.m_z += m_vStrafe.m_z * speed;

	// Add the strafe vector to our view
	m_vView.m_x += m_vStrafe.m_x * speed;
	m_vView.m_z += m_vStrafe.m_z * speed;
}

///////////////////////////////// UPDATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This updates the camera's view and strafe vector
/////
///////////////////////////////// UPDATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void ThirdPersonCamera::Update()
{
	// Below we calculate the strafe vector every time we update
	// the camera.  This is because many functions use it so we might
	// as well calculate it only once.  

	// Initialize a variable for the cross product result
	Vector3D vCross = (m_vView - m_vPosition).CrossVector3D( m_vUpVector);

	// Normalize the strafe vector
	m_vStrafe = vCross.NormalizedVector3D();

}

