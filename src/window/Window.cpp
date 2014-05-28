/*
 * Window.cpp
 *
 *  Created on: Mar 15, 2013
 *      Author: ICH
 */

#include "Window.h"



Window::Window(std::string name, HINSTANCE hInstance, int width, int height, IWindow *iWindow) {
	WNDCLASSEX wcex;


	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = this->wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = name.c_str();
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    ATOM rca;

    rca = RegisterClassEx(&wcex);

	if (!rca)
		return;

	RECT win;

	win.bottom = height;
	win.left = 0;
	win.top = 0;
	win.right = width;

	AdjustWindowRectEx(&win, WS_OVERLAPPEDWINDOW, FALSE, 0);

	this->hWnd = CreateWindowEx(
			0,
			(LPCSTR)rca,
			name.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			win.right - win.left,
			win.bottom - win.top,
			NULL,
			NULL,
			hInstance,
			iWindow);

    if (this->hWnd == NULL)
        printf("jdsfkhsdk");
}

Window::~Window() {
	DestroyWindow(this->hWnd);
}

bool Window::show(int nCmdShow)
{
	ShowWindow(this->hWnd, nCmdShow);

	return true;
}

LRESULT CALLBACK Window::wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    IWindow *wnd;
    if (uMsg == WM_NCCREATE)
    {
        wnd = (IWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)wnd);

        RAWINPUTDEVICE Rid;
        Rid.usUsagePage = 0x01;
        Rid.usUsage = 0x02;
        Rid.dwFlags = 0;//RIDEV_NOLEGACY;   // adds HID mouse and also ignores legacy mouse messages
        Rid.hwndTarget = hWnd;
        if (RegisterRawInputDevices(&Rid, 1, sizeof(Rid)) == false)
            std::cout << "register failed";
    }
    else
    {
        wnd = (IWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    }
	switch (uMsg)
    {
        case WM_SIZE:
           wnd->size(wParam, LOWORD(lParam), HIWORD(lParam));
        break;

        case WM_KEYDOWN:
            wnd->keydown(wParam);
        break;

        case WM_KEYUP:
            wnd->keyup(wParam);
        break;

        case WM_MOUSEMOVE:
            wnd->mousemove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;

        case WM_INPUT:
            {

                unsigned int dwSize;

                GetRawInputData((HRAWINPUT)lParam, RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
                char * data = new char[dwSize];

                GetRawInputData((HRAWINPUT)lParam, RID_INPUT, data, &dwSize, sizeof(RAWINPUTHEADER));

                RAWINPUT * raw = (RAWINPUT*)data;

                if ( raw->header.dwType == RIM_TYPEMOUSE)
                {
                    std::cout << "INPUT: " << raw->header.hDevice << ":" << raw->data.mouse.usFlags << std::endl;
                    wnd->rawInputMouse(raw->data.mouse.lLastX, raw->data.mouse.lLastY, raw->data.mouse.usButtonFlags, raw->data.mouse.usButtonData);
                }
                else
                    DefRawInputProc(&raw, 1, sizeof(RAWINPUTHEADER));
                delete data;
            }
        break;



        case WM_CLOSE:
            wnd->close();
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        break;

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}

