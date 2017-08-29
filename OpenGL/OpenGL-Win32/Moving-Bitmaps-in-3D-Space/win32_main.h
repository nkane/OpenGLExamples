/*
 * win32_main.h
 */

typedef struct read_file_result
{
	unsigned int	ContentSize;
	void 		*Contents;
} read_file_result;

struct loaded_bitmap
{
	int 		Width;
	int 		Height;
	unsigned int	*Pixel;
};

LRESULT CALLBACK WndProc(HWND windowHandle, UINT Message, WPARAM wParam, LPARAM lParam);

GLvoid ResizeGLScene(GLsizei width, GLsizei height);

int InitGL(GLvoid);

int DrawGLScene(GLvoid);

GLvoid KillGLWindow(GLvoid);

BOOL CreateGLWindow(char *title, int width, int height, int bits, bool fullscreenflag);

read_file_result ReadEntireFile(char *FileName);

loaded_bitmap *LoadBMP(char *);

int LoadGLTextures();

