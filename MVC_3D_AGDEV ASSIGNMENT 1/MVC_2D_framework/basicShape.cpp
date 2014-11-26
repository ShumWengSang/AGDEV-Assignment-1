#ifndef __BASIC_H__
#include"basicShape.h"
#endif

#ifndef __WINDOWS_H__
#include <Windows.h>
#define __WINDOWS_H__
#endif
#ifndef __GL_H__
#include <gl\gl.h> // Header File For The OpenGL32 Library
#define __GL_H__
#endif

#ifndef __GLU_H__
#include <gl\glu.h> // Header File For The GLu32 Library
#define __GLU_H__
#endif

#ifndef __MATH_H__
#include <math.h>
#define __MATH_H__
#endif

using namespace basicShape;

float basicShape::GetRad(float degree)
{
	return(degree/180.f*3.142f);
}

void basicShape::drawAxis()
{
	glBegin (GL_LINES);
		glColor3f (1.0, 0.0, 0.0);
		glVertex3f (-100.0, 0.0, 0.0);
		glVertex3f (100.0, 0.0, 0.0);
		/*
		for(int i=-100;i<100;i++)
		{
			glVertex3f(i,-1,0);
			glVertex3f(i,1,0);
		}
		*/
		glColor3f (0.0, 1.0, 0.0);
		glVertex3f (0.0, -100.0, 0.0);
		glVertex3f (0.0, 100.0, 0.0);
		/*for(int i=-100;i<100;i++)
		{
			glVertex3f(-1,i,0);
			glVertex3f(1,i,0);
		}
		*/
		glColor3f (0.0, 0.0, 1.0);
		glVertex3f (0.0, 0.0, -100.0);
		glVertex3f (0.0, 0.0, 100.0);
		/*for(int i=-100;i<100;i++)
		{
			glVertex3f(-1,0,i);
			glVertex3f(1,0,i);
		}
		*/
	glEnd ();
}

void basicShape::drawSquare()
{
	glBegin (GL_TRIANGLE_STRIP);
		glNormal3f(0,0,1);
		glTexCoord2f(0,0);
		glVertex3f(-0.5, 0.5, 0);
		
		glTexCoord2f(0,1.0);
		glVertex3f(-0.5,-0.5,0);

		glTexCoord2f(1.0,0.0);
		glVertex3f(0.5,0.5,0);

		glTexCoord2f(1.0,1.0);
		glVertex3f(0.5,-0.5,0);
	glEnd();
}

void basicShape::drawCube()
{
	glBegin(GL_POLYGON);
	{
		glNormal3f(1,0,0);
		glVertex3f(0.5,0.5,0.5);
		glVertex3f(0.5,-0.5,0.5);
		glVertex3f(0.5,-0.5,-0.5);
		glVertex3f(0.5,0.5,-0.5);
	}
	glEnd();

	glBegin(GL_POLYGON);
	{
		glNormal3f(0,0,1);
		glVertex3f(0.5,0.5,0.5);
		glVertex3f(-0.5,0.5,0.5);
		glVertex3f(-0.5,-0.5,0.5);
		glVertex3f(0.5,-0.5,0.5);
	}
	glEnd();
	glBegin(GL_POLYGON);
	{
		glNormal3f(0,1,0);
		glVertex3f(0.5,0.5,0.5);
		glVertex3f(0.5,0.5,-0.5);
		glVertex3f(-0.5,0.5,-0.5);
		glVertex3f(-0.5,0.5,0.5);
	}
	glEnd();
	glBegin(GL_POLYGON);
	{
		glNormal3f(-1,0,0);
		glVertex3f(-0.5,-0.5,-0.5);
		glVertex3f(-0.5,-0.5,0.5);
		glVertex3f(-0.5,0.5,0.5);
		glVertex3f(-0.5,0.5,-0.5);
	}
	glEnd();
	glBegin(GL_POLYGON);
	{
		glNormal3f(0,0,-1);
		glVertex3f(-0.5,-0.5,-0.5);
		glVertex3f(-0.5,0.5,-0.5);
		glVertex3f(0.5,0.5,-0.5);
		glVertex3f(0.5,-0.5,-0.5);
	}
	glEnd();
	glBegin(GL_POLYGON);
	{
		glNormal3f(0,-1,0);
		glVertex3f(-0.5,-0.5,-0.5);
		glVertex3f(0.5,-0.5,-0.5);
		glVertex3f(0.5,-0.5,0.5);
		glVertex3f(-0.5,-0.5,0.5);
	}
	glEnd();
}


float basicShape::GetX(float phi,float theta,float radius)
{
	return(radius*(cos(GetRad(phi)))*(cos(GetRad(theta))));
}
float basicShape::GetY(float phi,float radius)
{
	return (radius*(sin(GetRad(phi))));
}
float basicShape::GetZ(float phi,float theta,float radius)
{
	return(radius*(cos(GetRad(phi))*sin(GetRad(theta))));
}

void basicShape::drawSphere(float radius)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	for(float phi=-90;phi<90;phi+=15)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for(float theta=0;theta<=360;theta +=15)
		{
			glNormal3f(GetX(phi,theta,radius),GetY(phi,radius),GetZ(phi,theta,radius));
			glVertex3f(GetX(phi,theta,radius),GetY(phi,radius),GetZ(phi,theta,radius));
			glNormal3f(GetX(phi+45,theta,radius),GetY(phi+45,radius),GetZ(phi+45,theta,radius));
			glVertex3f(GetX(phi+45,theta,radius),GetY(phi+45,radius),GetZ(phi+45,theta,radius));
		}
		glEnd();
	}
	
}

void basicShape::drawCylinder(float scale,float scalez)
{
	if(scalez==2)
	{
		scalez=scale;
	}
	float radiusDifz=(1-scalez)/2;
	float Cradiusz=scalez/2;
	float Nradiusz;
	float radiusDif=(1-scale)/2;
	float Cradius=scale/2;
	float Nradius;
	float height =1;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLE_STRIP);
		for(float h=-(height/2);h<(height/2);h+=height)
		{
			Nradius=Cradius+(radiusDif/(1/height));
			Nradiusz=Cradiusz+(radiusDifz/(1/height));
			for(float theta=0;theta<=360;theta+=45)
			{
				glNormal3f(GetCX(theta,Cradius),0,GetCZ(theta,Cradiusz));
				glVertex3f(GetCX(theta,Cradius),h,GetCZ(theta,Cradiusz));
				glNormal3f(GetCX(theta,Nradius),0,GetCZ(theta,Nradiusz));
				glVertex3f(GetCX(theta,Nradius),h+height,GetCZ(theta,Nradiusz));
			}
			Cradius+=radiusDif/(1/height);	
			Cradiusz+=radiusDifz/(1/height);
		}
	glEnd();
		Cradius=scale/2;
		Cradiusz=scalez/2;
	glBegin(GL_TRIANGLE_FAN);
		//for(float h=-(height/2);h<(height/2);h+=height)
		glNormal3f(0,-height/2,0);
		glVertex3f(0,-height/2,0);
		for(float theta=360;theta>=0;theta-=15)
		{
			glVertex3f(GetCX(theta,Cradius),-height/2,GetCZ(theta,Cradiusz));
		}
	glEnd();
			
	glBegin(GL_TRIANGLE_FAN);
		Cradius+=radiusDif/(1/height);	
		Cradiusz+=radiusDifz/(1/height);
		glNormal3f(0,height/2,0);
		glVertex3f(0,height/2,0);
		for(float theta=360;theta>=0;theta-=15)
		{
			glVertex3f(GetCX(theta,Cradius),height/2,GetCZ(theta,Cradiusz));
		}
	glEnd();
}

float basicShape::GetCX(float theta,float radius)
{
	return radius*cos(GetRad(theta));
}

float basicShape::GetCZ(float theta,float radius)
{
	return radius*sin(GetRad(theta));
}

void basicShape::drawQuad(int x, int y, int width, int height)
{
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);  glVertex3f(x, y, 0);
	glTexCoord2f(0, 1); glVertex3f(x, y + height, 0);
	glTexCoord2f(1, 1); glVertex3f(x + width, y + height, 0);
	glTexCoord2f(1, 0); glVertex3f(x + width, y, 0);

	//glTexCoord2f(0, 0); glVertex3f(-10.0f, -10.0f, -10.0f);
	//glTexCoord2f(0, 1); glVertex3f(-10.0f, -10.0f, 10.0f);
	//glTexCoord2f(1, 1); glVertex3f(10.0f, -10.0f, 10.0f);
	//glTexCoord2f(1, 0); glVertex3f(10.0f, -10.0f, -10.0f);

	glEnd();
}