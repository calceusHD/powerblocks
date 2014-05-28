#include "GlyphData.h"

GlyphData::GlyphData()
{
}

void GlyphData::set(glm::vec2 advance, glm::vec2 size, glm::vec2 offset)
{
    this->advance = advance;
    this->size = size;
    this->offset = offset;
}

GlyphData::~GlyphData()
{
    //dtor
}
