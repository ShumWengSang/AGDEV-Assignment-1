#ifndef __MVC_VIEW_H__
#define __MVC_VIEW_H__
//#pragma comment(lib, "opengl32.lib")
//#pragma comment(lib, "glu32.lib")

#ifndef __MOUSE_H__
#include "Mouse.h"
#endif __MOUSE_H__

#ifndef __WINDOWS_H__
#include <windows.h> // Header File For Windows
#define __WINDOWS_H__
#endif
#ifndef __GL_H__
#include <gl\gl.h> // Header File For The OpenGL32 Library
#pragma comment(lib, "glu32.lib")
#define __GL_H__
#endif

class MVC_Model;

class MVC_View
{
public:
	MVC_View(MVC_Model* theModel);
	~MVC_View(void);
	// Draw the view
	BOOL Draw(void);

	int InitGL(GLvoid);										// All Setup For OpenGL Goes Here
	BOOL CreateGLWindow(char* title, int width, int height, int bits);
	GLvoid ReSizeGLScene(GLsizei width, GLsizei height);		// Resize And Initialize The GL Window
	GLvoid KillGLWindow(GLvoid);

	bool GetkeyState(int);
	bool* GetKeyBuffer();
	void GetSize(int* x,int* y);

	CMouse m_MouseInfo;
	float m_Swidth,m_Sheight;
private:
	GLuint  m_base;                           // Base Display List For The Font Set
	void Printw (float x, float y,const char* format, ...);

	MVC_Model* m_theModel;

	HDC m_hDC; // Private GDI Device Context
	HGLRC m_hRC; // Permanent Rendering Context
	HWND m_hWnd; // Holds Our Window Handle
	HINSTANCE m_hInstance; // Holds The Instance Of The Application

	bool m_bActive; // Window Active Flag Set To TRUE By Default
	bool m_bFullScreen; // Fullscreen Flag Set To Fullscreen Mode By Default
	bool m_keys[256]; // Array Used For The Keyboard Routine
	int m_iWindows_Width, m_iWindows_Height;

	void BuildFont(void);
	void KillFont(void);

	virtual LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM); // Declaration For WndProc
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // Declaration For WndProc
public:
	void GetDefaultRes(int& height,int& width);
	// Check if the player wants to quit the game
	bool IsQuitGame(void);
	// Check if the player wants to play the game in Full Screen
	bool RunFullScreen(void);
	// Toggle the game to be fullscreen or otherwise
	bool ToggleFullScreen(void);
	// Set the fullscreen display status
	void SetFullScreen(bool m_bFullScreen);
};

#endif