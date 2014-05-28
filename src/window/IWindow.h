#ifndef IWINDOW_H
#define IWINDOW_H

#include <cstdint>

class IWindow
{
    public:
        IWindow();
        virtual ~IWindow();

        virtual void size(uint64_t type, uint16_t width, uint16_t height) {}
        virtual void keydown(uint8_t vKey) {}
        virtual void keyup(uint8_t vKey) {}
        virtual void close() {}
        virtual void mousemove(uint64_t btns, uint16_t posx, uint16_t posy) {}
        virtual void rawInputMouse(int32_t dX, int32_t dY, uint16_t btnFlags, uint16_t btnData) {}
    protected:
    private:
};

#endif // IWINDOW_H
