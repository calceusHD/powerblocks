#ifndef FREETYPE_H
#define FREETYPE_H
extern "C" {
#include "ft2build.h"
#include FT_FREETYPE_H
}
class FreeType
{
    public:
        unsigned int _size;
        FT_Library _library;
        FT_Face _face;
        const char *_fontName;

        FreeType(unsigned int size, const char *fontName);
        virtual ~FreeType();
        FT_GlyphSlot createChar(char code);
    protected:
    private:
};

#endif // FREETYPE_H
