#include "VboBuilder.h"

VboBuilder::VboBuilder()
{
    //ctor
}

VboBuilder::~VboBuilder()
{
    //dtor
}

void VboBuilder::addVertex(glm::vec3 pos, glm::vec3 color)
{
    _vertices.push_back(pos);
    _colors.push_back(color);
}

void VboBuilder::clear()
{
    _vertices.clear();
    _colors.clear();
}
