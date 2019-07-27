if not exist .\artifacts\* mkdir .\artifacts
if not exist .\artifacts\obj\* mkdir .\artifacts\obj

cl ^
/EHsc ^
/std:c++17 ^
/I..\src\deps ^
/I..\src\deps\opengl ^
/I..\src ^
/DUNICODE ^
/Zi ^
/DDEBUG ^
/DVALIDATE_SHADERS ^
/Fo.\artifacts\obj\ ^
    ..\src\platform\win\main.cpp ^
    ..\src\platform\win\gl_win.cpp ^
    ..\src\platform\win\window_opengl.cpp ^
    ..\src\gfx\gl.cpp ^
    ..\src\gfx\render_opengl.cpp ^
/link ^
    user32.lib ^
    gdi32.lib ^
    opengl32.lib ^
/out:.\artifacts\gfx.exe