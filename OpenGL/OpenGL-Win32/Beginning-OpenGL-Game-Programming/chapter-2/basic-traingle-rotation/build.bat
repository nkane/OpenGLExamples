IF NOT EXIST .\build MKDIR .\build
PUSHD .\build

cl /Od /MTd /Zi /nologo ..\main.c /link user32.lib  gdi32.lib opengl32.lib glu32.lib

POPD
