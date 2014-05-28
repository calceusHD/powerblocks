#ifndef WORLD_H
#define WORLD_H

#define LOAD_DIST 11
#define WORLD_HEIGHT 16

#include <vector>

#include "chunk.h"
#include "vbobuilder.h"

class World
{
    public:
        std::vector<Chunk *> _chunks;


        World();
        virtual ~World();

        void render(VboBuilder *vbo);
        void genVbos();
    protected:
    private:
};

#endif // WORLD_H
