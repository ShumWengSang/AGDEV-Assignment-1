//*************************************************************************************************************************************//
//
//	Original MVC framework made by Mr Toh Da Jun for DM2231 Game Development Techniques
//	Adapted and modified by Kennard Kee Wei Sheng
//	Framework taken with permission by Shum Weng Sang
//************************************************************************************************************************************//

#ifndef __MVC_CONTROLLER_H__
#include "MVC_Controller.h"
#endif

#ifndef __MVC_MODEL_H__
#include "MVC_Model.h"
#endif

#ifndef __MVC_VIEW_H__
#include "MVC_View.h"
#endif


HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

MVC_Controller::MVC_Controller(MVC_Model* theModel, MVC_View* theView)
: m_theModel(NULL)
, m_theView(NULL)
, m_bContinueLoop(false)
{
	m_theModel = theModel;
	m_theView = theView;
	theTimer = MVCTime::GetInstance();
}

MVC_Controller::~MVC_Controller(void)
{
	m_theView = NULL;
	m_theModel = NULL;
}

bool MVC_Controller::Init(void)
{


	if(!m_theModel->Init(60))
		return false;

	return true;
}


// Get the status of the stop game boolean flag
BOOL MVC_Controller::RunMainLoop(void)
{

	MSG msg; // Windows Message Structure
	BOOL done=FALSE; // Bool Variable To Exit Loop
		// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		m_theView->SetFullScreen( false );
		int height, width;
		m_theView->GetDefaultRes(height, width);
		// Create Our OpenGL Window
		if (!m_theView->CreateGLWindow("NeHe's OpenGL Framework",height,width/2,16))
		{
			return false;									// Quit If Window Was Not Created
		}
	}
	else
	{
		m_theView->SetFullScreen( true );
		int height,width;
		m_theView->GetDefaultRes(height,width);
		// Create Our OpenGL Window
		if (!m_theView->CreateGLWindow("NeHe's OpenGL Framework",width,height,16))
		{
			return false;									// Quit If Window Was Not Created
		}
	}
	
	m_theModel->InitPhase2();

	while(!done) // Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) // Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT) // Have We Received A Quit Message?
			{
				done=TRUE; // If So done=TRUE
			}
			else // If Not, Deal With Window Messages
			{
				TranslateMessage(&msg); // Translate The Message
				DispatchMessage(&msg); // Dispatch The Message
			}
		}
		else // If There Are No Messages
		{
			theTimer->UpdateTime();
			if (ProcessInput())
			{
				m_theModel->Update();
				m_theView->Draw();
			}
			else
			{
				done=TRUE; // ESC or DrawGLScene Signalled A Quit
			}
		}
	}

	// Shutdown
	m_theView->KillGLWindow(); // Kill The Window
	return (msg.wParam); // Exit The Program
}

// Process input from I/O devices
bool MVC_Controller::ProcessInput(void)
{
	// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
	if (m_theView->IsQuitGame())				// Was ESC Pressed?
	{
		m_bContinueLoop=false;						// ESC Signalled A Quit
		return false;
	}

	if (m_theView->RunFullScreen())						// Is F1 Being Pressed?
	{
		if (m_theView->ToggleFullScreen() == false)
		{
			m_bContinueLoop=false;						// ESC Signalled A Quit
			return false;
		}
	}
	
	ProcKeyboard();
	
	ProcMouse();
	
	return true;
}

void MVC_Controller::ProcMouse()
{
	//m_theModel->theCamera.calculations(m_theView->m_MouseInfo.m_last_x, m_theView->m_MouseInfo.m_last_y);

	int w;
	int h;
	m_theView->GetSize(&w,&h);
	if(m_theView->m_MouseInfo.m_LButtonDown)
	{
		if (m_theView->m_MouseInfo.Record)
		{
			m_theView->m_MouseInfo.m_Tempx = m_theView->m_MouseInfo.GetDiff_X();
			m_theView->m_MouseInfo.Record = false;
		}

		m_theView->m_MouseInfo.m_Tempx2 = m_theView->m_MouseInfo.GetDiff_X();
		float Diff = m_theView->m_MouseInfo.m_Tempx - m_theView->m_MouseInfo.m_Tempx2;
		cout << "Diff : " << Diff << endl;
		Diff *= theTimer->GetDelta();

		//Adjusting the value so it won't be too fast
		Diff /= 300;

		m_theModel->thirdpersoncamera->RotateAroundPoint(m_theModel->thirdpersoncamera->m_vView, Diff, 0, 1, 0);

	}
	else if(m_theView->m_MouseInfo.m_LButtonUp)
	{
		m_theView->m_MouseInfo.Record = true;
		m_theView->m_MouseInfo.m_LButtonUp=false;
	}

	if(m_theView->m_MouseInfo.m_RButtonDown)
	{
		m_theView->m_MouseInfo.m_RButtonDown=false;
	}
	else if(m_theView->m_MouseInfo.m_RButtonUp)
	{
		m_theView->m_MouseInfo.m_RButtonUp=false;
	}
}

int MVC_Controller::ProcKeys(int key)
{
	if(key>=97&&key<122)
	{
		return 0x41+(key-97);
	}
	else if(key>=48&&key<57)
	{
		return 0x30+(key-48);
	}
	return 0;
}

void MVC_Controller::ProcKeyboard()
{
	bool* temp = m_theView->GetKeyBuffer();
	if(temp[VK_SPACE])
	{
		m_theModel->m_moveX=0;
		m_theModel->m_moveY=0;
	}
	if (temp[ProcKeys('d')])
	{
		m_theModel->thirdpersoncamera->StrafeCamera(1 * theTimer->GetDelta());
	}
	else if(temp[ProcKeys('a')])
	{
		m_theModel->thirdpersoncamera->StrafeCamera(-1 * theTimer->GetDelta());
	}

	if(temp[ProcKeys('w')])
	{
		m_theModel->thirdpersoncamera->MoveCamera(1 * theTimer->GetDelta());
	}
	if(temp[ProcKeys('s')])
	{
		m_theModel->thirdpersoncamera->MoveCamera(-1 * theTimer->GetDelta());
	}


	//DEBUG
	if (temp[VK_NUMPAD8])
	{
		m_theModel->thirdpersoncamera->MoveCamera(1);
	}
	if (temp[VK_NUMPAD2])
	{
		m_theModel->thirdpersoncamera->MoveCamera(-1);
	}
	if (temp[VK_F3])
	{
		m_theModel->theRoot->ApplyTranslate( 0.01f, 0.0f, 0.0f );
	}
	if (temp[VK_F4])
	{
		m_theModel->theRoot->ApplyTranslate(-0.01f, 0.0f, 0.0f);
	}

}