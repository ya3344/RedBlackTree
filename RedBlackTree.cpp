// RedBlackTree.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "RedBlackTree.h"
#include "RedBlackClass.h"
#include "TestSystem.h"
#define MAX_LOADSTRING 100

enum eWindowINdex
{
    WINDOW_WIDTH = 1680,
    WINDOW_HEIGHT = 800,
};

enum eDrawIndex
{
    nodeSize = 15,
    lineSize = 30,
    heightSize = 40,
};

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND gHWnd;
HIMC gHOldIMC;
RedBlackClass gRedBlakcClass;
TestSystem gTestSystem(&gRedBlakcClass);
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
    LoadStringW(hInstance, IDC_REDBLACKTREE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_REDBLACKTREE));

    MSG msg;
    RECT windowRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

    // 테스트 시스템 클래스 초기화
  
    //gRedBlakcClass.InsertNode(10);
    //gRedBlakcClass.InsertNode(11);
    //gRedBlakcClass.InsertNode(12);
    //gRedBlakcClass.InsertNode(13);
    //gRedBlakcClass.InsertNode(5);
    //gRedBlakcClass.InsertNode(3);
    //gRedBlakcClass.InsertNode(9);
    //gRedBlakcClass.InsertNode(100);
    //gRedBlakcClass.InsertNode(20);
    //gRedBlakcClass.InsertNode(1);
    //gRedBlakcClass.InsertNode(2);
    //gRedBlakcClass.InsertNode(4);
    //gRedBlakcClass.InsertNode(7);
    //gRedBlakcClass.InsertNode(8);
    //gRedBlakcClass.InsertNode(111);
    //gRedBlakcClass.InsertNode(112);
    //gRedBlakcClass.InsertNode(101);
    //gRedBlakcClass.InsertNode(24);
    //gRedBlakcClass.InsertNode(23);
    //gRedBlakcClass.InsertNode(22);
    //gRedBlakcClass.InsertNode(25);
    //gRedBlakcClass.InsertNode(26);
    gTestSystem.RandomInsert();
   /* gRedBlakcClass.InsertNode(10);
    gRedBlakcClass.InsertNode(5);
    gRedBlakcClass.InsertNode(14);
    gRedBlakcClass.InsertNode(13);
    gRedBlakcClass.InsertNode(15);
    gRedBlakcClass.InsertNode(3);
    gRedBlakcClass.InsertNode(6);
    gRedBlakcClass.InsertNode(4);
    gRedBlakcClass.InsertNode(1);
    gRedBlakcClass.InsertNode(2);
    gRedBlakcClass.InsertNode(7);
    gRedBlakcClass.InsertNode(8);*/
  //  gRedBlakcClass.InsertNode(3);
   // gRedBlakcClass.InsertNode(7);
  //  gRedBlakcClass.RightRotation(gRedBlakcClass.GetRootNode());
    wprintf(L"Origin Inorder:");
    gRedBlakcClass.InorderPrint(gRedBlakcClass.GetRootNode());
    wprintf(L"\nNode Num:%d\n", gRedBlakcClass.GetNodeNum());

  /*  gRedBlakcClass.DeleteNode(10);
    gRedBlakcClass.DeleteNode(11);
    gRedBlakcClass.DeleteNode(12);
    gRedBlakcClass.DeleteNode(13);
    gRedBlakcClass.DeleteNode(5);
    gRedBlakcClass.DeleteNode(3);
    gRedBlakcClass.DeleteNode(9);
    gRedBlakcClass.DeleteNode(100);
    gRedBlakcClass.DeleteNode(20);
    gRedBlakcClass.DeleteNode(1);
    gRedBlakcClass.DeleteNode(2);
    gRedBlakcClass.DeleteNode(4);
    gRedBlakcClass.DeleteNode(7);
    gRedBlakcClass.DeleteNode(8);
    gRedBlakcClass.DeleteNode(111);
    gRedBlakcClass.DeleteNode(112);
    gRedBlakcClass.DeleteNode(101);
    gRedBlakcClass.DeleteNode(24);
    gRedBlakcClass.DeleteNode(23);*/
   // gRedBlakcClass.DeleteNode(22);
  //  gRedBlakcClass.DeleteNode(25);
   // gRedBlakcClass.DeleteNode(26);

   /* wprintf(L"Delete Inorder:");
    gRedBlakcClass.InorderPrint(gRedBlakcClass.GetRootNode());
    wprintf(L"\nNode Num:%d\n", gRedBlakcClass.GetNodeNum());
    wprintf(L"\n\n");*/
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_REDBLACKTREE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_REDBLACKTREE);
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

   gHWnd = CreateWindowEx(0, szTitle, szTitle, WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
       CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

   if (gHWnd == NULL)
       return FALSE;

   ShowWindow(gHWnd, SW_SHOW);
   UpdateWindow(gHWnd);
   SetFocus(gHWnd);

   RECT windowRect;
   windowRect.top = 0;
   windowRect.left = 0;
   windowRect.right = WINDOW_WIDTH;
   windowRect.bottom = WINDOW_HEIGHT;

   AdjustWindowRectEx(&windowRect, GetWindowStyle(gHWnd), GetMenu(gHWnd) != NULL,
       GetWindowExStyle(gHWnd));

   int x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (WINDOW_WIDTH / 2); //화면의 크기를 얻어서 정 중앙으로
   int y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (WINDOW_HEIGHT / 2);

   MoveWindow(gHWnd, x, y,
       windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, TRUE);

   // IME 삭제, 원래 가지고 있던 IME 핸들을 리턴해줌. (WM_CREATE 에서 호출)
   gHOldIMC = ImmAssociateContext(gHWnd, NULL);

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


void DrawRedBlackTree(HDC hdc, POINT rootPos, POINT standardPos, int depth,
    RedBlackClass::NodeInfo* node, int size, POINT parentPos)
{
    TCHAR inputText[20] = { 0, };
    POINT nodePos;
    POINT currentPos;
    RECT rectNodeSize = { -nodeSize, -nodeSize, nodeSize, nodeSize };
    RECT resultNodePos;
    WORD lineLen = (lineSize * size) / 2;
    RedBlackClass::NodeInfo* parentNode = nullptr;

    if (nullptr == node)
    {
        CONSOLE_ERROR_LOG("node nullptr!");
        return;
    }

    parentNode = node->parent;
    if (parentNode != nullptr)
    {    
        nodePos = parentPos;
        nodePos = PointPlus(nodePos, standardPos);
        MoveToEx(hdc, nodePos.x, nodePos.y, NULL);
    }

    if (parentNode == nullptr)
    {
        nodePos = { 0, rootPos.y + heightSize * depth };
    }
    else if (parentNode->data > node->data)
    {
        nodePos = { parentPos.x - lineLen / depth + 1,
                    rootPos.y + heightSize * depth };
    }
    else
    {
        nodePos = { parentPos.x + lineLen / depth + 1,
                    rootPos.y + heightSize * depth };
    }

    // 노드 위치 저장
    currentPos = nodePos;

    // 노드 사이즈 및 기준점을 고려하여 노드 위치 계산
    nodePos = PointPlus(nodePos, standardPos);
    resultNodePos = RectPointPlus(rectNodeSize, nodePos);

    if (parentNode != nullptr)
    {
        LineTo(hdc, nodePos.x, nodePos.y);
    }

    if (node->color == RedBlackClass::NodeInfo::BLACK)
    {
        SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
        Ellipse(hdc, resultNodePos.left, resultNodePos.top, resultNodePos.right, resultNodePos.bottom);
    }
    else
    {
        SetDCBrushColor(hdc, RGB(255, 0, 0));
        SelectObject(hdc, (HBRUSH)GetStockObject(DC_BRUSH));
        Ellipse(hdc, resultNodePos.left, resultNodePos.top, resultNodePos.right, resultNodePos.bottom);
    }
    wsprintf(inputText, L"%d", node->data);
    DrawText(hdc, inputText, -1, &resultNodePos, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //	선 때문에 가려지는 노드 새로 그려주기.
    if (parentNode != nullptr)
    {
        nodePos = parentPos;
        nodePos = PointPlus(nodePos, standardPos);
        resultNodePos = RectPointPlus(rectNodeSize, nodePos);

        if (parentNode->color == RedBlackClass::NodeInfo::BLACK)
        {
            SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
            Ellipse(hdc, resultNodePos.left, resultNodePos.top, resultNodePos.right, resultNodePos.bottom);
        }
        else
        {
            SetDCBrushColor(hdc, RGB(255, 0, 0));
            SelectObject(hdc, (HBRUSH)GetStockObject(DC_BRUSH));
            Ellipse(hdc, resultNodePos.left, resultNodePos.top, resultNodePos.right, resultNodePos.bottom);
        }

        wsprintf(inputText, L"%d", parentNode->data);
        DrawText(hdc, inputText, -1, &resultNodePos, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    if (node->left != gRedBlakcClass.GetNilNode())
        DrawRedBlackTree(hdc, rootPos, standardPos, depth + 1, node->left, size, currentPos);
    if (node->right != gRedBlakcClass.GetNilNode())
        DrawRedBlackTree(hdc, rootPos, standardPos, depth + 1, node->right, size, currentPos);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    HDC layDC;
    HBITMAP lay;
    PAINTSTRUCT ps;
    RECT windowRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    RECT inputRect = { 50, WINDOW_HEIGHT - 100, 150, WINDOW_HEIGHT - 70 };
    RECT insertRect = { 160, WINDOW_HEIGHT - 100, 230, WINDOW_HEIGHT - 70 };
    RECT deleteRect = { 240, WINDOW_HEIGHT - 100, 310, WINDOW_HEIGHT - 70 };
    RECT clearRect = { 320, WINDOW_HEIGHT - 100, 390, WINDOW_HEIGHT - 70 };
    RECT randomInsertRect = { 400, WINDOW_HEIGHT - 100, 510, WINDOW_HEIGHT - 70 };
    RECT tempRect;
    TCHAR textInput[128] = { 0, };
    static TCHAR textNodeInput[26] = { 0, };
    POINT rootPos = { WINDOW_WIDTH / 2, 50 };
    static POINT standardPos = { WINDOW_WIDTH / 2, 0 };
    static POINT selPos;
    WORD depth = 0;
    static SIZE size;
    static BYTE inputLen;
    static POINT mousePoint;
    static bool isClip = false;
    WORD nodeNum = 0;

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
    case WM_CHAR:
        {
            inputLen = lstrlen(textNodeInput);
            if (inputLen < 3 && wParam >= 48 && wParam <= 58)
            {
                textNodeInput[inputLen] = (TCHAR)wParam;
                textNodeInput[inputLen + 1] = NULL;

                InvalidateRect(hWnd, NULL, true);
            }
            switch (wParam)
            {
                // backspace
                case 8:
                {
                    if (inputLen > 0)
                        textNodeInput[inputLen - 1] = NULL;
 
                    InvalidateRect(hWnd, NULL, false);
                    break;
                }
            }
        }
        break;
    case WM_MOUSEMOVE:
	    {
            mousePoint.x = LOWORD(lParam);
            mousePoint.y = HIWORD(lParam);

		    if (isClip)
		    {
			    standardPos = PointPlus(standardPos, PointMinus(mousePoint, selPos));
			    selPos = mousePoint;
			    InvalidateRect(hWnd, NULL, false);
		    }
	    }
        break;
    case WM_LBUTTONDOWN:
        {
            mousePoint.x = LOWORD(lParam);
            mousePoint.y = HIWORD(lParam);

            nodeNum = _wtoi(textNodeInput);
            if (PtInRect(&insertRect, mousePoint))
            {
                gRedBlakcClass.InsertNode(nodeNum);
                textNodeInput[0] = NULL;
                wprintf(L"Inorder:");
                gRedBlakcClass.InorderPrint(gRedBlakcClass.GetRootNode());
                wprintf(L"\nNode Num:%d\n", gRedBlakcClass.GetNodeNum());
            }
            if (PtInRect(&deleteRect, mousePoint))
            {
                gRedBlakcClass.DeleteNode(nodeNum);
                textNodeInput[0] = NULL;
                wprintf(L"Inorder:");
                gRedBlakcClass.InorderPrint(gRedBlakcClass.GetRootNode());
                wprintf(L"\nNode Num:%d\n", gRedBlakcClass.GetNodeNum());
            }
            if (PtInRect(&clearRect, mousePoint))
            {
                gRedBlakcClass.AllDeleteNode(gRedBlakcClass.GetRootNode());
                textNodeInput[0] = NULL;
                wprintf(L"\nNode Num:%d\n", gRedBlakcClass.GetNodeNum());
            }
            if (PtInRect(&randomInsertRect, mousePoint))
            {
                if(gRedBlakcClass.GetNodeNum() > 0)
                    gRedBlakcClass.AllDeleteNode(gRedBlakcClass.GetRootNode());

                textNodeInput[0] = NULL;
                wprintf(L"\nNode Num:%d\n", gRedBlakcClass.GetNodeNum());
                gTestSystem.RandomInsert();
                wprintf(L"Inorder:");
                gRedBlakcClass.InorderPrint(gRedBlakcClass.GetRootNode());
                wprintf(L"\nNode Num:%d\n", gRedBlakcClass.GetNodeNum());
            }

            selPos = mousePoint;
            isClip = true;
            InvalidateRect(hWnd, NULL, false);
        }
        break;
    case WM_LBUTTONUP:
        {
            isClip = false;
        }
        break;
    case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            //	DoubleBuffering
            layDC = CreateCompatibleDC(hdc);
            lay = CreateCompatibleBitmap(hdc, WINDOW_WIDTH, WINDOW_HEIGHT);
            SelectObject(layDC, lay);
            //	Begin work
            SetBkMode(layDC, TRANSPARENT);
            SetTextColor(layDC, RGB(255, 255, 255));
            FillRect(layDC, &windowRect, (HBRUSH)GetStockObject(WHITE_BRUSH));

            // 레드블랙 트리 노드 그리기
            if (gRedBlakcClass.GetNodeNum() > 0)
            {
                DrawRedBlackTree(layDC, rootPos, standardPos, depth, gRedBlakcClass.GetRootNode(), gRedBlakcClass.GetNodeNum(), { 0, 0 });
            }

            // 입력창 그리기
            FrameRect(layDC, &inputRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
            SetTextColor(layDC, RGB(0, 0, 0));
            wsprintf(textInput, L"Input : %s", textNodeInput);
            GetTextExtentPoint32(layDC, textInput, lstrlen(textInput), &size);
            tempRect = RectPointPlus(inputRect, { 5, 0 });
            DrawText(layDC, textInput, -1, &tempRect, DT_VCENTER | DT_SINGLELINE);

            SetTextColor(layDC, RGB(0, 0, 0));
            DrawLineBox(layDC, insertRect, RGB(125, 125, 125), RGB(125, 125, 125), 2, false);
            wsprintf(textInput, L"insert");
            DrawText(layDC, textInput, -1, &insertRect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

            SetTextColor(layDC, RGB(0, 0, 0));
            DrawLineBox(layDC, deleteRect, RGB(125, 125, 125), RGB(125, 125, 125), 2, false);
            wsprintf(textInput, L"delete");
            DrawText(layDC, textInput, -1, &deleteRect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

            SetTextColor(layDC, RGB(0, 0, 0));
            DrawLineBox(layDC, clearRect, RGB(125, 125, 125), RGB(125, 125, 125), 2, false);
            wsprintf(textInput, L"clear");
            DrawText(layDC, textInput, -1, &clearRect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

            SetTextColor(layDC, RGB(0, 0, 0));
            DrawLineBox(layDC, randomInsertRect, RGB(125, 125, 125), RGB(125, 125, 125), 2, false);
            wsprintf(textInput, L"random insert");
            DrawText(layDC, textInput, -1, &randomInsertRect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

            BitBlt(hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, layDC, 0, 0, SRCCOPY);
            EndPaint(hWnd, &ps);
            DeleteDC(layDC);
            DeleteObject(lay);
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
