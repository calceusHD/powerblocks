#ifndef FONT_H
#define FONT_H

#include <vector>
#include <thread>
#include <atomic>
#include <iostream>
#include <fstream>


#include "windows.h"

#include "GL/glew.h"

#include "GlyphData.h"
#include "FreeType.h"
#include "DistMap.h"
#include "Hash.h"


class Font
{
    struct ThreadData {
        Font *me;
        std::atomic<unsigned int> cnt;
        const char *name;
        unsigned int size;
        unsigned int textureSize;
        float *dataOut;
    };
    public:

        std::vector<float> _data;
        std::vector<GlyphData> _glyphs;
        unsigned int _size;
        unsigned int _textureNumber;
        const char *_name;


        Font(unsigned int size, const char *name, unsigned int textureSize, unsigned int glTextureNumber);
        virtual ~Font();

        void fillGlyph(char id, FT_GlyphSlot data);
        FT_GlyphSlot createGlyph(unsigned int id, FreeType *ft);
        void createTexFromGlyph(unsigned int textureSize, FT_GlyphSlot gl, float *totalMap, unsigned int id);
        void createGlyphsThreaded(FreeType *ft, unsigned int textureSize, float *totalMap);
        static DWORD WINAPI threadFunc( LPVOID lpParam );

    protected:
    private:
};

#endif // FONT_H
