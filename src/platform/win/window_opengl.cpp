#include "window_opengl.h"
#include "gfx/open_gl.h"
#include "utils/log.h"

using namespace gfxOpenGL;

LRESULT CALLBACK WindowOpenGL::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	// "controller" function
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		else if (wParam == VK_UP ||
						 wParam == VK_RIGHT ||
						 wParam == VK_DOWN ||
						 wParam == VK_LEFT ||
						 wParam == VK_SPACE)
		{
			gfxLog::info("wParam {0}", wParam);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0; // message handled
}

WindowOpenGL::WindowOpenGL()
{
	width = 1024;
	height = 720;
	posX = CW_USEDEFAULT;
	posY = 0;
	windowed = true;

	style = WS_CAPTION | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
}

void WindowOpenGL::adjustSize()
{
	RECT rect = {0, 0, width, height};
	AdjustWindowRect(&rect, style, false);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;
}

void WindowOpenGL::center()
{
	RECT primaryDisplaySize;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &primaryDisplaySize, 0); // system taskbar and application desktop toolbars not included
	posX = (primaryDisplaySize.right - width) / 2;
	posY = (primaryDisplaySize.bottom - height) / 2;
}

bool WindowOpenGL::create(HINSTANCE curr, int cmdShow)
{
	windowClass = MAKEINTATOM(registerClass(curr));
	if (windowClass == 0)
	{
		showMessage(L"registerClass() failed.");
		return false;
	}

	HWND tmpWnd = CreateWindow(
			windowClass, L"Tmp Window",
			style,
			0, 0,				 // position x, y
			1, 1,				 // width, height
			NULL, NULL,	 // parent window, menu
			curr, NULL); // instance, param

	HDC tmpHdc = GetDC(tmpWnd); // Device Context

	PIXELFORMATDESCRIPTOR tmpPfd;
	ZeroMemory(&tmpPfd, sizeof(tmpPfd));
	tmpPfd.nSize = sizeof(tmpPfd);
	tmpPfd.nVersion = 1;
	tmpPfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	tmpPfd.iPixelType = PFD_TYPE_RGBA;
	tmpPfd.cColorBits = 32;
	tmpPfd.cAlphaBits = 8;
	tmpPfd.cDepthBits = 24;

	const int tmpPfdId = ChoosePixelFormat(tmpHdc, &tmpPfd);
	if (tmpPfdId == 0)
	{
		showMessage(L"ChoosePixelFormat() failed.");
		return false;
	}

	if (SetPixelFormat(tmpHdc, tmpPfdId, &tmpPfd) == false)
	{
		showMessage(L"SetPixelFormat() failed.");
		return false;
	}

	HGLRC tmpRC = wglCreateContext(tmpHdc); // Rendering Context

	if (tmpRC == 0)
	{
		showMessage(L"wglCreateContext() failed.");
		return false;
	}

	if (wglMakeCurrent(tmpHdc, tmpRC) == false)
	{
		showMessage(L"wglMakeCurrent() failed.");
		return false;
	}

	// get pointers to functions (or init opengl loader here)
	InitializeContextDependantFunctions();

	if (wglChoosePixelFormatARB == nullptr)
	{
		showMessage(L"wglGetProcAddress() failed.");
		return false;
	}

	if (wglCreateContextAttribsARB == nullptr)
	{
		showMessage(L"wglGetProcAddress() failed.");
		return false;
	}

	if (windowed == true)
	{
		adjustSize();
		center();
	}

	hwnd = CreateWindow(
			windowClass, L"OpenGL Window", // class name, window name
			style,												 // styles
			posX, posY,										 // posx, posy. If x is set to CW_USEDEFAULT y is ignored
			width, height,								 // width, height
			NULL, NULL,										 // parent window, menu
			curr, NULL);									 // instance, param

	hdc = GetDC(hwnd);

	const int pixelAttribs[] = {
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_ALPHA_BITS_ARB, 8,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
			WGL_SAMPLES_ARB, 4,
			0};

	int pixelFormatID;
	UINT numFormats;
	const bool status = wglChoosePixelFormatARB(hdc, pixelAttribs, NULL, 1, &pixelFormatID, &numFormats);

	if (status == false || numFormats == 0)
	{
		showMessage(L"wglChoosePixelFormatARB() failed.");
		return false;
	}

	PIXELFORMATDESCRIPTOR pfd;
	DescribePixelFormat(hdc, pixelFormatID, sizeof(pfd), &pfd);
	SetPixelFormat(hdc, pixelFormatID, &pfd);

	const int major_min = 4, minor_min = 0;
	const int contextAttribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, major_min,
			WGL_CONTEXT_MINOR_VERSION_ARB, minor_min,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			//		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
			0};

	hglrc = wglCreateContextAttribsARB(hdc, 0, contextAttribs);
	if (hglrc == NULL)
	{
		showMessage(L"wglCreateContextAttribsARB() failed.");
		return false;
	}

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(tmpRC);
	ReleaseDC(tmpWnd, tmpHdc);
	DestroyWindow(tmpWnd);
	if (!wglMakeCurrent(hdc, hglrc))
	{
		showMessage(L"wglMakeCurrent() failed.");
		return false;
	}

	// init opengl loader here (extra safe version)
	InitializeOpenGLFunctions();
	renderer.printBasicInfo();

	SetWindowText(hwnd, L"GFX");
	ShowWindow(hwnd, cmdShow);

	return true;
}

void WindowOpenGL::destroy()
{
	wglMakeCurrent(NULL, NULL);
	if (hglrc)
	{
		wglDeleteContext(hglrc);
	}
	if (hdc)
	{
		ReleaseDC(hwnd, hdc);
	}
	if (hwnd)
	{
		DestroyWindow(hwnd);
	}
}

void WindowOpenGL::render()
{
	renderer.render();
}

ATOM WindowOpenGL::registerClass(HINSTANCE curr)
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = WindowProcedure;
	wcex.hInstance = curr;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.lpszClassName = L"Core";
	return RegisterClassEx(&wcex);
}

void WindowOpenGL::showMessage(LPCWSTR message)
{
	MessageBox(0, message, L"WindowOpenGL::create", MB_ICONERROR);
}

void WindowOpenGL::swapBuffers()
{
	SwapBuffers(hdc);
}