/*
 * Window.h
 *
 *  Created on: Mar 15, 2013
 *      Author: ICH
 */



#ifndef WINDOW_H_
#define WINDOW_H_

#include <iostream>
#include <string>
#include <windows.h>
#include <windowsx.h>

#include "iwindow.h"

class Window {
public:
	Window(std::string name, HINSTANCE hInstance, int width, int height, IWindow *iWindow);
	virtual ~Window();

	bool show(int nCmdShow);

	static LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void setSizeCallback(void *cl, void (*func)(int w, int h));

	HWND hWnd;
};

#endif /* WINDOW_H_ */
