#ifndef RENDERER_H
#define RENDERER_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gl/program.h"
#include "vbobuilder.h"

class Renderer
{
    public:
        Program _program;
        unsigned int _vbo[2];
        unsigned int _vao;
        glm::ivec2 _screenSize;

        Renderer();
        virtual ~Renderer();
        void renderVbo(VboBuilder *vbo, glm::vec2 look, glm::vec3 pos);
        void setScreenSize(glm::ivec2 size);
    protected:
    private:
};

#endif // RENDERER_H
