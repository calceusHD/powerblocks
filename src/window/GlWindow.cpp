/*
 * GlWindow.cpp
 *
 *  Created on: Mar 15, 2013
 *      Author: ICH
 */

#include "GlWindow.h"

GlWindow::GlWindow(Window *window, int major, int minor) {
	this->window = window;
	hDC = GetDC(this->window->hWnd);

	PIXELFORMATDESCRIPTOR pfd;

	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int iFormat = ChoosePixelFormat(hDC, &pfd);

	SetPixelFormat(this->hDC, iFormat, &pfd);

	HGLRC tmpc = wglCreateContext(this->hDC);

	wglMakeCurrent(this->hDC, tmpc);

	glewInit();

	int attribList[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, major,
			WGL_CONTEXT_MINOR_VERSION_ARB, minor,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
	};
	hRC = wglCreateContextAttribsARB(this->hDC, 0, attribList);

	wglMakeCurrent(this->hDC, this->hRC);

	wglDeleteContext(tmpc);







}

GlWindow::~GlWindow() {
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(this->hRC);
	ReleaseDC(this->window->hWnd, this->hDC);
}

void GlWindow::swapBuffers()
{
    SwapBuffers(this->hDC);
}
