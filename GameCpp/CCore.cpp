#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

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
	Vec2 vPos = g_obj.GetPos();

	// 물체들의 변경점을 체크
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // 눌렸다면
	{
		//vPos.x -= 100.f * DeltaTime;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 0.01;
	}

	g_obj.SetPos(vPos);
}

void CCore::render()
{
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	// 그리기
	Rectangle(m_hDC,
		int(vPos.x - vScale.x / 2.f),
		int(vPos.y - vScale.y / 2.f),
		int(vPos.x + vScale.x / 2.f),
		int(vPos.y + vScale.y / 2.f));
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

	// Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();


	g_obj.SetPos(Vec2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2)));
	g_obj.SetScale(Vec2( 100, 100 ));


	return S_OK;
}



void CCore::progress()
{
	/*static int callCount = 0;
	callCount++;
	static int iPrevCount = GetTickCount();
	int iCurCount = GetTickCount();
	if (GetTickCount() - iPrevCount > 1000)
	{
		iPrevCount = iCurCount;
		callCount = 0;
	}*/

	update();
	render();


	// 메시지를 사용하지 않으므로 여기서 가능해야함
	
}
