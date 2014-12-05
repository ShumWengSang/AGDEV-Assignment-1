#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#ifndef __WINDOWS_H__
#include <windows.h> // Header File For Windows
#endif

#ifndef __GL_H__
#include <gl\gl.h> // Header File For The OpenGL32 Library
#endif

#ifndef __GLU_H__
#include <gl\glu.h> // Header File For The GLu32 Library
#endif

class SkyBox
{
public:
	SkyBox();
	~SkyBox();

	int textureID[6];
	void Draw();

	float Height, Width;
	float GetTop();
	float GetBottom();
	float GetLeft();
	float GetRight();
	float GetNear();
	float GetFar();
private:

	void Init();

	float Top;
	float Bottom;
	float Left;
	float Right;
	float Near;
	float Far;
};
#endif
