#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"

//CCore* CCore::g_pInst = nullptr;

//CObject g_obj;

CCore::CCore()
	: m_hWnd(0), m_ptResolution{}, m_hDC(0), m_hBit(0), m_memDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC); // 윈도우에 달려있는 DC 해지

	// Create 으로 만든건 Delete 로 지우라고 나와있음
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

//void CCore::update()
//{
//	Vec2 vPos = g_obj.GetPos();
//
//	// 물체들의 변경점을 체크
//	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
//	{
//		vPos.x -= 200.f * CTimeMgr::GetInst()->GetfDT();
//	}
//
//	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
//	{
//		vPos.x += 200.f * CTimeMgr::GetInst()->GetfDT();
//	}
//
//	g_obj.SetPos(vPos);
//}

//void CCore::render()
//{
//	Vec2 vPos = g_obj.GetPos();
//	Vec2 vScale = g_obj.GetScale();
//
//	// 그리기 -> 화면에 안나옴
//	Rectangle(m_memDC,
//		int(vPos.x - vScale.x / 2.f),
//		int(vPos.y - vScale.y / 2.f),
//		int(vPos.x + vScale.x / 2.f),
//		int(vPos.y + vScale.y / 2.f));
//
//	
//}

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
	
	m_hDC = GetDC(m_hWnd); // 그리기 할 목적지 기입 -> 비트맵

	// 이중 버퍼링 용도의 비트맵과 DC 를 만든다.
	// 그려진 픽셀 덩어리 -> 비트맵
	// 여분의 비트맵을 하나 더 만들어서 내 창에 복사해오기 위한 것
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y); // 똑같은 크기의 비트맵을 만들어 ID 전달
	m_memDC = CreateCompatibleDC(m_hDC); // 여분의 비트맵을 담당할 DC 가 필요함

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit); // 그림을 그릴 타겟을 바꿔줌 -> 디폴트(1픽셀) 비트맵을 반환
	DeleteObject(hOldBit); // 디폴트 비트맵 삭제


	// Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();


	//g_obj.SetPos(Vec2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2)));
	//g_obj.SetScale(Vec2( 100, 100 ));


	return S_OK;
}



void CCore::progress()
{
	// 메시지를 사용하지 않으므로 여기서 가능해야함

	/*static int callCount = 0;
	callCount++;
	static int iPrevCount = GetTickCount();
	int iCurCount = GetTickCount();
	if (GetTickCount() - iPrevCount > 1000)
	{
		iPrevCount = iCurCount;
		callCount = 0;
	}*/

	// Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	
	CSceneMgr::GetInst()->update();


	// ========
	// Rendering
	// ========
	// 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC); // memDC 를 전달해주어야 어디에 그릴지 알 수 있음

	// 전달해주기 : 그림을 아무리 많이 그려도 전체를 복사하는 것이기에 고정비용임
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();
}
