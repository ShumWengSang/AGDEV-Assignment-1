#ifndef __MVC_VIEW_H
#include "MVC_View.h"
#endif

#ifndef __MVC_MODEL_H__
#include "MVC_Model.h"
#endif

#ifndef __WINDOWS_H__
#include <windows.h> // Header File For Windows
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

GLvoid MVC_View::ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0) // Prevent A Divide By Zero By
	{
		height=1; // Making Height Equal One
	}

	m_iWindows_Width = width; 
	m_iWindows_Height = height;
	//Swidth=Sheight*width/height;
	m_theModel->m_worldSizeX=1024;
	m_theModel->m_worldSizeY=800;
	glViewport(0,0,m_iWindows_Width,m_iWindows_Height); // ReSet The Current Viewport

	glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
	glLoadIdentity(); // ReSet The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(60.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0f);

	//glOrtho(0, m_theModel->m_worldSizeX, m_theModel->m_worldSizeY, 0,-1,1);

	glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
	glLoadIdentity(); // ReSet The Modelview Matrix
	glDisable(GL_DEPTH_TEST);
}

void MVC_View::GetSize(int* x,int* y)
{
	*x=m_iWindows_Width;
	*y=m_iWindows_Height;
}

GLvoid MVC_View::KillGLWindow(GLvoid) // Properly Kill The Window
{
	if (m_bFullScreen) // Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0); // If So Switch Back To The Desktop
		ShowCursor(TRUE); // Show Mouse Pointer
	}

	if (m_hRC) // Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL)) // Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(m_hRC)) // Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		m_hRC=NULL; // Set RC To NULL
	}

	if (m_hDC && !ReleaseDC(m_hWnd,m_hDC)) // Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		m_hDC=NULL; // Set DC To NULL
	}

	if (m_hWnd && !DestroyWindow(m_hWnd)) // Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		m_hWnd=NULL; // Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",m_hInstance)) // Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		m_hInstance=NULL; // Set hInstance To NULL
	}
	KillFont();
}

/* This Code Creates Our OpenGL Window. Parameters Are: *
* title - Title To Appear At The Top Of The Window *
* width - Width Of The GL Window Or Fullscreen Mode *
* height - Height Of The GL Window Or Fullscreen Mode *
* bits - Number Of Bits To Use For Color (8/16/24/32) *
* fullscreenflag - Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE) */

BOOL MVC_View::CreateGLWindow(char* title, int width, int height, int bits)
{
	GLuint PixelFormat; // Holds The Results After Searching For A Match
	WNDCLASS wc; // Windows Class Structure
	DWORD dwExStyle; // Window Extended Style
	DWORD dwStyle; // Window Style
	RECT WindowRect; // Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0; // Set Left Value To 0
	WindowRect.right=(long)width; // Set Right Value To Requested Width
	WindowRect.top=(long)0; // Set Top Value To 0
	WindowRect.bottom=(long)height; // Set Bottom Value To Requested Height

	m_hInstance = GetModuleHandle(NULL); // Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC) WndProc; // WndProc Handles Messages
	wc.cbClsExtra = 0; // No Extra Window Data
	wc.cbWndExtra = 0; // No Extra Window Data
	wc.hInstance = m_hInstance; // Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO); // Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Load The Arrow Pointer
	wc.hbrBackground = NULL; // No Background Required For GL
	wc.lpszMenuName = NULL; // We Don't Want A Menu
	wc.lpszClassName = "OpenGL"; // Set The Class Name

	if (!RegisterClass(&wc)) // Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if (m_bFullScreen) // Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings; // Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings)); // Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings); // Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width; // Selected Screen Width
		dmScreenSettings.dmPelsHeight = height; // Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits; // Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results. NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options. Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				m_bFullScreen=false; // Windowed Mode Selected. Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE; // Return FALSE
			}
		}
	}

	if (m_bFullScreen) // Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW; // Window Extended Style
		dwStyle=WS_POPUP; // Windows Style
		ShowCursor(FALSE); // Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW; // Window Extended Style
		dwStyle = WS_POPUP; // Windows Style
		ShowCursor(TRUE); // Hide Mouse Pointer
		//dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE; // Window Extended Style
		//dwStyle=WS_OVERLAPPEDWINDOW; // Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle); // Adjust Window To True Requested Size

	// Create The Window
	if (!(m_hWnd=CreateWindowEx( dwExStyle, // Extended Style For The Window
		"OpenGL", // Class Name
		title, // Window Title
		dwStyle | // Defined Window Style
		WS_CLIPSIBLINGS | // Required Window Style
		WS_CLIPCHILDREN, // Required Window Style
		0, 0, // Window Position
		WindowRect.right-WindowRect.left, // Calculate Window Width
		WindowRect.bottom-WindowRect.top, // Calculate Window Height
		NULL, // No Parent Window
		NULL, // No Menu
		m_hInstance, // Instance
		NULL))) // Dont Pass Anything To WM_CREATE
	{
		KillGLWindow(); // ReSet The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	static PIXELFORMATDESCRIPTOR pfd= // pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR), // Size Of This Pixel Format Descriptor
		1, // Version Number
		PFD_DRAW_TO_WINDOW | // Format Must Support Window
		PFD_SUPPORT_OPENGL | // Format Must Support OpenGL
		PFD_DOUBLEBUFFER, // Must Support Double Buffering
		PFD_TYPE_RGBA, // Request An RGBA Format
		bits, // Select Our Color Depth
		0, 0, 0, 0, 0, 0, // Color Bits Ignored
		0, // No Alpha Buffer
		0, // Shift Bit Ignored
		0, // No Accumulation Buffer
		0, 0, 0, 0, // Accumulation Bits Ignored
		16, // 16Bit Z-Buffer (Depth Buffer)
		0, // No Stencil Buffer
		0, // No Auxiliary Buffer
		PFD_MAIN_PLANE, // Main Drawing Layer
		0, // Reserved
		0, 0, 0 // Layer Masks Ignored
	};

	if (!(m_hDC=GetDC(m_hWnd))) // Did We Get A Device Context?
	{
		KillGLWindow(); // ReSet The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(m_hDC,&pfd))) // Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow(); // ReSet The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if(!SetPixelFormat(m_hDC,PixelFormat,&pfd)) // Are We Able To Set The Pixel Format?
	{
		KillGLWindow(); // ReSet The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if (!(m_hRC=wglCreateContext(m_hDC))) // Are We Able To Get A Rendering Context?
	{
		KillGLWindow(); // ReSet The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if(!wglMakeCurrent(m_hDC,m_hRC)) // Try To Activate The Rendering Context
	{
		KillGLWindow(); // ReSet The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (long)this);

	ShowWindow(m_hWnd,SW_SHOW); // Show The Window
	UpdateWindow(m_hWnd);
	SetForegroundWindow(m_hWnd); // Slightly Higher Priority
	SetFocus(m_hWnd); // Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height); // Set Up Our Perspective GL Screen

	if (!InitGL()) // Initialize Our Newly Created GL Window
	{
		KillGLWindow(); // ReSet The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	// Store the width and height
	m_iWindows_Width = width; 
	m_iWindows_Height = height;
	//Swidth=Sheight*width/height;
	
	m_theModel->m_worldSizeX=float(width);
	m_theModel->m_worldSizeY=float(height);

	return TRUE; // Success
}

LRESULT CALLBACK MVC_View::MsgProc( HWND hWnd, // Handle For This Window
									  UINT uMsg, // Message For This Window
									  WPARAM wParam, // Additional Message Information
									  LPARAM lParam) // Additional Message Information
{
	switch (uMsg) // Check For Windows Messages
	{
	case WM_ACTIVATE: // Watch For Window Activate Message
		{
			if (!HIWORD(wParam)) // Check Minimization State
			{
				m_bActive=TRUE; // Program Is Active
			}
			else
			{
				m_bActive=FALSE; // Program Is No Longer Active
			}

			return 1; // Return To The Message Loop
		}

	case WM_SYSCOMMAND: // Intercept System Commands
		{
			switch (wParam) // Check System Calls
			{
			case SC_SCREENSAVE: // Screensaver Trying To Start?
			case SC_MONITORPOWER: // Monitor Trying To Enter Powersave?
				return 1; // Prevent From Happening
			}
			break; // Exit
		}

	case WM_CLOSE: // Did We Receive A Close Message?
		{
			PostQuitMessage(0); // Send A Quit Message
			return 1; // Jump Back
		}

	case WM_KEYDOWN: // Is A Key Being Held Down?
		{

			m_keys[wParam] = TRUE; // If So, Mark It As TRUE
			return 1; // Jump Back
		}

	case WM_KEYUP: // Has A Key Been Released?
		{

			m_keys[wParam] = FALSE; // If So, Mark It As FALSE
			return 1; // Jump Back
		}

	case WM_SIZE: // Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam)); // LoWord=Width, HiWord=Height
			return 1; // Jump Back
		}
	case WM_MOUSEMOVE:
		{
			m_MouseInfo.SetMousePos( LOWORD(lParam), HIWORD(lParam) );
			int diffX = m_MouseInfo.GetDiff_X();
			int diffY = m_MouseInfo.GetDiff_Y();

		//	m_MouseInfo.m_last_x = diffX;
			//m_MouseInfo.m_last_y = diffY;
			if (m_theModel->ChooseCamera == 1)
				m_theModel->Camera2.calculations(diffX, diffY);

			//Make sure the mouse doesn't go out of the window.
			RECT WindowRect;
			GetWindowRect(hWnd, &WindowRect);
			ClipCursor(&WindowRect);
			return 1; // Jump Back
		}
	case WM_LBUTTONDOWN:
		{
			m_MouseInfo.m_LButtonDown=true;
			m_MouseInfo.m_LButtonHold=true;
			return 1;
		}
	case WM_LBUTTONUP:
		{
			m_MouseInfo.m_LButtonDown=false;
			m_MouseInfo.m_LButtonHold=false;
			m_MouseInfo.m_LButtonUp=true;
			return 1;
		}
	case WM_RBUTTONDOWN:
		{
			m_MouseInfo.m_RButtonDown=true;
			m_MouseInfo.m_RButtonHold=true;
			return 1;
		}
	case WM_RBUTTONUP:
		{
			m_MouseInfo.m_RButtonDown=false;
			m_MouseInfo.m_RButtonHold=false;
			m_MouseInfo.m_RButtonUp=true;
			return 1;
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}


LRESULT CALLBACK MVC_View::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	// Recover the pointer to our class, don't forGet to type cast it back

	MVC_View* winptr = (MVC_View*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	// Check if the pointer is NULL and call the Default WndProc

	if (winptr == NULL)
	{
		return DefWindowProc(hwnd, message, wParam, lParam);
	} else
	{
		// Call the Message Handler for my class (MsgProc in my case)
		return winptr->MsgProc(hwnd, message, wParam, lParam);
	}
}
// Check if the player wants to quit the game
bool MVC_View::IsQuitGame(void)
{
	if (m_keys[VK_ESCAPE])				// Was ESC Pressed?
		return true;
	else
		return false;
}

// Check if the player wants to play the game in Full Screen
bool MVC_View::RunFullScreen(void)
{
	if (m_keys[VK_F1])
		return true;
	else
		return false;
}

// Toggle the game to be fullscreen or otherwise
bool MVC_View::ToggleFullScreen(void)
{
	m_keys[VK_F1]=FALSE;					// If So Make Key FALSE
	m_bFullScreen=!m_bFullScreen;				// Toggle Fullscreen / Windowed Mode
	int height=0,width=0;
	KillGLWindow();						// Kill Our Current Window
	// Recreate Our OpenGL Window
	if(!m_bFullScreen)
	{
		if (!CreateGLWindow("NeHe's OpenGL Framework",640,480,16))
		{
			return false;						// Quit If Window Was Not Created
		}
	}
	else
	{
		GetDefaultRes(height,width);
		if(!CreateGLWindow("NeHe's OpenGL Framework",width,height,16))
		{
			return false;
		}
	}

	return true;
}

// Set the fullscreen display status
void MVC_View::SetFullScreen(bool bFullScreen)
{
	this->m_bFullScreen = bFullScreen;
}

bool MVC_View::GetkeyState(int key)
{
	return m_keys[key];
}

bool* MVC_View::GetKeyBuffer()
{
	return m_keys;
}

void MVC_View::Printw (float x, float y, const char* format, ...) 
{ 
	glRasterPos2f(x,y);
	//credit to nehe bitmap font tutorial for base char printing code
	char text[256];
	va_list ap;
	if(format==NULL)
		return;
	va_start(ap,format);
		vsprintf_s(text,format,ap);
	va_end(ap);

	glPushAttrib(GL_LIST_BIT);
		glListBase(m_base-32);
		glCallLists(strlen(text),GL_UNSIGNED_BYTE,text);
	glPopAttrib();

} 

void MVC_View::BuildFont(void)
{
	//credit to nehe bitmap font tutorial for base char printing code
	//http://nehe.gamedev.net/tutorial/bitmap_fonts/17002/
	HFONT font;
	HFONT oldfont;
	m_base =glGenLists(96);
	
	font=CreateFont(24
		,0//width
		,0//rotation angle
		,0//orientaion angle
		,FW_DONTCARE//thickness
		,false,false,false//italic,underline,strikeout
		,ANSI_CHARSET//character Set indentifier
		,OUT_TT_PRECIS
		,CLIP_DEFAULT_PRECIS
		,ANTIALIASED_QUALITY
		,FF_DONTCARE|DEFAULT_PITCH
		,"Times New Roman");
	oldfont=(HFONT)SelectObject(m_hDC,font);
	wglUseFontBitmaps(m_hDC,32,96,m_base);
	SelectObject(m_hDC,oldfont);
	DeleteObject(font);

}

void MVC_View::KillFont(void)
{
	//credit to nehe bitmap font tutorial for base char printing code
	glDeleteLists(m_base,96);
}

void MVC_View::GetDefaultRes(int& height, int&width)
{
	//credits to http://stackoverflow.com/questions/8690619/how-to-Get-screen-resolution-in-c
	RECT desktop;
	HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	width  = desktop.right;
	height = desktop.bottom;
}
