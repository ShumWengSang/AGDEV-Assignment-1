#pragma once
#include <cmath>
class Quarternion
{
public:
	Quarternion();
	~Quarternion();

	//float x, y, z, w;
	//float angle, distance;

	///*Find magnitude of quaternion*/
	//double Length(Quarternion quat)
	//{
	//	return sqrt(quat.x * quat.x + quat.y * quat.y +
	//		quat.z * quat.z + quat.w * quat.w);
	//}

	///*Quaternion with a length of 1*/
	//Quarternion Normalize(Quarternion quat)
	//{
	//	double L = Length(quat);

	//	quat.x /= L;
	//	quat.y /= L;
	//	quat.z /= L;
	//	quat.w /= L;

	//	return quat;
	//}

	//Quarternion Inverse(Quarternion quat)
	//{
	//	quat.x = -quat.x;
	//	quat.y = -quat.y;
	//	quat.z = -quat.z;
	//	return quat;
	//}

	//Quarternion Multiply(Quarternion A, Quarternion B)
	//{
	//	Quarternion C;

	//	C.x = A.w*B.x + A.x*B.w + A.y*B.z - A.z*B.y;
	//	C.y = A.w*B.y - A.x*B.z + A.y*B.w + A.z*B.x;
	//	C.z = A.w*B.z + A.x*B.y - A.y*B.x + A.z*B.w;
	//	C.w = A.w*B.w - A.x*B.x - A.y*B.y - A.z*B.z;
	//	return C;
	//}

	//Vector3D ToEuler(Quarternion theQuat)
	//{
	//	Vector3D theVector;
	//	theVector.m_x = theQuat.distance * cos(theQuat.angle);
	//	theVector.m_z = theQuat.distance * sin(theQuat.angle);

	//	theVector.m_y = theQuat.y;
	//	return theVector;
	//}
};

