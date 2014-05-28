#ifndef GLYPHDATA_H
#define GLYPHDATA_H

#include <glm/glm.hpp>

class GlyphData
{
    public:
        glm::vec2 advance;
        glm::vec2 size;
        glm::vec2 offset;
        GlyphData();
        void set(glm::vec2 advance, glm::vec2 size, glm::vec2 offset);
        virtual ~GlyphData();
    protected:
    private:
};

#endif // GLYPHDATA_H
