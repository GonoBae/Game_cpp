// GameCpp.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "pch.h"
#include "framework.h"
#include "GameCpp.h"
#include "CCore.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND      g_hwnd; // 메인 윈도우 핸들
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// SAL -> 주석언어(설명)
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // 실행 된 프로세스의 시작 주소 -> 여러 개를 실행시켜도 하나의 인스턴스 (가상 메모리 주소)
                     _In_opt_ HINSTANCE hPrevInstance, // 이전에 실행 된 프로세스의 시작 주소
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // 의미없는 코드를 참조하지 않는다고 알려주는 역할
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAMECPP, szWindowClass, MAX_LOADSTRING);

    // 윈도우 정보 등록
    MyRegisterClass(hInstance);

    // 윈도우 생성 (창)
    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // Core 초기화 -> 초기화 실패하면 FALSE -> 프로그램 종료
    if (FAILED(CCore::GetInst()->init(g_hwnd, POINT{1280, 768})))
    {
        MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);
        return FALSE;
    }

    // 단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMECPP));

    MSG msg;

    // 겁나 느림 (윈도우메시지 처리떄문에)
    //SetTimer(g_hwnd, 0, 0, nullptr); // 2 번째 인자는 Timer ID , 3 번째 인자가 시간 (ms) -> 0 이라도 컴퓨터 성능에 따라서 최대치로 동작

    // GetMessage
    // 기본 메시지 루프입니다:
    // 메시지 큐에서 메시지가 확인 될 때까지 대기
    // msg.message == WM_QUIT --> false 반환

    // PeekMessage
    // 메시지 유무와 관계없이 항상 반환됨

    //DWORD dwPrevCount = GetTickCount();
    //DWORD dwAccCount = 0;
    

    while (true) // True or False 를 반환하는 GetMessage -> While 문이 끝나면 프로그램이 종료됨을 뜻함
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) // 메시지큐에서 메시지 확인 후 메시지있으면 true 와 없으면 false 를 반환함
        {
            //int iTime = GetTickCount();

            if (WM_QUIT == msg.message) break;
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            //int iAdd = (GetTickCount() - iTime);
            //dwAccCount += iAdd;
        }
        else
        {
            // 메시지가 없는동안 호출
            // ------------------------------------------->> 컴퓨터가 얼마나 노는지 체크해보기
            //DWORD dwCurCount = GetTickCount();
            //if (dwCurCount - dwPrevCount > 1000)
            //{
                //float fRatio = (float)dwAccCount / 1000.f;
                //wchar_t szBuff[50] = {};
                //swprintf_s(szBuff, L"비율 : %f", fRatio);
                //SetWindowText(g_hwnd, szBuff);

                //dwPrevCount = dwCurCount;
                //dwAccCount = 0;
            //}

            // -------------------------------------------->> Game 코드 수행
            // 디자인 패턴 (설계 유형)
            // Singleton 패턴은 모르면 안됨!!!

            CCore::GetInst()->progress();

        }
    }

    //KillTimer(g_hwnd, 0); // 0 번 타이머를 끔

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMECPP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GAMECPP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hwnd)
   {
      return FALSE;
   }

   // 창을 화면에 띄우는 함수 -> hWnd 로 창의 아이디값을 받아서 동작
   ShowWindow(g_hwnd, nCmdShow);
   UpdateWindow(g_hwnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
// HWND (ID) 를 받아서 메시지를 전달
//int g_x = 0;
//int g_y = 0;
//
//#include <vector>
//using std::vector;
//struct tObjInfo
//{
//    POINT g_ptObjPos;
//    POINT g_ptObjScale;
//};
//
//vector<tObjInfo> g_vecInfo;
//
//// 좌 상단
//POINT g_ptLT;
//// 우 하단
//POINT g_ptRB;
//
//// 마우스 클릭 bool
//bool blbtnDown = false;

// 여러 이벤트 테스트하기
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT: // 무효화 영역(Invalidate)이 발생한 경우 -> 창이 다시 화면에 나타나는 경우 -> 중단점 걸고 확인해보면 됨
        // case 문 안에서 지역변수를 선언하고 싶다면 괄호가 필요함 (지역이 필요함)
        {
            PAINTSTRUCT ps;
            // Device Context 만들어서 ID 를 반환
            HDC hdc = BeginPaint(hWnd, &ps); // 화면을 다시 그려준다.
            // Device Context -> 그리기 작업을 수행하는데 필요한 Data 집합체
            // DC 의 목적지는 hWnd
            // DC 의 펜은 기본 펜 (Black)
            // DC 의 브러쉬는 기본 브러쉬 (White)

            // 윈도우 핸들 ( 화면을 그릴 윈도우 창의 ID )
            // 윈도우 좌표 ( 단위는 픽셀 <R , G , B 각 1 바이트>, 타이틀 & 메뉴바 밑의 작업공간 왼쪽 상단이 0,0 )
            // HDC , HWND , HPEN , HBRUSH ? -> 쓰임새가 다르므로 구분해주기 위해 ( 각 구조체는 int ID 하나만 가지고 있음 )
            //Rectangle(hdc, 10, 10, 110, 110); // 배경이 White 로 채워진 것
            
            // 직접 펜을 만들어서 DC 에 줘보자.
            HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            // 자주쓰는 오브젝트는 미리 만들어서 저장해둠 GetStockObject();
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));

            // ((COLORREF)(((BYTE)(255) | ((WORD)((BYTE)(0)) << 8)) | (((DWORD)(BYTE)(0)) << 16)))
            // Blue 를 16비트 왼쪽으로 밀고 Green 을 8비트 왼쪽으로 밀고 R은 그대로 하고 합침
            // 결국 메모리는 B G R 순으로 되어있음

            // 펜을 만들었으면 적용해주자.
            // 기본 펜 ID 값을 받아둠
            //HPEN hdefaultPen = (HPEN)SelectObject(hdc, hRedPen); // 사용자가 캐스팅해서 적절히 사용하라고 HGDIOBJ 반환형 (void 포인터 반환형)
            //HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);
            // 변경된 펜으로 사각형 그림
            /*if (blbtnDown)
            {
                Rectangle(hdc,
                    g_ptLT.x, g_ptLT.y,
                    g_ptRB.x, g_ptRB.y);
            }*/
            //Rectangle(hdc, 1180, 668, 1280, 768);
            // 추가한 사각형도 그려준다. -> 물체가 늘어날 때마다 깜빡임이 엄청나다. -> 메세지가 없으면 화면을 다시 그리지 않음 -> NPC OR Enemy 는?
            /*for (size_t i = 0; i < g_vecInfo.size(); i++)
            {
                Rectangle(hdc,
                    g_vecInfo[i].g_ptObjPos.x - g_vecInfo[i].g_ptObjScale.x / 2,
                    g_vecInfo[i].g_ptObjPos.y - g_vecInfo[i].g_ptObjScale.y / 2,
                    g_vecInfo[i].g_ptObjPos.x + g_vecInfo[i].g_ptObjScale.x / 2,
                    g_vecInfo[i].g_ptObjPos.y + g_vecInfo[i].g_ptObjScale.y / 2);
            }*/

            // DC의 펜을 원래 펜으로 되돌림
            //SelectObject(hdc, hdefaultPen);
            //SelectObject(hdc, hDefaultBrush);
            // 사용한 빨간펜 지우기 (CreateObject 하면 지워줘야함)
            //DeleteObject(hRedPen);
            //DeleteObject(hBlueBrush);
            
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_KEYDOWN: // 입력이 한 템포 느리고 동시입력이 안됨
        // 키 입력을 받으면 중단걸림
    {
    //    switch (wParam)
    //    {
    //        // 바로바로 적용이 안됨 -> 화면을 줄였다가 띄워야 적용됨
    //    case VK_UP:
    //        //g_ptObjPos.y -= 20;
    //        //InvalidateRect(hWnd, nullptr, false); // 해결방법 : 무효화 영역을 지정 (nullptr => 전체영역) / 그려지긴 하지만 이전에 그렸던 정보가 사라지지 않음
    //        InvalidateRect(hWnd, nullptr, true); // Erase 로 화면을 지워주기 위해 true 대입
    //        break;
    //    case VK_DOWN:
    //        //g_ptObjPos.y += 20;
    //        InvalidateRect(hWnd, nullptr, true);
    //        break;
    //    case VK_RIGHT:
    //        //g_ptObjPos.x += 20;
    //        InvalidateRect(hWnd, nullptr, true);
    //        break;
    //    case VK_LEFT:
    //        //g_ptObjPos.x -= 20;
    //        InvalidateRect(hWnd, nullptr, true);
    //        break;
    //    }
    }   
        break;
    case WM_LBUTTONDOWN:
    {
        // 좌클릭 입력
        // 작업공간 기준
        //g_ptLT.x = LOWORD(lParam); // x 좌표
        //g_ptLT.y = HIWORD(lParam); // y 좌표
        //blbtnDown = true;
    }
        break;
    case WM_LBUTTONUP:
    {
        /*tObjInfo info = {};
        info.g_ptObjPos.x = (g_ptLT.x + g_ptRB.x) / 2;
        info.g_ptObjPos.y = (g_ptLT.y + g_ptRB.y) / 2;

        info.g_ptObjScale.x = abs(g_ptLT.x - g_ptRB.x);
        info.g_ptObjScale.y = abs(g_ptLT.y - g_ptRB.y);

        g_vecInfo.push_back(info);

        blbtnDown = false;
        InvalidateRect(hWnd, nullptr, true);*/
    }
        break;
    case WM_MOUSEMOVE:
        /*g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);*/
        // vector 에 데이터 추가 후 InvalidateRect 때문에 계속 사각형이 작동함 -> bool 변수로 마우스 Down/Up 추가
        // 마우스를 움직여야 InvalidateRect 가 작동하기에 마우스 Up 으로 vector 에 데이터 추가해도 사각형은 남아있고 마우스 움직여야 사라짐
        // -> 마우스 Up 일 때도 InvalidateRect 추가
        /*InvalidateRect(hWnd, nullptr, true);*/
        break;

    //case WM_TIMER:
    //    SetTimer 함수로 인해 들어옴
    //    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
