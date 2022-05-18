#include "pch.h"
#include "CTimeMgr.h"


CTimeMgr::CTimeMgr()
	: m_llCurCount{}, m_llFrequency{}
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	QueryPerformanceCounter(&m_llCurCount); // 
	QueryPerformanceFrequency(&m_llFrequency); // 1초당 차이 -> 1천만
}
