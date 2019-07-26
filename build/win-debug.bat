if not exist .\artifacts\* mkdir .\artifacts
if not exist .\artifacts\obj\* mkdir .\artifacts\obj

cl ^
/EHsc ^
/std:c++17 ^
/Zi ^
/I..\src\deps ^
/I..\src\deps\opengl ^
/I..\src ^
/DUNICODE ^
/Fo.\artifacts\obj\ ^
    ..\src\platform\win\main.cpp ^
    ..\src\platform\win\window.cpp ^
/link ^
    user32.lib ^
    gdi32.lib ^
    opengl32.lib ^
/out:.\artifacts\gfx.exe