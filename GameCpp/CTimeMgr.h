#pragma once

// 컴퓨터 성능과 상관없이 움직이는 물체는 일정한 속도로 움직여야 함.
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency;
	
	double		  m_dDT; // 프레임 간의 시간 값
	double		  m_dAcc; // 누적 시간 (1초 측정하기 위해)
	UINT		  m_iCallCount; // 초당 호출 횟수
	UINT		  m_iFPS; // 초당 호출 횟수
	// FPS
	// 1. 프레임당 시간 -> Delta Time

public:
	void init();
	void update();
	void render();

	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

