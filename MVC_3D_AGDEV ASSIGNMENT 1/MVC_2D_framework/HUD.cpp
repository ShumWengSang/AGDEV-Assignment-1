#include "HUD.h"


HUD::HUD(void): theCamera(NULL)
{
	theCamDir.Set(0,0,1);
	int m_iHeightOfBar = 30;
	int m_iWidthOfBar = 30;
}


HUD::~HUD(void)
{
}

void HUD::Draw()
{
	DrawMinimap();
	DrawHealthBar(50,100);
}

void HUD::DrawHealthBar(const int m_iHealth, const int m_iMaxHealth)
{
	glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(100,25);
		glTexCoord2f(1,0); glVertex2f(100,25 + m_iHeightOfBar);
		glTexCoord2f(1,1); glVertex2f(100+((float)m_iHealth/m_iMaxHealth)*m_iWidthOfBar,25 + m_iHeightOfBar);
		glTexCoord2f(0,1); glVertex2f(100+((float)m_iHealth/m_iMaxHealth)*m_iWidthOfBar,25);	
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(100,25);
		glTexCoord2f(1,0); glVertex2f(100,25 + m_iHeightOfBar);
		glTexCoord2f(1,1); glVertex2f(100+m_iWidthOfBar,25 + m_iHeightOfBar);
		glTexCoord2f(0,1); glVertex2f(100+m_iWidthOfBar,25);	
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void HUD::DrawMinimap()
{
		// MiniMap
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_STENCIL_TEST);

	// draw circle to the stencil buffer.
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE); // replace pixel in stencil buffer
	glStencilFunc(GL_ALWAYS, 1, 0xffffffff); //always draw, replace stencil buffer pixel with 1

		glBegin(GL_TRIANGLE_FAN);
			for (int i=0; i < 360; i++)
			{
				glVertex2f(65.0f+cos(i*3.142/180)*50.0f,505.0f+sin(i*3.142/180)*50.0f);
			}
		glEnd();

		// render minimap
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilFunc(GL_EQUAL, 1, 0xffffffff);  // draw if stencil == 1 

		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, theMinimap.texID);
			glPushMatrix();
				glTranslatef(4.0,450.0,0.0);
				glBegin(GL_QUADS);
					int height = 100 * 1.333/1.5;
					glTexCoord2f(0,0); glVertex2f(10,10);
					glTexCoord2f(1,0); glVertex2f(10,10 + height);
					glTexCoord2f(1,1); glVertex2f(110,10 + height);
					glTexCoord2f(0,1); glVertex2f(110,10);	
				glEnd();
			glPopMatrix();
			glDisable(GL_BLEND);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

	glDisable(GL_STENCIL_TEST);

	// Player icon in minimap
	glPushMatrix();
		glColor3f(1.0f,1.0f,0.0f);
		glTranslatef(65.0, 510.0,0.0);
		glPushMatrix();
			glRotatef( atan2(theCamDir.m_x, theCamDir.m_z) * 180/3.142, 0, 0, 1);
			glBegin(GL_TRIANGLES);
				glVertex2f( 0.0f, -10.0f );
				glVertex2f( 5.0f, 10.0f );
				glVertex2f( -5.0f, 10.0f );
			glEnd();
		glPopMatrix();
	glPopMatrix();
}