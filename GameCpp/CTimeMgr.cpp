#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"

CTimeMgr::CTimeMgr()
	: m_llPrevCount{}, m_llCurCount{}, m_llFrequency{}, m_dDT(0.), m_dAcc(0.), m_iCallCount(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	QueryPerformanceCounter(&m_llPrevCount); // 현재 카운드
	QueryPerformanceFrequency(&m_llFrequency); // 1초당 카운트 횟수 -> 1천만
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount); // 현재 카운드

	// 이전 프레임의 카운팅과 현재 프레임의 카운팅 값의 차이를 구한다.
	// (카운팅 / 프레임) / (카운팅 / 초) = 초 / 프레임
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;


	// 이전 카운트 값 갱신
	m_llPrevCount = m_llCurCount;

	m_iCallCount++;
	m_dAcc += m_dDT;

	if (m_dAcc > 1.) // 1초에 한 번
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}