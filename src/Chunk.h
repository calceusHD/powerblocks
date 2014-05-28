#ifndef CHUNK_H
#define CHUNK_H

#define CHUNK_SIZE 16

#include <vector>
#include <cstdlib>

#include "blockbase.h"
#include "vbobuilder.h"
class Chunk
{
    public:
        VboBuilder _vboBuilder;
        std::vector<BlockBase *> _blocks;
        Chunk(glm::ivec3 pos);
        virtual ~Chunk();
        glm::ivec3 _pos;

        void render();
        void genVbo();
    protected:
    private:
};

#endif // CHUNK_H
