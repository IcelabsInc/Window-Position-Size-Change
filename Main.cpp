#include <Windows.h>

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hDC = BeginPaint(hWnd, &ps);

            HBRUSH backgroundBrush = CreateSolidBrush(RGB(0, 0, 0));

            FillRect(hDC, &ps.rcPaint, backgroundBrush);

            DeleteObject(backgroundBrush);

            EndPaint(hWnd, &ps);
            break;
        }

        case WM_LBUTTONDOWN:
        {
            SetWindowPos(hWnd, NULL, 400, 200, 800, 600, 0);
            break;
        }

        case WM_RBUTTONDOWN:
        {
            SetWindowPos(hWnd, NULL, 200, 200, 200, 200, 0);
            break;
        }

        default:
            break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int nCmdShow)
{
    LPCWSTR className = (LPCWSTR)"Simple Application";

    WNDCLASSEXW windowClass;
    windowClass.cbClsExtra = 0;
    windowClass.cbSize = sizeof(windowClass);
    windowClass.cbWndExtra = 0;
    windowClass.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    windowClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
    windowClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    windowClass.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
    windowClass.hInstance = hInstance;
    windowClass.lpfnWndProc = WndProc;
    windowClass.lpszClassName = className;
    windowClass.lpszMenuName = 0;
    windowClass.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassExW(&windowClass))
    {
        MessageBoxA(NULL, (LPCSTR)"Failed to register Class. Please try again.", (LPCSTR)"Registeration Error", MB_OK);
        exit(-1);
    }

    HWND hWnd = CreateWindowExW(WS_EX_APPWINDOW, className, (LPCWSTR)"Simple Application", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 200, 200, 200, 200, NULL, 0, hInstance, NULL);

    if (!hWnd)
    {
        MessageBoxA(NULL, (LPCSTR)"Failed to create window. Please try Again.", (LPCSTR)"Window Creation Error", MB_OK);
        exit(-1);
    }

    MSG msg;

    while (GetMessage(&msg, hWnd, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
