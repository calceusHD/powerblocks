#include "Run.h"

Run::Run() :
    _window("PowerBlocks INTERNAL", 0, 1760, 990, this),
    _glWindow(&_window, 4, 1),
    _keys(256, false),
    _pos(0.0f, 0.0f, 0.0f),
    _look(125.0f, -235.0f)
{
    _window.show(SW_SHOW);
    Font font(1024, "data/fonts/arial.ttf", 32, _textureManager.getFreeTexture());
    _print.set(&font, "data/shaders/fontVertex.c", "data/shaders/fontFragment.c");



    startLoop();
}

Run::~Run()
{
    //dtor
}

void Run::startLoop()
{


    glBlendEquation(GL_FUNC_ADD);

    wglSwapIntervalEXT(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    VboBuilder vboB;
    _world.render(&vboB);
    while (_run)
    {
        MSG msg;
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				//quit = true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
        {


            glClearColor(0.0f, 0.0f, 0.0f, 0.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            _print.printfAt(-1.0f, -0.45f, 0.3f, 0.3, "Te st!");
            //vboB.clear();

            _renderer.renderVbo(&vboB, _look, _pos);
            if ( _keys.at('W'))
                _pos.x += 1.0f;

            if ( _keys.at('S'))
                _pos.x -= 1.0f;

            if ( _keys.at('A'))
                _pos.y += 1.0f;

            if ( _keys.at('D'))
                _pos.y -= 1.0f;

            if ( _keys.at('Q'))
                _pos.z += 1.0f;

            if ( _keys.at('Y'))
                _pos.z -= 1.0f;


            _glWindow.swapBuffers();
            std::cout << _look.x << ":" << _look.y << std::endl;
        }
    }
}

void Run::size(uint64_t type, uint16_t width, uint16_t height)
{
    glViewport(0, 0, width, height);
    _print.setScreenSize(glm::ivec2(width, height));
    _renderer.setScreenSize(glm::ivec2(width, height));
}

void Run::close()
{
    _run = false;
}

void Run::rawInputMouse(int32_t dX, int32_t dY, uint16_t btnFlags, uint16_t btnData)
{
    std::cout << "test";
    _look += glm::vec2(dX, dY) * 0.01f;
}

void Run::keydown(uint8_t vKey)
{
    _keys.at(vKey) = true;
}

void Run::keyup(uint8_t vKey)
{
    _keys.at(vKey) = false;
}
