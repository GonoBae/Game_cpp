#include "pch.h"
#include "CCore.h"
#include "CObject.h"

//CCore* CCore::g_pInst = nullptr;

CObject g_obj;

CCore::CCore()
	: m_hWnd(0), m_ptResolution{}, m_hDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC); // 윈도우에 달려있는 DC 해지
}

void CCore::update()
{
	// 물체들의 변경점을 체크
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // 눌렸다면
	{
		g_obj.m_ptPos.x -= 1;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_obj.m_ptPos.x += 1;
	}
}

void CCore::render()
{
	// 그리기
	Rectangle(m_hDC,
		g_obj.m_ptPos.x - g_obj.m_ptScale.x / 2,
		g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2,
		g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2,
		g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	//if (FAILED(S_OK)) // FAILED 매크로 : 음수이면 참 -> 에러
	//{
	//
	//}

	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	RECT rt = {0, 0, m_ptResolution.x, m_ptResolution.y}; // 좌상단 0 , 0 ::: 우하단 x , y

	// 해상도에 맞게 윈도우 크기 조정
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true); // 사각형 크기 , 스타일 , 메뉴바 t / f
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0); // ID, ? , 시작 좌상단, 가로 길이 , 세로 길이 , flag(?)
	
	m_hDC = GetDC(m_hWnd); // 그리기 할 목적지 기입

	g_obj.m_ptPos = POINT{ m_ptResolution.x / 2, m_ptResolution.y / 2 };
	g_obj.m_ptScale = POINT{ 100, 100 };


	return S_OK;
}



void CCore::progress()
{
	static int callCount = 0;
	callCount++;
	static int iPrevCount = GetTickCount();
	int iCurCount = GetTickCount();
	if (GetTickCount() - iPrevCount > 1000)
	{
		iPrevCount = iCurCount;
		callCount = 0;
	}

	update();
	render();


	// 메시지를 사용하지 않으므로 여기서 가능해야함
	
}
