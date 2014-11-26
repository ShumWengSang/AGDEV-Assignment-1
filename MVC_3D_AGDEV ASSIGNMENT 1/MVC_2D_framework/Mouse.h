#ifndef __MOUSE_H__
#define __MOUSE_H__

class CMouse
{
public:
	CMouse(void);
	~CMouse(void);

	int m_x, m_y;
	int m_last_x, m_last_y;
	bool m_LButtonDown,m_RButtonDown,m_MButtonDown;
	bool m_LButtonUp,m_RButtonUp,m_MButtonUp;
	bool m_LButtonHold,m_RButtonHold,m_MButtonHold;

	void init(void)
	{
		m_x = -1;
		m_y = -1;
		m_last_x = -1;
		m_last_y = -1;
		m_LButtonDown = false;
		m_RButtonDown = false;
		m_MButtonDown = false;
		m_LButtonUp=m_RButtonUp=m_MButtonUp=false;
		m_LButtonHold=m_RButtonHold=m_MButtonHold=false;
	};

	void SetMousePos( const int new_x, const int new_y )
	{
		if (m_last_x == -1)
		{
			m_last_x = new_x;
			m_last_y = new_y;
		}
		else
		{
			m_last_x = m_x;
			m_last_y = m_y;
		}

		m_x = new_x;
		m_y = new_y;
	}

	int GetDiff_X(void)
	{
		return (m_x - m_last_x);
	}

	int GetDiff_Y(void)
	{
		return (m_y - m_last_y);
	}
};

#endif