#ifndef _GFX_WINDOW_OPENGL_
#define _GFX_WINDOW_OPENGL_

#include "win.h"
#include "gfx/render_opengl.h"

class WindowOpenGL
{
public:
    WindowOpenGL::WindowOpenGL();

    bool create(HINSTANCE curr, int cmdShow);
    void destroy();
    void render();
    void swapBuffers();

private:
    static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    void WindowOpenGL::adjustSize();
    void WindowOpenGL::center();
    ATOM WindowOpenGL::registerClass(HINSTANCE curr);
    void WindowOpenGL::showMessage(LPCWSTR message);

    int width;
    int height;
    int posX;
    int posY;
    bool windowed;

    HDC hdc;
    HGLRC hglrc;
    HWND hwnd;
    DWORD style;
    LPTSTR windowClass;

    RenderOpenGL renderer;
};

#endif