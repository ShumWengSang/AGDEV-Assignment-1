#ifndef __MVCTIME_H__
#define __MVCTIME_H__

#ifndef __VECTOR_H__
#include <vector>
#define __VECTOR_H__
#endif

class MVCTime
{
public:
	typedef struct
	{
		bool active;
		long previousTime,timeInterval;
		int limiter;
	} timeKeeper;

	static MVCTime* GetInstance(void);
	static void Drop(void);

	void Init(bool limitFPS,int limit);
	void UpdateTime(void);

	float GetDelta(void);
	float GetFPS(void);
	bool TestFramerate(void);
	void SetFPSLimit(void);

	int PushNewTime(int limit);

	bool TestTime(int num,bool reSet);
	void ResetTime(int num);

	int GetTimeInterval(int num);

	void SetLimit(int num,int nlimit);
	int GetLimit(int num);

	void SetActive(bool mode,int num);
	bool GetActive(int num);

private:
	MVCTime(void);
	~MVCTime(void);
	static MVCTime* s_instance;
	int m_frameCount;
	int  m_timeInterval,m_dtInterval;
	long m_currentTime,m_previousTime,m_dtPTime;
	float m_fps;
	float m_fpsLimit;//fps limit
	float m_dt;
	bool m_resetDt;
	bool m_limitFPS;//keeps track of whether to limit fps
	std::vector<timeKeeper*> m_timer;
};

#endif