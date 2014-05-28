#include "FreeType.h"
#include "GL/glew.h"

FreeType::FreeType(unsigned int size, const char *fontName)
{
    _fontName = fontName;
    _size = size;
    FT_Init_FreeType(&_library);
    FT_New_Face(_library, _fontName, 0, &_face);
    FT_Set_Pixel_Sizes(_face, _size, _size);
}

FT_GlyphSlot FreeType::createChar(char code)
{
    FT_Load_Char(_face, code, FT_LOAD_RENDER);
    return _face->glyph;
}


FreeType::~FreeType()
{
    //dtor
}
