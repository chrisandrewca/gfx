#include "win.h"
#include "window.h"

#include <iostream>

int APIENTRY wWinMain(
    HINSTANCE curr,
    HINSTANCE prev,
    LPWSTR cmdLine,
    int cmdShow)
{
    std::cout << "Hello, world!" << std::endl;

    Window window;
    if (!window.create(curr, cmdShow))
    {
        PostQuitMessage(1);
    }

    MSG msg;
    bool running = true;
    while (running)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT || msg.message == VK_ESCAPE || msg.message == VK_BACK)
            {
                running = false;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        window.render();
        window.swapBuffers();
    }
    window.destroy();

    return msg.wParam;
}