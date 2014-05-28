/*
 * Print.cpp
 *
 *  Created on: Mar 17, 2013
 *      Author: ICH
 */

#include "Print.h"

Print::Print() :
	_font(nullptr)
{

}

Print::Print(Font *font, const char *vertex, const char *frag)
{
    set(font, vertex, frag);
}

void Print::set(Font *font, const char *vertex, const char *frag)
{

    _font = font;

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(2, _vbo);

    //_program = new Program();

	_program.attach(new Shader(vertex, true, GL_VERTEX_SHADER));
	_program.attach(new Shader(frag, true, GL_FRAGMENT_SHADER));

	_program.build();
	_program.use();

    _ufStepSize = _program.getUniformLocation("stepSize");

    _ufTex = _program.getUniformLocation("tex");

    _ufCharMat = _program.getUniformLocation("charMat");


    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);


    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);



    glVertexAttribIPointer(1, 1, GL_BYTE, 0, 0);

    glEnableVertexAttribArray(1);
}

Print::~Print() {
	// TODO Auto-generated destructor stub
}

//void Print::at(Vec2<float> pos, )


void Print::printfAt(float x, float y, float sx, float sy, const char *fmt, ...)
{
	char *text = new char[256];

	va_list ap;
	if (fmt == NULL)
		return;
	va_start(ap, fmt);
	vsprintf(text, fmt, ap);
	va_end(ap);

	unsigned int k = strlen(text);

	uint8_t *data = new uint8_t[k * 6];

	struct point {
        float x;
        float y;
        float s;
        float t;
    };


	point *points = new point[k * 6];

	glm::vec2 adv(0.0f, 0.0f);


    for (unsigned int i = 0; i < k; i++)
    {

        char key = text[i];
        if (key == '\n')
        {
            adv = /*adv * glm::vec2(0, 1) +*/ glm::vec2(0, -1);
        }
        else
        {

            data[i * 6] =
                data[i * 6 + 1] =
                data[i * 6 + 2] =
                data[i * 6 + 3] =
                data[i * 6 + 4] =
                data[i * 6 + 5] = key;

            glm::vec2 off = _font->_glyphs[key].offset / (float)_font->_size + adv;


            points[i * 6 + 0] = (point){off.x, off.y, 0.0f, 1.0f};
            points[i * 6 + 1] = (point){off.x, off.y + 1, 0.0f, 0.0f};
            points[i * 6 + 2] = (point){off.x + 1, off.y + 1, 1.0f, 0.0f};

            points[i * 6 + 3] = (point){off.x, off.y, 0.0f, 1.0f};
            points[i * 6 + 4] = (point){off.x + 1, off.y + 1, 1.0f, 0.0f};
            points[i * 6 + 5] = (point){off.x + 1, off.y, 1.0f, 1.0f};
            //glm::vec2 test = _font->_glyphs[key].advance;
            adv += _font->_glyphs[key].advance / (float)_font->_size;

        }
    }

    _program.use();

    glBindVertexArray(_vao);


    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, k * 6 * sizeof(point), points, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, k * 6, data, GL_DYNAMIC_DRAW);
    glVertexAttribIPointer(1, 1, GL_UNSIGNED_BYTE, 0, 0);


    glm::mat4 tmpmat(1.0f);// = _mat;

    tmpmat = glm::scale(tmpmat, glm::vec3(sx, sy, 1.0f));

    tmpmat = glm::translate(tmpmat, glm::vec3(x, y, 0.0f));

    tmpmat *= _mat;

    glUniform1f(_ufStepSize, .004 / sx );

    glUniform1i(_ufTex, _font->_textureNumber);

    glUniformMatrix4fv(_ufCharMat, 1,  GL_FALSE, glm::value_ptr(tmpmat));
    glDrawArrays(GL_TRIANGLES, 0, k * 6);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    delete points;
    delete data;
    delete text;

}

void Print::setScreenSize(glm::ivec2 size)
{
    float ratio = (float)size.x / (float)size.y;
    _mat = glm::mat4(1.0f);
    _mat = glm::ortho(-1.0f, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
}
