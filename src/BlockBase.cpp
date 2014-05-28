#include "BlockBase.h"

BlockBase::BlockBase()
{
    //ctor
}

BlockBase::~BlockBase()
{
    //dtor
}

void BlockBase::render(glm::ivec3 pos, VboBuilder *vbo, glm::vec3 test)
{
    vbo->addVertex(glm::vec3(pos), test);
}
