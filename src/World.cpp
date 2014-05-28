#include "World.h"

World::World() :
    _chunks(LOAD_DIST * LOAD_DIST * WORLD_HEIGHT)
{
    for (int x = 0; x < LOAD_DIST; x++)
        for (int y = 0; y < LOAD_DIST; y++)
            for (int z = 0; z < WORLD_HEIGHT; z++)
                _chunks.at(z + y * WORLD_HEIGHT + x * WORLD_HEIGHT * LOAD_DIST) = new Chunk(glm::ivec3(x, y, z));
}

World::~World()
{
    //dtor
}

void World::genVbos()
{
    for ( Chunk *ch : _chunks )
        ch->genVbo();
}

void World::render()
{
    for (Chunk *&ch : _chunks)
        ch->render(ren);
}
