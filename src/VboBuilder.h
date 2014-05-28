#ifndef VBOBUILDER_H
#define VBOBUILDER_H

#include <vector>
#include <glm/glm.hpp>

class VboBuilder
{
    public:
        std::vector<glm::vec3> _vertices;
        std::vector<glm::vec3> _colors;

        VboBuilder();
        virtual ~VboBuilder();

        void addVertex(glm::vec3 pos, glm::vec3 color);
        void clear();
    protected:
    private:
};

#endif // VBOBUILDER_H
