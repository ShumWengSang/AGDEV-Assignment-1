//*************************************************************************************************************************************//
//
//	Original MVC framework made by Mr Toh Da Jun for DM2231 Game Development Techniques
//	Adapted and modified by Kennard Kee Wei Sheng
//	Framework taken with permission by Shum Weng Sang
//************************************************************************************************************************************//
#ifndef __MVC_VIEW_H__
#include "MVC_View.h"
#endif

#ifndef __MVC_MODEL_H__
#include "MVC_Model.h"
#endif

#ifndef __BASIC_H__
#include "basicShape.h"
#endif

#ifndef __MVCTIME_H__
#include "MVCtime.h"
#endif

#ifndef __WINDOWS_H__
#include <windows.h> // Header File For Windows
#define __WINDOWS_H__
#endif
#ifndef __GL_H__
#include <gl\gl.h> // Header File For The OpenGL32 Library
#pragma comment(lib, "glu32.lib")
#define __GL_H__
#endif
#ifndef __GLU_H__
#include <gl\glu.h> // Header File For The GLu32 Library
#pragma comment(lib, "opengl32.lib")
#define __GLU_H__
#endif


MVC_View::MVC_View(MVC_Model* theModel)
{
	m_theModel = theModel;

	m_MouseInfo.init();
	m_iWindows_Width = 1; 
	m_iWindows_Height = 1;
	m_Sheight=100;
	m_Swidth=150;

	m_bActive = true; // Window Active Flag Set To TRUE By Default
	m_bFullScreen = false; // Fullscreen Flag Set To Fullscreen Mode By Default

	m_hDC=NULL;
	m_hRC=NULL;
	m_hWnd=NULL;

	for (int i=0; i<256; i++)
	{
		m_keys[i] = false;
	}
}

MVC_View::~MVC_View(void)
{
	m_theModel = NULL;
}

// Draw the view
BOOL MVC_View::Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
	glLoadIdentity(); // ReSet The Current Modelview Matrix

	glColor3f(1,1,1);
	Printw(5,30,"FPS: %.2f",MVCTime::GetInstance()->GetFPS());



	m_theModel->theCamera.Update(Vector3D(m_theModel->x,m_theModel->y, m_theModel->z));
	//m_theModel->theCamera.Update();
	//m_theModel->theCamera.SetDirection(m_theModel->x, m_theModel->y, m_theModel->z);
	//m_theModel->theCamera.SetPosition(m_theModel->x, m_theModel->y, m_theModel->z);

	glPushMatrix();
	glTranslatef(m_theModel->x,m_theModel->y, m_theModel->z); // Move Left 1.5 Units And Into The Screen 6.0
//	glRotatef(rtri, 0.0f, 1.0f, 0.0f); // Rotate The Triangle On The Y axis ( NEW )
	glBegin(GL_TRIANGLES); // Start Drawing A Triangle
	glColor3f(1.0f, 0.0f, 0.0f); // Set Top Point Of Triangle To Red
	glVertex3f(0.0f, 1.0f, 0.0f); // First Point Of The Triangle
	glColor3f(0.0f, 1.0f, 0.0f); // Set Left Point Of Triangle To Green
	glVertex3f(-1.0f, -1.0f, 0.0f); // Second Point Of The Triangle
	glColor3f(0.0f, 0.0f, 1.0f); // Set Right Point Of Triangle To Blue
	glVertex3f(1.0f, -1.0f, 0.0f); // Third Point Of The Triangle
	glEnd(); // Done Drawing The Triangle
	glPopMatrix();

	m_theModel->theBox.Draw();
//	m_theModel->theFrustum->Draw();
	


	m_theModel->theCamera.SetHUD(true);
	m_theModel->theHUD.Draw();
	m_theModel->theCamera.SetHUD(false);



	glColor3f(1,1,1);
	SwapBuffers(m_hDC); // Swap Buffers (Double Buffering)

	return TRUE; // Keep Going
}

int MVC_View::InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH); // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // Black Background
	glClearDepth(1.0f); // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations

	BuildFont();
	
	return TRUE; // Initialization Went OK
}

