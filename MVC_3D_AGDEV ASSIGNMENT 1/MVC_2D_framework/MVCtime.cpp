#ifndef __MVCTIME_H__
#include"MVCtime.h"
#endif

#ifndef __WINDOWS_H__
#include <Windows.h>//for timeGetTime
#define __WINDOWS_H__
#endif

MVCTime* MVCTime::GetInstance(void)
{
	if(s_instance==NULL)
	{
		s_instance=new MVCTime();
	}
	return s_instance;
}

void MVCTime::Drop(void)
{
	if(s_instance!=NULL)
	{
		delete s_instance;
	}
}

MVCTime* MVCTime::s_instance=NULL;

void MVCTime::UpdateTime()
{

	long ctime=timeGetTime();
	m_currentTime=ctime;

	m_dtInterval=m_currentTime-m_dtPTime;
	m_dt=float(m_dtInterval)*0.001f;
	if(m_resetDt||!m_limitFPS)
	{
		//increase frame count
		m_frameCount++;
		m_dtPTime=m_currentTime;
		m_resetDt=false;
	}


	std::vector<timeKeeper*>::iterator end=m_timer.end();
	for(std::vector<timeKeeper*>::iterator it=m_timer.begin();it!=end;++it)
	{
		timeKeeper* t=*it;
		if(t->active)
			t->timeInterval=m_currentTime-t->previousTime;
	}

	//calculate time passed
	m_timeInterval=m_currentTime-m_previousTime;

	if(m_timeInterval>1000)//updates fps every 1s
	{
		//calculate the number of frames per second
		m_fps=float(float(m_frameCount)/(float(m_timeInterval)*0.001f));

		//Set time
		m_previousTime=m_currentTime;

		//reSet frame count
		m_frameCount=0;
	}
}

MVCTime::~MVCTime()
{

}

MVCTime::MVCTime()
{
	m_frameCount=m_timeInterval=m_dtInterval=0;
	m_dt=0.f;
	m_previousTime=m_currentTime=m_dtPTime=timeGetTime();
	m_fps=0.0f;
}

void MVCTime::Init(bool limitFPS=false,int limit=0)
{
	m_frameCount=0;
	m_previousTime=m_currentTime=m_dtPTime=timeGetTime();
	m_fps=0.0f;
	m_limitFPS=limitFPS;
	m_fpsLimit=float(1000.f/limit);
}

float MVCTime::GetDelta(void)
{
	return m_dt;
}

float MVCTime::GetFPS(void)
{
	return m_fps;
}

bool MVCTime::TestFramerate(void)
{
	if(m_limitFPS)
	{
		if(m_dtInterval>=m_fpsLimit*0.9f)
		{
			m_resetDt=true;
			//std::cout<<"time interval(reSet):"<<dtInterval<<" "<<fpsLimit<<"\n";
			return true;
		}
			//std::cout<<"time interval:"<<dtInterval<<" "<<fpsLimit<<"\n";		
		return false;
	}
	return true;
}

int MVCTime::PushNewTime(int limit)
{
	timeKeeper* Ntime=new timeKeeper;
	Ntime->limiter=limit;
	Ntime->active=true;
	Ntime->timeInterval=0;
	Ntime->previousTime=timeGetTime();
	m_timer.push_back(Ntime);
	return m_timer.size()-1;
}

bool MVCTime::TestTime(int num,bool reSet=true)
{
	if(m_timer[num]->active)
	{
		if(m_timer[num]->timeInterval>m_timer[num]->limiter)
		{
			if(reSet)
				ResetTime(num);
			return true;
		}
		return false;
	}
	else
		return true;
}

void MVCTime::ResetTime(int num)
{
	m_timer[num]->previousTime=m_currentTime;
	m_timer[num]->timeInterval=0;
}

int MVCTime::GetTimeInterval(int num)
{
	return m_timer[num]->timeInterval;
}

void MVCTime::SetLimit(int num,int nlimit)
{
	m_timer[num]->limiter=nlimit;
}

int MVCTime::GetLimit(int num)
{
	return m_timer[num]->limiter;
}

void MVCTime::SetActive(bool mode,int num)
{
	m_timer[num]->active=mode;
}

bool MVCTime::GetActive(int num)
{
	return m_timer[num]->active;
}