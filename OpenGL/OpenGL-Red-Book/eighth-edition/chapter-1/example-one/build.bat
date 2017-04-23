IF NOT EXIST .\build mkdir .\build
pushd .\build

:: NOTE(nick): current build uses x64 instead of x86 static libraries
cl -Od -MD -nologo -Zi ..\main.cpp /link -incremental:no -opt:ref /LIBPATH:..\lib\x64 glew32s.lib glfw3.lib opengl32.lib glu32.lib user32.lib gdi32.lib shell32.lib

dir

popd

copy triangles.vert .\build
copy triangles.frag .\build
