/*
 * Print.h
 *
 *  Created on: Mar 17, 2013
 *      Author: ICH
 */

#ifndef PRINT_H_
#define PRINT_H_

#include <cstdarg>
#include <cstring>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gl/program.h"
#include "font.h"

class Print {
public:
	Program _program;
    Font *_font;
    unsigned int _vbo[2];
    unsigned int _vao;
    glm::mat4 _mat;
    glm::ivec2 _screen;
    int _ufStepSize, _ufTex, _ufCharMat;


    Print();
	Print(Font *font, const char *vertex, const char *frag);
	virtual ~Print();

	void printfAt(float x, float y, float sx, float sy, const char *fmt, ...);
	void set(Font *font, const char *vertex, const char *frag);
	//void
	void setScreenSize(glm::ivec2 size);
};

#endif /* PRINT_H_ */
