#ifndef _GFX_WINDOW_
#define _GFX_WINDOW_

#include "win.h"

class Window
{
public:
    Window::Window();

    bool create(HINSTANCE curr, int cmdShow);
    void destroy();
    void render();
    void swapBuffers();

private:
    static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    void Window::adjustSize();
    void Window::center();
    ATOM Window::registerClass(HINSTANCE curr);
    void Window::showMessage(LPCWSTR message);

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
};

#endif