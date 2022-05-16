#pragma once

// 지역
// 전역
// 정적 (데이터 영역)
// 1. 함수 안에 -> 함수 내에서만 접근 가능
// 2. 파일 안에 -> 파일 내에서만 접근 가능
// 3. 클래스 안에 -> 정적 멤버 / 클래스 내에서 접근 가능
// 외부

//class Example
//{
//private:
//	Example();
//	~Example();
//public:
//	static int a; // 선언을 하고나서 클래스 밖에서 무조건 초기화 해주어야 함
//	Example* GetInstance()
//	{
//		return nullptr;
//	}
//	// 정적 멤버함수 , 객체없이 호출 가능 -> this 키워드가 없음 -> 멤버 접근 불가 , 정적 멤버 접근 가능
//	static void Func()
//	{
//		a = 10;
//	}
//};
//int Example::a = 0;



// Singleton Pattern
// 객체의 생성을 1개로 제한
// 어디서든 쉽게 접근이 가능
//class CCore
//{
//private:
//	CCore(); // 생성자를 private 으로 막아서 외부에서 더이상 호출이 불가함
//	~CCore();
//	static CCore* g_pInst; // 포인터는 데이터 영역
//public:
//	// 정적 멤버함수
//	static CCore* GetInstance()
//	{
//		// 이 함수가 최초 호출 된 경우
//		if (nullptr == g_pInst)
//		{
//			g_pInst = new CCore; // 동적할당 -> 객체 자체는 힙 메모리
//		}
//
//		return g_pInst;
//	}
//
//	// 동적할당된 Instance를 해제해주기 위한 함수
//	static void ReleaseInstance()
//	{
//		if (nullptr != g_pInst)
//		{
//			delete g_pInst;
//			g_pInst = nullptr;
//		}
//	}
//};

class CCore
{
	SINGLE(CCore);
private:
	CCore();
	~CCore();

	HWND	m_hWnd; // 메인 윈도우 핸들
	POINT	m_ptResolution; // 메인 윈도우 해상도
public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();
};
