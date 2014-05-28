#ifndef BLOCKBASE_H
#define BLOCKBASE_H

#include <glm/glm.hpp>

#include "vbobuilder.h"

class BlockBase
{
    public:
        BlockBase();
        virtual ~BlockBase();

        void render(glm::ivec3 pos, VboBuilder *vbo, glm::vec3 test);
    protected:
    private:
};

#endif // BLOCKBASE_H
