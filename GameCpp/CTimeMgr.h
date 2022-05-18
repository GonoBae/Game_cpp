#pragma once

// 컴퓨터 성능과 상관없이 움직이는 물체는 일정한 속도로 움직여야 함.
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency;
	// FPS
	// 1. 프레임당 시간 -> Delta Time

public:
	void init();
};

