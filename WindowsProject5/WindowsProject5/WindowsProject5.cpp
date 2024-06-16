// WindowsProject5.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "WindowsProject5.h"
#include <time.h>
#include "iostream"

//#define DEBUG_GAME

enum Modes {
    START,// старт
    GAME, // игра
    VICTORY, // победа
    LOSS,// проигрыш    
    FINAL // Завершение 
};
// Глобальная переменная, хранящая номер режима
enum Modes mode = START;
// номер шага.Отсчитывается для задержки при отрисовке окна победы и поражения 
int step = 0;
// SonicBlue
typedef struct SonicBlue {

    int X;
    int Y;

    int Helth;

} SONICBLUE;

SONICBLUE SonicBlue = {100, 200, 3};

typedef struct GameObject {

    int X;
    int Y;
    int Visible;
} GAMEOBJECT;
GAMEOBJECT Monetka = { 200, 400, 1 };
GAMEOBJECT SonicBlack = { 150, 200, 1 };
GAMEOBJECT Vrag = { 300, 230, 1 };

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT5));

    MSG msg;

    // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT5);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void DrawSonicBlue(HDC hdc, int cx, int cy) {
    const int dx = 100, dy = 250;
    HPEN hPenSonic1 = CreatePen(PS_SOLID, 7, RGB(0, 0, 205));
    HBRUSH hBrushSonic2 = CreateSolidBrush(RGB(150, 255, 255));
    HBRUSH hBrushSonic1 = CreateSolidBrush(RGB(0, 0, 255));


    SelectObject(hdc, hBrushSonic1);
    SelectObject(hdc, hBrushSonic1);
    Ellipse(hdc, 75 - dx + cx, 225 - dy + cy, 125 - dx + cx, 275 - dy + cy);
    DeleteObject(hBrushSonic1);
    DeleteObject(hPenSonic1);

    SelectObject(hdc, hBrushSonic2);
    Ellipse(hdc, 80 - dx + cx, 230 - dy + cy, 100 - dx + cx, 235 - dy + cy);
    DeleteObject(hBrushSonic2);
#ifdef DEBUG_GAME
    // Зона захвата
    HPEN hPenZone = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(hdc, hPenZone);
    SelectObject(hdc, GetStockObject(NULL_BRUSH));
    Rectangle(hdc, cx - 25, cy - 25, cx + 25, cy + 25);

    MoveToEx(hdc, cx - 40, cy, NULL);
    LineTo(hdc, cx + 40, cy);
    MoveToEx(hdc, cx, cy - 40, NULL);
    LineTo(hdc, cx, cy + 40);
    DeleteObject(hPenZone);
#endif
}

void DrawSonicBlack(HDC hdc, int cx, int cy) {
    const int dx = 180, dy = 250;
    HPEN hPenBlackSonic1 = CreatePen(PS_SOLID, 7, RGB(2, 2, 2));
    HBRUSH hBrushBlackSonic1 = CreateSolidBrush(RGB(22, 22, 22));
    HPEN hPenBlackSonic2 = CreatePen(PS_SOLID, 7, RGB(255, 255, 255));
    HBRUSH  hBrushBlackSonic2 = CreateSolidBrush(RGB(150, 255, 255));
    SelectObject(hdc, hPenBlackSonic1);
    SelectObject(hdc, hBrushBlackSonic1);

    Ellipse(hdc, 155 - dx + cx, 225 - dy + cy, 205 - dx + cx, 275 - dy + cy);
    DeleteObject(hPenBlackSonic1);
    DeleteObject(hBrushBlackSonic1);

    SelectObject(hdc, hPenBlackSonic2);
    SelectObject(hdc, hBrushBlackSonic2);
    Ellipse(hdc, 165 - dx + cx, 230 - dy + cy, 175 - dx + cx, 235 - dy + cy);
    DeleteObject(hPenBlackSonic2);
    DeleteObject(hBrushBlackSonic2);
#ifdef DEBUG_GAME
    // Зона захвата
    HPEN hPenZone = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(hdc, hPenZone);
    SelectObject(hdc, GetStockObject(NULL_BRUSH));
    Rectangle(hdc, cx - 25, cy - 25, cx + 25, cy + 25);

    MoveToEx(hdc, cx - 40, cy, NULL);
    LineTo(hdc, cx + 40, cy);
    MoveToEx(hdc, cx, cy - 40, NULL);
    LineTo(hdc, cx, cy + 40);
    DeleteObject(hPenZone);
#endif
}

void DrawMonetka(HDC hdc, int cx, int cy) {
    const int dx = 240, dy = 240;
    HPEN hPenMonetka1 = CreatePen(PS_SOLID, 7, RGB(255, 215, 0));
    HBRUSH hBrushMonetka1 = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hPenMonetka1);
    SelectObject(hdc, hBrushMonetka1);
    Ellipse(hdc, 225 - dx + cx, 225 - dy + cy, 255 - dx + cx, 255 - dy + cy);
    DeleteObject(hPenMonetka1);
    DeleteObject(hBrushMonetka1);
#ifdef DEBUG_GAME
    // Зона захвата
    HPEN hPenZone = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(hdc, hPenZone);
    SelectObject(hdc, GetStockObject(NULL_BRUSH));
    Rectangle(hdc, cx - 20, cy - 20, cx + 20, cy + 20);

    MoveToEx(hdc, cx - 40, cy, NULL);
    LineTo(hdc, cx + 40, cy);
    MoveToEx(hdc, cx, cy - 40, NULL);
    LineTo(hdc, cx, cy + 40);
    DeleteObject(hPenZone);
#endif
}

void DrawVrag(HDC hdc, int cx, int cy) {
    const int dx = 275, dy = 270;
    HPEN hPenVrag1 = CreatePen(PS_SOLID, 7, RGB(165, 0, 0));
    HBRUSH hBrushVrag1 = CreateSolidBrush(RGB(245, 164, 96));

    HPEN hPenVrag2 = CreatePen(PS_SOLID, 7, RGB(165, 0, 0));
    HBRUSH hBrushVrag2 = CreateSolidBrush(RGB(245, 164, 96));
    SelectObject(hdc, hPenVrag1);
    SelectObject(hdc, hBrushVrag1);
    Ellipse(hdc, 255 - dx + cx, 255 - dy + cy, 295 - dx + cx, 305 - dy + cy);
    DeleteObject(hPenVrag1);
    DeleteObject(hBrushVrag1);

    SelectObject(hdc, hPenVrag2);
    SelectObject(hdc, hBrushVrag2);
    Ellipse(hdc, 265 - dx + cx, 235 - dy + cy, 285 - dx + cx, 255 - dy + cy);
    DeleteObject(hBrushVrag2);
    DeleteObject(hPenVrag2);
#ifdef DEBUG_GAME
    // Зона захвата
    HPEN hPenZone = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(hdc, hPenZone);
    SelectObject(hdc, GetStockObject(NULL_BRUSH));
    Rectangle(hdc, cx - 40, cy - 40, cx + 40, cy + 40);

    MoveToEx(hdc, cx - 50, cy, NULL);
    LineTo(hdc, cx + 50, cy);
    MoveToEx(hdc, cx, cy - 50, NULL);
    LineTo(hdc, cx, cy + 50);
    DeleteObject(hPenZone);
#endif
}

void DrawGame(HDC hdc) {
    if (SonicBlue.Helth) {
        DrawSonicBlue(hdc, SonicBlue.X, SonicBlue.Y);
    }
    if (Monetka.Visible) {
        DrawMonetka(hdc, Monetka.X, Monetka.Y);
    }
    if (SonicBlack.Visible) {
        DrawSonicBlack(hdc, SonicBlack.X, SonicBlack.Y);
    }
    if (Vrag.Visible) {
        DrawVrag(hdc, Vrag.X, Vrag.Y);
    }

}

void TryToEatMonetka() {
     /*(int i = 0;i < NUM_CANDYS;i++) {*/
        if (Monetka.Visible) {

            if (SonicBlue.X - 20 < Monetka.X
                && SonicBlue.X + 20 > Monetka.X
                && SonicBlue.Y - 20 < Monetka.Y
                && SonicBlue.Y + 20 > Monetka.Y) {
                Monetka.Visible = 0;
                SonicBlue.Helth += 5;
            }
        }
    }
//}

//void DrawSonicBlue(HDC hdc, int cx, int cy) {
//    const int dx = 121, dy = 122;
//    HPEN hPenSonic = CreatePen(PS_SOLID, 7, RGB(0, 0, 205));
//    
//
//    HBRUSH hBrushSonic1 = CreateSolidBrush(RGB(0, 0, 255));
//    SelectObject(hdc, hBrushSonic1);
//
//    Ellipse(hdc, 75 - dx + cx, 225 - dy + cy, 125 - dx + cx, 275 - dy + cy);
//    DeleteObject(hBrushSonic1);
//    DeleteObject(hPenSonic);
//
//    HBRUSH hBrushSonic2 = CreateSolidBrush(RGB(150, 255, 255));
//    SelectObject(hdc, hBrushSonic2);
//
//    Ellipse(hdc, 80 - dx + cx, 230 - dy + cy, 100 - dx + cx, 235 - dy + cy);
//    DeleteObject(hBrushSonic1);
//    DeleteObject(hBrushSonic2);
//}
//
//void DrawSonicBlack(HDC hdc, int cx, int cy) {
//    const int dx = 121, dy = 122;
//    HPEN hPenBlackSonic1 = CreatePen(PS_SOLID, 7, RGB(2, 2, 2));
//    SelectObject(hdc, hPenBlackSonic1);
//
//    HBRUSH hBrushBlackSonic1 = CreateSolidBrush(RGB(22, 22, 22));
//    SelectObject(hdc, hBrushBlackSonic1);
//
//    Ellipse(hdc, 155 - dx + cx, 225 - dy + cy, 205 - dx + cx, 275 - dy + cy);
//
//    HPEN hPen = CreatePen(PS_SOLID, 7, RGB(255, 255, 255));
//    SelectObject(hdc, hPen);
//
//    HBRUSH hBrush;hBrush = CreateSolidBrush(RGB(150, 255, 255));
//    SelectObject(hdc, hBrush);
//
//    Ellipse(hdc, 165 - dx + cx, 230 - dy + cy, 175 - dx + cx, 235 - dy + cy);
//}
//
//void DrawMonetka(HDC hdc, int cx, int cy) {
//    const int dx = 121, dy = 122;
//    HPEN hPen = CreatePen(PS_SOLID, 7, RGB(255, 215, 0));
//    SelectObject(hdc, hPen);
//
//    HBRUSH hBrush;hBrush = CreateSolidBrush(RGB(255, 255, 255));
//    SelectObject(hdc, hBrush);
//
//    Ellipse(hdc, 225 - dx + cx, 225 - dy + cy, 255 - dx + cx, 255 - dy + cy);
//}
//
//void DrawVrag(HDC hdc, int cx, int cy) {
//    const int dx = 121, dy = 122;
//    HPEN hPenVrag1 = CreatePen(PS_SOLID, 7, RGB(165, 0, 0));
//    SelectObject(hdc, hPenVrag1);
//
//    HBRUSH hBrushVrag1 = CreateSolidBrush(RGB(245, 164, 96));
//    SelectObject(hdc, hBrushVrag1);
//
//    Ellipse(hdc, 255 - dx + cx, 255 - dy + cy, 295 - dx + cx, 305 - dy + cy);
//
//
//    HPEN hPenVrag2 = CreatePen(PS_SOLID, 7, RGB(165, 0, 0));
//    SelectObject(hdc, hPenVrag2);
//
//    HBRUSH hBrushVrag2 = CreateSolidBrush(RGB(245, 164, 96));
//    SelectObject(hdc, hBrushVrag2);
//
//    Ellipse(hdc, 265 - dx + cx, 235 - dy + cy, 285 - dx + cx, 255 - dy + cy);
//    DeleteObject(hBrushVrag2);
//}


void DrawStart(HDC hdc) {
    {

        int x = 0;
        int y = 0;
        int i = 0;
        do {
            DrawSonicBlack(hdc, x, y);
            x = x + 20;
            y = y + 20;
            i++;
        } while (i < 20);
    }

    {

        int x = 130;
        int y = 0;
        int i = 0;
        do {
            DrawSonicBlue(hdc, x, y);
            x = x + 20;
            y = y - 20;
            i++;
        } while (i < 20);
    } {

        int x = 250;
        int y = 0;
        int i = 0;
        do {
            DrawMonetka(hdc, x, y);
            x = x + 20;
            y = y + 20;
            i++;
        } while (i < 20);
    }
    {

        int x = 350;
        int y = 0;
        int i = 0;
        do {
            DrawVrag(hdc, x, y);
            x = x + 20;
            y = y - 20;
            i++;
        } while (i < 20);
    }
}

void DrawVictory(HDC hdc) {

    int y = 50;
    do {
        int x = 50;
        do {
            DrawSonicBlue(hdc, x, y);
            x += 50;
        } while (x <= 500);
        y += 50;
    } while (y <= 300);
}

void DrawLoss(HDC hdc) {

    int y = 50;
    do {
        int x = 50;
        do {
            DrawSonicBlack(hdc, x, y);
            x += 50;
        } while (x <= 500);
        y += 50;
    } while (y <= 300);
}

void DrawFinal(HDC hdc)
{
    int x, y;

    y = 0;
    do {
        x = 50;
        do {
            DrawSonicBlue(hdc, x, y);
            x += 60;
        } while (x <= 230);
        y += 60;
    } while (y <= 230);

    y = 240;
    while (y <= 440) {
        x = -100;
        while (x <= 100) {
            DrawMonetka(hdc, x, y);
            x += 40;
        }
        y += 40;
    }
    for (y = 870; y <= 400; y += 60) {
        for (x = 220; x <= 380; x += 20) {
            DrawVrag(hdc, x, y);

        }
    }



    // эмуляция вложенных do while при помощи GOT(
    y = 0;
do1:
    x = 110;
do2:
    DrawVrag(hdc, x, y);
    x += 70;
    if (x <= 300) goto do2;
    y += 90;
    if (y <= 360) goto do1;
    // эмуляция вложенных while при помощи GOTO
    y = 0;
while1:
    if (!(y <= 450)) goto after1;
    x = 400;
while2:
    if (!(x <= 600)) goto after2;
    DrawSonicBlack(hdc, x, y);
    x += 70;
    goto while2;
after2:
    y += 100;
    goto while1;
after1:
    // Вывод имени автора игры
    HFONT hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0,
        DEFAULT_CHARSET, 0, 0, 0, 8, L"Courier New");
    SelectObject(hdc, hFont);
    SetTextColor(hdc, RGB(128, 0, 128));
    TCHAR strT[180] = L"Автор игры: Цой Максим Алексеевич ИСдо-17";
    TextOut(hdc, 0, 0, (LPCWSTR)strT, _tcslen(strT));
    DeleteObject(hFont);
}
void RandomMoveSonicBlack() {

    if (SonicBlack.Visible) {
        int dx = rand() % 21 - 10;
        int dy = rand() % 21 - 10;

        SonicBlack.X += dx;
        SonicBlack.Y += dy;
    }
}

void RandomMoveVrag() {

    if (Vrag.Visible) {
        int dx = rand() % 21 - 10;
        int dy = rand() % 21 - 10;

        Vrag.X += dx;
        Vrag.Y += dy;
    }
}

void ContactSonicBlueAndSonicBlack() {
    if (SonicBlack.Visible) {
        if (SonicBlue.X - 20 < SonicBlack.X
            && SonicBlue.X + 20 > SonicBlack.X
            && SonicBlue.X - 20 < SonicBlack.Y
            && SonicBlue.X + 20 > SonicBlack.Y) {
            SonicBlue.Helth--;  
        }
    }
}

void ContactSonicBlueAndVrag() {
    if (Vrag.Visible) {
        if (SonicBlue.X - 20 < Vrag.X
            && SonicBlue.X + 20 > Vrag.X
            && SonicBlue.X - 20 < Vrag.Y
            && SonicBlue.X + 20 > Vrag.Y) {
            SonicBlue.Helth--;
        }
    }
}
//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
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


    case WM_KEYDOWN:
        if (mode == START) {
            mode = GAME;
        }
        else if (mode == GAME) {
            switch (wParam)
            {
                //...
            case VK_UP:
                SonicBlue.Y -= 10;
                break;
            case VK_DOWN:
                SonicBlue.Y += 10;
                break;
            case VK_LEFT:
                SonicBlue.X -= 10;
                break;
            case VK_RIGHT:
                SonicBlue.X += 10;
                break;
            }
            ContactSonicBlueAndSonicBlack();
            if (SonicBlue.Helth == 0) {
                mode = LOSS;
            }
            ContactSonicBlueAndVrag();
            if (SonicBlue.Helth == 0) {
                mode = LOSS;
            }
            TryToEatMonetka();
            if (Monetka.Visible == 0) {
                mode = VICTORY;
            }
        }
        else if (mode == VICTORY || mode == LOSS) {
            step++;
            if (step > 10)
                mode = FINAL;
        }
        InvalidateRect(hWnd, NULL, TRUE);
        break;
        
    case WM_CREATE:
        srand(time(NULL));
        SetTimer(hWnd, 1, 1000, NULL);
            break;
            

        case WM_TIMER:
        if (mode == GAME) {
                    RandomMoveSonicBlack();
                    ContactSonicBlueAndSonicBlack();
                    if (SonicBlue.Helth == 0) {
                        mode = LOSS;
                    }
                    RandomMoveVrag();
                    ContactSonicBlueAndVrag();
                    if (SonicBlue.Helth == 0) {
                        mode = LOSS;
                    }
                if (Monetka.Visible == 0) {
                    mode = VICTORY;
                }

            }
            
            else if (mode == VICTORY || mode == LOSS) {
                step++;
                if (step > 10)
                    mode = FINAL;
            }
            InvalidateRect(hWnd, NULL, TRUE);
            break;
            

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            
            if (mode == START)
                DrawStart(hdc);
            if (mode == GAME)
                DrawGame(hdc);
            if (mode == VICTORY)
                DrawVictory(hdc);
            if (mode == LOSS)
                DrawLoss(hdc);
            if (mode == FINAL)
                DrawFinal(hdc);
            
          /*  DrawFinal(hdc);
  
            DrawVictory(hdc);
            DrawLoss(hdc);
            
            DrawStart(hdc);
            DrawMode0(hdc);
             
            DrawSonicBlue(hdc, 235, 245);
            DrawSonicBlack(hdc, 285, 295);
            DrawMonetka(hdc, 320, 330);
            DrawVrag(hdc, 350, 360);*/
            
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

// Обработчик сообщений для окна "О программе".
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
