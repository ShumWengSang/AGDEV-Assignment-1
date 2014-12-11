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

	if (m_theModel->ChooseCamera == 0)
		m_theModel->theCamera.Update(m_theModel->thePlayerData.GetPos(), m_theModel->thePlayerData.GetDir(), m_theModel->ObjectAngle);
	else
		m_theModel->Camera2.Update();

	m_theModel->thePlayerData.DebugDraw();

	DrawScene();

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

void MVC_View::DrawObject()
{
	glPushMatrix();
	glTranslatef(m_theModel->theCamera.GetPosition().m_x, m_theModel->theCamera.GetPosition().m_y, m_theModel->theCamera.GetPosition().m_z);
	glRotatef(Math::VectorToAngle(m_theModel->theCamera.GetDirection()), 0.0f, 1.0f, 0.0f); // Rotate The Triangle On The Y axis ( NEW )
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	// Top face (y = 1.0f)
	// Define vertices in counter-clockwise (CCW) order with normal pointing out
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom face (y = -1.0f)
	glColor3f(1.0f, 0.5f, 0.0f);     // Orange
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front face  (z = 1.0f)
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back face (z = -1.0f)
	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Left face (x = -1.0f)
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right face (x = 1.0f)
	glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();  // End of drawing color-cube
	glPopMatrix();
}

void MVC_View::DrawScene()
{
	glPushMatrix();
	m_theModel->theBox.Draw();

	Draw3DSGrid();

	for (int i = 0; i < m_theModel->theMaze.PossibleExits.size(); i++)
	{
		m_theModel->theExits[i].Draw();
	}

	if (m_theModel->thePlayerData.ToggleFrustum)
	{

		m_theModel->FrustumChecking();
		m_theModel->theFrustum.Draw();
	}
	else
	{
		m_theModel->theRoot.Draw();
	}



	m_theModel->theCamera.SetHUD(true);
	m_theModel->theHUD.Draw();
	Printw(10, 50, "FPS: %.2f", MVCTime::GetInstance()->GetFPS());
	Printw(10, 100, "Camera Pos: %f %f %f", m_theModel->theCamera.GetPosition().m_x, m_theModel->theCamera.GetPosition().m_y, m_theModel->theCamera.GetPosition().m_z);
	Printw(10, 150, "Player Data Pos: %f %f %f", m_theModel->thePlayerData.GetPos().m_x, m_theModel->thePlayerData.GetPos().m_y, m_theModel->thePlayerData.GetPos().m_z);
	Printw(10, 200, "Player Direction %f %f %f , Angle : %f", m_theModel->thePlayerData.GetDir().m_x, m_theModel->thePlayerData.GetDir().m_y, m_theModel->thePlayerData.GetDir().m_z, Math::VectorToAngle(m_theModel->thePlayerData.GetDir()));
	Printw(10, 250, "Camera Direction %f %f %f , Angle : %f", m_theModel->theCamera.GetDirection().m_x, m_theModel->theCamera.GetDirection().m_y, m_theModel->theCamera.GetDirection().m_z, Math::VectorToAngle(m_theModel->theCamera.GetDirection()));
	Printw(10, 300, "Distance with Data: %f", (m_theModel->thePlayerData.GetPos() - m_theModel->theCamera.GetPosition()).GetMagnitude());
	m_theModel->theCamera.SetHUD(false);
	glPopMatrix();

}

void MVC_View::Draw3DSGrid()
{
	// This function was added to give a better feeling of moving around.
	// A black background just doesn't give it to ya :)  We just draw 100
	// green lines vertical and horizontal along the X and Z axis.

	// Turn the lines GREEN
	glColor3ub(0, 255, 0);
	glLineWidth(5);
	// Draw a 1x1 grid along the X and Z axis'
	for (float i = -m_theModel->theBox.Width; i <= m_theModel->theBox.Width; i += 1)
	{
		// Start drawing some lines
		glBegin(GL_LINES);

		// Do the horizontal lines (along the X)
		glVertex3f(-100, 0, i);
		glVertex3f(100, 0, i);

		// Do the vertical lines (along the Z)
		glVertex3f(i, 0, -100);
		glVertex3f(i, 0, 100);

		// Stop drawing lines
		glEnd();
	}
	glLineWidth(1);
}