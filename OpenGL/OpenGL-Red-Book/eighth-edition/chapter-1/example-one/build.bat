IF NOT EXIST .\build mkdir .\build
pushd .\build

cl -Od -MD -nologo -Zi ..\main.cpp /link -incremental:no -opt:ref /LIBPATH:..\lib glew32s.lib glfw3.lib opengl32.lib glu32.lib user32.lib gdi32.lib shell32.lib

dir

popd

copy triangles.vert .\build
copy triangles.frag .\build
