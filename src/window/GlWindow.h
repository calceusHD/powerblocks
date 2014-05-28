/*
 * GlWindow.h
 *
 *  Created on: Mar 15, 2013
 *      Author: ICH
 */

#ifndef GLWINDOW_H_
#define GLWINDOW_H_

#include "GL/glew.h"
#include "GL/wglew.h"

#include "Window.h"



class GlWindow {
public:
	GlWindow(Window *window, int major, int minor);
	virtual ~GlWindow();

	void swapBuffers();
	static void sizeCallback(int w, int h);

	HDC hDC;
	HGLRC hRC;
	Window *window;
};

#endif /* GLWINDOW_H_ */
