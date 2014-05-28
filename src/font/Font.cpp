#include "Font.h"



void checkErr(const char *name)
{

    GLenum ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        printf(
            "ERROR: %X at %s\n",
            (ErrorCheckValue), name
        );
    }
}


Font::Font(unsigned int size, const char *name, unsigned int textureSize, unsigned int glTextureNumber) :
    _data(textureSize * textureSize * 0x100),
    _glyphs(0x100),
    _size(size),
    _textureNumber(glTextureNumber),
    _name(name)
{

    unsigned int sizeSq = textureSize * textureSize;
    float *totalMap = (float*)malloc(sizeSq * 0x100 * sizeof(float));

    FreeType ft(size, name);

    bool done = false;
    Hash h;

    h << size << textureSize << name;
    std::vector<uint32_t> hv = h.digest();

    std::fstream tex("data/textures/font", std::fstream::in | std::fstream::binary);

    if ( !tex.fail())
    {

        std::vector<uint32_t> fv(4);
        tex.read((char*)fv.data(), sizeof(uint32_t) * 4);

        if (std::equal(hv.begin(), hv.end(), fv.begin()))
        {
            tex.read((char*)totalMap, sizeSq * 0x100 * sizeof(float));
            done = true;
        }
    }

    tex.close();
    if ( !done )
    {
        createGlyphsThreaded(&ft, textureSize, totalMap);





    }
    else
    {
        for (unsigned int i = 0; i < 0x100 ;i++)
        {
            FreeType ft(size, name);
            createGlyph(i, &ft);
        }
    }

    if ( !done )
    {

        std::fstream texOut("data/textures/font", std::fstream::out | std::fstream::binary);
        texOut.write((char*)hv.data(), sizeof(uint32_t) * 4);
        texOut.write((char*)totalMap, sizeSq * 0x100 * sizeof(float));


    }


    unsigned int texture;

    glGenTextures(1, &texture );

    glActiveTexture( GL_TEXTURE0 + glTextureNumber);

    glBindTexture( GL_TEXTURE_2D_ARRAY, texture );

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage3D( GL_TEXTURE_2D_ARRAY, 0, GL_RED, textureSize, textureSize, 0x100, 0, GL_RED, GL_FLOAT, totalMap);

    //checkErr("test1");

    free(totalMap);
}

#define THREAD_COUNT 1

void Font::createGlyphsThreaded(FreeType *ft, unsigned int textureSize, float *totalMap)
{


    ThreadData td;
    td.me = this;
    td.cnt = 0;
    td.name = _name;
    td.size = _size;
    td.textureSize = textureSize;
    td.dataOut = totalMap;

    HANDLE hThreads[THREAD_COUNT];

    for (unsigned int i = 0; i < THREAD_COUNT; i++)
    {
        uint64_t aff = (1 << i * 2);
        hThreads[i] = CreateThread(NULL, 0, &Font::threadFunc, &td, 0, NULL);
        SetThreadAffinityMask(hThreads[i], aff);
    }

    WaitForMultipleObjects(THREAD_COUNT, hThreads, TRUE, INFINITE);

    for (int i = 0;i < THREAD_COUNT; i++)
    {
        CloseHandle(hThreads[i]);
    }


}

DWORD WINAPI Font::threadFunc( LPVOID lpParam )
{
    ThreadData *td = (ThreadData*)lpParam;
    unsigned int i;

    FreeType ft(td->size, td->name);

    while (( i = td->cnt.fetch_add(1) ) < 0x80)
    {
        time_t start = time(nullptr);
        FT_GlyphSlot gl = td->me->createGlyph(i, &ft);
        td->me->createTexFromGlyph(td->textureSize, gl, td->dataOut, i);
        std::cout << "Id: " << i << " Time:" << time(nullptr) - start << std::endl;
    }
    return 0;
}

FT_GlyphSlot Font::createGlyph(unsigned int id, FreeType *ft)
{
    FT_GlyphSlot gl = ft->createChar(id);
    _glyphs[id].advance = glm::vec2(gl->advance.x >> 6, gl->advance.y >> 6);
    _glyphs[id].size = glm::vec2(gl->bitmap.width, gl->bitmap.rows);
    _glyphs[id].offset = glm::vec2(gl->bitmap_left, gl->bitmap_top) + ( glm::vec2(_size) - _glyphs[id].size ) / glm::vec2(-2, 2);
    return gl;
}

void Font::createTexFromGlyph(unsigned int textureSize, FT_GlyphSlot gl, float *totalMap, unsigned int id)
{
    DistMap dm(gl->bitmap.buffer, _size, gl->bitmap.width, gl->bitmap.rows);

    float *out = dm.generate(textureSize);

    unsigned int sizeSq = textureSize * textureSize;


    float min = out[0];
    float max = out[0];

    for (unsigned int j = 0; j < sizeSq; j++)
    {
        if ( out[j] > max )
            max = out[j];
        if ( out[j] < min )
            min = out[j];
    }

    if (max == min )
    {
        for (unsigned int j = 0; j< sizeSq;j++)
        {
            out[j] = 0.0f;
        }
    }
    else
    {


        float diff = 1/ ( max - min );

        //max = 1 / max;

        min *= diff;

        min = -.5f;

        //min = - 1 / min;

        for (unsigned int j = 0; j< sizeSq;j++)
        {
            if ( out[j] > 0)
                out[j] = out[j] * diff - min;
            else
                out[j] = out[j] * diff - min;
        }
    }

    memcpy(totalMap + sizeSq * id, out, sizeSq * sizeof(float));

    delete out;
}


Font::~Font()
{
    //dtor
}
