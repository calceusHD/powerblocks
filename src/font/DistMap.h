#ifndef DISTMAP_H
#define DISTMAP_H

#include <vector>
#include <iostream>
#include <glm/glm.hpp>

class DistMap
{
    public:
        unsigned int size;
        unsigned char *data;
        unsigned int rWidth;
        unsigned int rHeight;
        unsigned int offX, offY;
        bool valid;

        DistMap(unsigned char *data, unsigned int size, unsigned int rWidth, unsigned int rHeight);
        virtual ~DistMap();

        void createChangeList();
        bool getColor(unsigned int x, unsigned int y);
        bool checkAround(unsigned int x, unsigned int y);

        float *generate(unsigned int sizeo);
        float findNearest(unsigned int x, unsigned int y);

        float *getFullImage();

        std::vector<glm::ivec2> whiteList;
        std::vector<glm::ivec2> blackList;



    protected:
    private:
};

#endif // DISTMAP_H
