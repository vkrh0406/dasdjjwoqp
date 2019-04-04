// GameHw1.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "GameHw1.h"
#include <string>
#include <stack>
#include <stdlib.h>
#include <string>

#define MAX_LOADSTRING 100


struct student {
	std::wstring name;
	int jumsu;
	int red;
	int green;
	int blue;
};

std::wstring Rnames[] = { L"김갑수",L"김철수",L"김영희",L"연가시",L"조롱이",L"송영삼",L"김길치",L"영화지",L"구궁그",L"김바보",L"여력석",L"바오밥" }; //랜덤으로 넣을 이름들

std::stack<student> std_stack;// 정보 넣을 스택 선언




// 전역 변수:

HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAMEHW1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMEHW1));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEHW1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GAMEHW1);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
  

   student ts = { L"김상수",50 };
   std_stack.push(ts);


   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}



LRESULT drawRectangle(HWND hWnd,HDC hdc)///스택에서 순서대로 박스 그려주는 함수
{
	LPCWSTR charname;  //String -> TCHAR 형변환 하기위해 미리 선언 
	LPCWSTR charJumsu;

	int x = 600;  //초기 박스가 위치할 좌표 x y
	int y = 10;
	int count;  //스택의 사이즈

	HPEN hMyRedPen= CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	HGDIOBJ hOldPen= SelectObject(hdc, hMyRedPen);
	SetTextAlign(hdc, TA_CENTER); //텍스트 가운데 정렬

	std::stack<student> temp = std_stack;
	count = temp.size();
	for (int i=0;i<count;i++)
	{
		student stdtemp = temp.top();
		temp.pop();
		hMyRedPen = CreatePen(PS_SOLID, 3, RGB(stdtemp.red,stdtemp.green,stdtemp.blue)); // 구조체에서 색을 불러와 펜을 생성함
		hOldPen = SelectObject(hdc, hMyRedPen);

		Rectangle(hdc, x, y, x + 200, y + 100);
	

		std::wstring jumsu = std::to_wstring(stdtemp.jumsu); //int -> wstring
		
	
		charname = stdtemp.name.c_str();   //wstring -> LPCWSTR
		charJumsu = jumsu.c_str();
		// 텍스트 출력
		TextOut(hdc, x + 100, y + 35, charname, wcslen(charname));
		TextOut(hdc, x + 100, y + 60, charJumsu, wcslen(charJumsu));

		y = y + 110;
	}


	SelectObject(hdc, hOldPen); // 원래 객체를 복원함
	DeleteObject(hMyRedPen);




	
	

	return 0;
}





//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
	case WM_LBUTTONDOWN:

		// lParam에서 x, y 좌표값 받아오기
		FLOAT x, y; 
		x = LOWORD(lParam);
		y = HIWORD(lParam);

		// 특정 좌표값의 클릭인지 확인함 (맨위 박스)
		if (x >= 600 && x <= 800 && y >= 10 && y <= 110)
		{
			if(!std_stack.empty())//스택이 비어있지 않다면 pop
				std_stack.pop();
			else//스택이 비어있다면
			{
				MessageBoxA(hWnd, "스택이 비어있습니다.", "오류", MB_OK);
			}
		
			

		}
		else if (std_stack.size() < 6) //스택이 6개 미만일때만 삽임
		{
			student tmpstd = { Rnames[rand() % 11],rand() % 30 + 20 , rand()%200,rand()%200,rand()%200}; 
			std_stack.push(tmpstd);
		}
		else
		{
			MessageBoxA(hWnd, "스택이 꽉찼습니다.", "오류", MB_OK);
		}


		InvalidateRect(hWnd, NULL, TRUE); //화면 다시 그리기

		break;


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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);


			drawRectangle(hWnd,hdc);


           
            EndPaint(hWnd, &ps);
        }
        break;
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
