#include "Renderer.h"

Renderer::Renderer()
{
    _program.attach(new Shader("data/shaders/blockVertex.c", true, GL_VERTEX_SHADER));
    _program.attach(new Shader("data/shaders/blockFragment.c", true, GL_FRAGMENT_SHADER));
    _program.build();


    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(2, _vbo);


    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);


    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);


   /* glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);



    glVertexAttribIPointer(1, 1, GL_BYTE, 0, 0);

    glEnableVertexAttribArray(1);*/
}

Renderer::~Renderer()
{
    //dtor
}

void Renderer::setScreenSize(glm::ivec2 size)
{
    _screenSize = size;
}

void Renderer::renderVbo(VboBuilder *vbo, glm::vec2 look, glm::vec3 pos)
{

    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    _program.use();
    glm::mat4 mvpmat(1.0f);

    mvpmat = glm::perspective(50.0f, (float)_screenSize.x / (float)_screenSize.y , 0.1f, 300.0f);
    mvpmat = glm::rotate(mvpmat, look.y, glm::vec3(1.0f, 0.0f, 0.0f));
    mvpmat = glm::rotate(mvpmat, -look.x, glm::vec3(0.0f, 0.0f, 1.0f));

    mvpmat = glm::translate(mvpmat, pos);

    glBindVertexArray(_vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, vbo->_vertices.size() * sizeof(glm::vec3), vbo->_vertices.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, vbo->_colors.size() * sizeof(glm::vec3), vbo->_colors.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glUniformMatrix4fv(_program.getUniformLocation("mvpmat"), 1,  GL_FALSE, glm::value_ptr(mvpmat));
    glDrawArrays(GL_POINTS, 0, vbo->_vertices.size());
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    if (glGetError())
        std::cout << "!!11";
}
