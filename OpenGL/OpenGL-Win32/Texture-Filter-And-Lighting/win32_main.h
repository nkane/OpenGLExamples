/*
 * Idea from: Handmade Hero - day ~37
 */

typedef struct read_file_result
{
	unsigned int ContentsSize;
	void *Contents;
} read_file_result;

struct loaded_bitmap
{
	int Width;
	int Height;
	unsigned int *Pixels;
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); 

GLvoid ResizeGLScene(GLsizei, GLsizei);

int InitGL(GLvoid);

int DrawGLScene(GLvoid);

GLvoid KillGLWindow(GLvoid);

BOOL CreateGLWindow(char *, int, int, int, bool);

read_file_result ReadEntireFile(char *);

loaded_bitmap * LoadBMP(char *);

int LoadGLTextures();

