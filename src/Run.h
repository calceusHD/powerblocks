#ifndef RUN_H
#define RUN_H

#include "window/window.h"
#include "window/glwindow.h"
#include "window/iwindow.h"
#include "font/print.h"
#include "font/font.h"
#include "gl/texturemanager.h"
#include "world.h"
#include "renderer.h"

class Run : IWindow
{
    public:
        Window _window;
        GlWindow _glWindow;
        bool _run;
        TextureManager _textureManager;
        Print _print;
        World _world;
        Renderer _renderer;
        glm::vec2 _look;
        glm::vec3 _pos;
        std::vector<bool> _keys;

        Run();
        virtual ~Run();
        void startLoop();

        virtual void size(uint64_t type, uint16_t width, uint16_t height) override;
        virtual void close() override;
        virtual void keydown(uint8_t vKey) override;
        virtual void keyup(uint8_t vKey) override;
        virtual void rawInputMouse(int32_t dX, int32_t dY, uint16_t btnFlags, uint16_t btnData) override;

    protected:
    private:
};

#endif // RUN_H
