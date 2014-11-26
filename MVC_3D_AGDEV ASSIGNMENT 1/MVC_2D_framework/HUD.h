#ifndef __HUD_H__
#define __HUD_H__

#ifndef __CAMERA_H__
#include"camera.h"
#endif

#ifndef __WINDOWS_H__
#include <windows.h> // Header File For Windows
#endif
#ifndef __GL_H__
#include <gl\gl.h> // Header File For The OpenGL32 Library
#endif

#ifndef __GLU_H__
#include <gl\glu.h> // Header File For The GLu32 Library
#endif

#ifndef __TEXTURE_H__
#include "texture.h"
#endif

#ifndef __VECTOR_H__
#include "vector3D.h"
#endif

class HUD
{
public:
	HUD(void);
	~HUD(void);

	void GetCameraDirection(Vector3D CamDir);
	Vector3D theCamDir;

	Camera * theCamera;
	TextureImage theMinimap;
	void DrawMinimap();
	void Draw();
	void DrawHealthBar(const int m_iHealth, const int m_iMaxHealth);

	int m_iHeightOfBar;
	int m_iWidthOfBar;

	
};

#endif