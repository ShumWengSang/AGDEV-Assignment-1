#ifndef __BASIC_H__
#define __BASIC_H__

namespace basicShape
{
	void drawAxis();
	float GetRad(float degree);
	void drawCube();
	void drawSquare();//square
	void drawQuad(int x, int y, int width, int height);

	//Sphere
	float GetX(float phi,float theta,float radius);
	float GetY(float phi,float radius);
	float GetZ(float phi,float theta,float radius);
	void drawSphere(float radius);

	//Cylinder
	float GetCX(float theta,float radius);
	float GetCZ(float theta,float radius);
	void drawCylinder(float scale,float scalez=2);
}

#endif
