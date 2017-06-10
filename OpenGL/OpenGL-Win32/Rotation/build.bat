IF NOT EXIST .\build mkdir .\build
pushd .\build

cl -Od -MTd -Zi -nologo ..\win32_main.cpp /link gdi32.lib opengl32.lib glu32.lib user32.lib

popd
