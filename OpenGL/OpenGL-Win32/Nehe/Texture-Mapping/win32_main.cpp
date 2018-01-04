/*
 *  Created By: Nick Kane
 */

#include <windows.h>	// header file for Windows
#include <gl\gl.h>	// header file for OpenGL32 library
#include <gl\glu.h>	// header file for GLu32 library

#include "bitmap.h"
#include "win32_main.h"

#define global_variable static
#define local_persist static
#define internal static

// global OpenGL rendering context handle
global_variable HGLRC RenderContextHandle = NULL;

// global device context handle
global_variable HDC DeviceContextHandle = NULL;

// global window handle
global_variable HWND WindowHandle = NULL;

// global handle to an program instance
global_variable HINSTANCE InstanceHandle = NULL;

// global array for keyboard key presses
global_variable bool keys[256];

// global window active 
global_variable bool active = true;

// global window fullscreen
global_variable bool fullscreen = true;

// global bitmap file
global_variable loaded_bitmap BitMap;

// global storage for texture(s)
global_variable GLuint texture[1];

// global x rotation
global_variable GLfloat x_rotation;

// global y rotation
global_variable GLfloat y_rotation;

// global z rotation
global_variable GLfloat z_rotation;

// default window procedure
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); 

// resize and initialize the GL Window
GLvoid ResizeGLScene(GLsizei, GLsizei);

// initializes OpenGL
int InitGL(GLvoid);

// drawing function
int DrawGLScene(GLvoid);

// destorys rendering context, device context, and window handle
GLvoid KillGLWindow(GLvoid);

// creates a GL window
BOOL CreateGLWindow(char *, int, int, int, bool);

// read entire file
read_file_result ReadEntireFile(char *);

// loads bitmap file
loaded_bitmap * LoadBMP(char *);

// loads bitmaps and convert to textures
int LoadGLTextures();

GLvoid ResizeGLScene(GLsizei width, GLsizei height)
{
	if (height == 0)
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,
		      ((GLfloat)width / (GLfloat)height),
		      0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int InitGL(GLvoid)
{
	if (!LoadGLTextures())
	{
		return FALSE;
	}
	
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	return TRUE;
}

int DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);

	glRotatef(x_rotation, 1.0f, 0.0f, 0.0f);
	glRotatef(y_rotation, 0.0f, 1.0f, 0.0f);
	glRotatef(z_rotation, 0.0f, 0.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, texture[0]);

	// begin drawing cube
	glBegin(GL_QUADS);
	{
		// begin front face
		// bottom left of texture and quad point
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( -1.0f, -1.0f, 1.0f );
		// bottom right of texture and quad point
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( 1.0f, -1.0f, 1.0f );
		// top right of texture and quad point
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( 1.0f, 1.0f, 1.0f );
		// top left of texture and quad point
		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( -1.0f, 1.0f, 1.0f );
		// end front face

		// begin back face
		// bottom right of texture and quad point
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( -1.0f, -1.0f, -1.0f );
		// top right of texture and quad point
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( -1.0f, 1.0f, -1.0f );
		// top left of texture and quad point
		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( 1.0f, 1.0f, -1.0f );
		// bottom left of texture and quad point
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( 1.0f, -1.0f, -1.0f );
		// end back face
		
		// begin top face
		// top left of texture and quad point
		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( -1.0f, 1.0f, -1.0f );
		// bottom left of texture and quad point
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( -1.0f, 1.0f, 1.0f );
		// bottom right of texture and quad point
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( 1.0f, 1.0f, 1.0f );
		// top right of texture and quad
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( 1.0f, 1.0f, -1.0f );
		// end top face

		// begin bottom face
		// top right of texture and quad point
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( -1.0f, -1.0f, -1.0f );
		// top left of texture and quad point
		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( 1.0f, -1.0f, -1.0f );
		// bottom left of texture and quad point
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( 1.0f, -1.0f, 1.0f );
		// bottom right of texture and quad point
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( -1.0f, -1.0f, 1.0f );
		// end bottom face

		// begin right face
		// bottom right of texture and quad point
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( 1.0f, -1.0f, -1.0f );
		// top right of texture and quad point
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( 1.0f, 1.0f, -1.0f );
		// top left of texture and quad point
		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( 1.0f, 1.0f, 1.0f );
		// bottom left of texture and quad point
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( 1.0f, -1.0f, 1.0f );
		// end right face
		
		// begin left face
		// bottom left of texture and quad point
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( -1.0f, -1.0f, -1.0f );
		// bottom right of texture and quad point
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( -1.0f, -1.0f, 1.0f );
		// top right of texture and quad point
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( -1.0f, 1.0f, 1.0f );
		// top left of texture and quad point
		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( -1.0f, 1.0f, -1.0f );
		// end left face
	}
	// end drawning cube
	glEnd();

	x_rotation += 0.3f;
	y_rotation += 0.2f;
	z_rotation += 0.4f;

	return TRUE;
}

GLvoid KillGLWindow(GLvoid)
{
	if (fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	if (RenderContextHandle)
	{
		if (!wglMakeCurrent(NULL, NULL))
		{
			MessageBox(NULL,
			 	   "Deattaching of device context and rendering context failed!",
				   "SHUTDOWN ERROR",
				   (MB_OK | MB_ICONINFORMATION));
		}
		if (!wglDeleteContext(RenderContextHandle))
		{
			MessageBox(NULL,
				   "Release rendering contxt failed.",
				   "SHUTDOWN ERROR",
				   (MB_OK | MB_ICONINFORMATION));
		}
		RenderContextHandle = NULL;
	}

	if (DeviceContextHandle && !ReleaseDC(WindowHandle, DeviceContextHandle))
	{
		MessageBox(NULL,
			  "Release device context failed.",
			  "SHUTDOWN ERROR",
			  (MB_OK | MB_ICONINFORMATION));
		DeviceContextHandle = NULL;
	}

	if (WindowHandle && !DestroyWindow(WindowHandle))
	{
		MessageBox(NULL,
			   "Could not release window handle.",
			   "SHUTDOWN ERROR",
			   (MB_OK | MB_ICONINFORMATION));
		WindowHandle = NULL;
	}

	if (!UnregisterClass("OpenGL", InstanceHandle))
	{
		MessageBox(NULL,
			   "Coult not unregister class.",
			   "SHUTDOWN ERROR",
			   (MB_OK | MB_ICONINFORMATION));
		InstanceHandle = NULL;
	}
}

BOOL CreateGLWindow(char *title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint PixelFormat;
	WNDCLASS WindowClass;
	DWORD doubleWordExtendedStyle;
	DWORD doubleWordStyle;

	RECT WindowRectangle;
	WindowRectangle.left = (long)0;
	WindowRectangle.right = (long)width;
	WindowRectangle.top = (long)0;
	WindowRectangle.bottom = (long)height;

	fullscreen = fullscreenflag;

	InstanceHandle = GetModuleHandle(NULL);
	WindowClass.style = (CS_HREDRAW | CS_VREDRAW | CS_OWNDC);
	WindowClass.lpfnWndProc = (WNDPROC) WndProc;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = InstanceHandle;
	WindowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WindowClass.hbrBackground = NULL;
	WindowClass.lpszMenuName = NULL;
	WindowClass.lpszClassName = "OpenGL";

	if (!RegisterClass(&WindowClass))
	{
		MessageBox(NULL,
			  "Failed to register the window class.", 
			  "ERROR",
			  (MB_OK | MB_ICONEXCLAMATION));
		return FALSE;
	}

	if (fullscreen)
	{
		DEVMODE DeviceModeScreenSettings;
		memset(&DeviceModeScreenSettings, 0, sizeof(DeviceModeScreenSettings));
		DeviceModeScreenSettings.dmSize = sizeof(DeviceModeScreenSettings);
		DeviceModeScreenSettings.dmPelsWidth = width;
		DeviceModeScreenSettings.dmPelsHeight = height;
		DeviceModeScreenSettings.dmBitsPerPel = bits;
		DeviceModeScreenSettings.dmFields = (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT);
		
		if (ChangeDisplaySettings(&DeviceModeScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL,
				       "The request fullscreen mode is not supported by\nyour video card. Use Windowed Mode Instead?",
				       "OpenGL",
				       (MB_YESNO | MB_ICONEXCLAMATION)) == IDYES)
			{
				fullscreen = FALSE;
			}
			else 
			{
				MessageBox(NULL,
					   "Program will now close.",
					   "ERROR",
					   (MB_OK | MB_ICONSTOP));
				return FALSE;
			}
		}
	}

	if (fullscreen)
	{
		doubleWordExtendedStyle = WS_EX_APPWINDOW;
		doubleWordStyle = WS_POPUP;
		ShowCursor(FALSE);
	}
	else
	{
		doubleWordExtendedStyle = (WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
		doubleWordStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&WindowRectangle, doubleWordStyle, FALSE, doubleWordExtendedStyle);

	WindowHandle = CreateWindowEx(doubleWordExtendedStyle,
			            "OpenGL",
				    title,
				    (WS_CLIPSIBLINGS | WS_CLIPCHILDREN | doubleWordStyle),
				    0, 0,
				    (WindowRectangle.right - WindowRectangle.left),
				    (WindowRectangle.bottom - WindowRectangle.top),
				    NULL,
				    NULL,
				    InstanceHandle,
				    NULL);

	if (!WindowHandle)
	{
		KillGLWindow();
		MessageBox(NULL,
			   "Window Create Error.",
			   "ERROR",
			   (MB_OK | MB_ICONEXCLAMATION));
		return FALSE;
	}

	local_persist PIXELFORMATDESCRIPTOR PixelFormatDescriptor =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		(PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER), 
		PFD_TYPE_RGBA,
		bits,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0, 
		PFD_MAIN_PLANE,
		0,
		0, 0, 0,
	};

	if (!(DeviceContextHandle = GetDC(WindowHandle)))
	{
		KillGLWindow();
		MessageBox(NULL,
			   "Can't create a GL device context.",
			   "ERROR",
			   (MB_OK | MB_ICONEXCLAMATION));
		return FALSE;
	}

	if (!(PixelFormat = ChoosePixelFormat(DeviceContextHandle, &PixelFormatDescriptor)))
	{
		KillGLWindow();
		MessageBox(NULL,
			   "Can't find a suitable pixelformat.",
			   "ERROR",
			   (MB_OK | MB_ICONEXCLAMATION));
		return FALSE;
	}

	if (!SetPixelFormat(DeviceContextHandle, PixelFormat, &PixelFormatDescriptor))
	{
		KillGLWindow();
		MessageBox(NULL,
			   "Can't set the pixelformat.",
			   "ERROR",
			   (MB_OK | MB_ICONEXCLAMATION));
		return FALSE;
	}

	if (!(RenderContextHandle = wglCreateContext(DeviceContextHandle)))
	{
		KillGLWindow();
		MessageBox(NULL, 
			   "Can't create a GL rendering context.",
			   "ERROR",
			   (MB_OK | MB_ICONEXCLAMATION));
		return FALSE;
	}

	if (!wglMakeCurrent(DeviceContextHandle, RenderContextHandle))
	{
		KillGLWindow();
		MessageBox(NULL, 
			   "Can't attach render context to device context",
			   "ERROR",
			   (MB_OK | MB_ICONEXCLAMATION));
		return FALSE;
	}

	ShowWindow(WindowHandle, SW_SHOW);
	SetForegroundWindow(WindowHandle);
	SetFocus(WindowHandle);
	ResizeGLScene(width, height);

	if (!InitGL())
	{
		KillGLWindow();
		MessageBox(NULL, 
			   "Initialization of GL failed.",
			   "ERROR",
			   (MB_OK | MB_ICONEXCLAMATION));
		return FALSE;
	}

	return TRUE;
} 

LRESULT CALLBACK WndProc(HWND windowHandle, 
			 UINT Message,
			 WPARAM wParam,
			 LPARAM lParam)
{
	switch (Message)
	{
		case WM_ACTIVATE:
		{
			if (!HIWORD(wParam))
			{
				active = TRUE;
			}
			else 
			{
				active = FALSE;
			}
			return 0;
		} break;

		case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0;
			} break;
		} break;

		case WM_KEYDOWN:
		{
			keys[wParam] = TRUE;
			return 0;
		} break;

		case WM_KEYUP:
		{
			keys[wParam] = FALSE;
			return 0;
		} break;

		case WM_SIZE:
		{
			ResizeGLScene(LOWORD(lParam), HIWORD(lParam));
			return 0;
		} break;

		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		} break;

		default:
		{

		} break;
	}

	return DefWindowProc(windowHandle, Message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE instanceHandle,
		   HINSTANCE previousInstanceHandle,
		   LPSTR longPointerCmdParmeters,
		   int nCmdShow)
{
	MSG message;
	BOOL done = FALSE;

	if (MessageBox(NULL,
		       "Would you like to run in fullscreen mode?",
		       "Start fullscreen?",
		       (MB_YESNO | MB_ICONQUESTION)) == IDNO)
	{
		fullscreen = FALSE;
	}

	if (!CreateGLWindow("Win32 OpenGL Bolierplate", 640, 480, 16, fullscreen))
	{
		return 0;
	}


	while (!done)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
			{
				done = TRUE;
			}
			else 
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else
		{
			if (active)
			{
				if (keys[VK_ESCAPE])
				{
					done = TRUE;
				}
				else 
				{
					DrawGLScene();
					SwapBuffers(DeviceContextHandle);
				}

				if (keys[VK_F1])
				{
					keys[VK_F1] = FALSE;
					KillGLWindow();
					fullscreen = !fullscreen;

					if (!CreateGLWindow("Win32 OpenGL Boilerplate", 640, 480, 16, fullscreen))
					{
						return 0;
					}
				}
			}
		}
	}

	KillGLWindow();
	return (message.wParam);
}

// TODO(nick): memory allocated here needs to be released
read_file_result ReadEntireFile(char *FileName)
{
	read_file_result Result = {};
	HANDLE FileHandle = CreateFileA(FileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	if (FileHandle != INVALID_HANDLE_VALUE) 
	{
		LARGE_INTEGER FileSize;
		if (GetFileSizeEx(FileHandle, &FileSize))
		{
			unsigned int FileSize32 = ((unsigned int)FileSize.QuadPart);
			// TODO(nick): this needs to be freed?
			Result.Contents = VirtualAlloc(0, FileSize32, (MEM_RESERVE | MEM_COMMIT), PAGE_READWRITE);
			if (Result.Contents)
			{
				DWORD BytesRead;
				if (ReadFile(FileHandle, Result.Contents, FileSize32, &BytesRead, 0) &&
				    (FileSize32 == BytesRead))
				{
					Result.ContentsSize = FileSize32;
				}
				else
				{
					Result.Contents = 0;
				}
			}
		}
		CloseHandle(FileHandle);
	}

	return Result;
}

loaded_bitmap * LoadBMP(char *FileName)
{
	loaded_bitmap *Result = (loaded_bitmap *)VirtualAlloc(0, (unsigned int)sizeof(loaded_bitmap), (MEM_RESERVE | MEM_COMMIT), PAGE_READWRITE);
	read_file_result ReadResult = ReadEntireFile(FileName);

	if (ReadResult.ContentsSize != 0)
	{
		bitmap_header *Header = (bitmap_header *)ReadResult.Contents;
		unsigned int *Pixels = (unsigned int *)((unsigned char*)ReadResult.Contents + Header->BitmapOffset);
		Result->Pixels = Pixels;
		Result->Width = Header->Width;
		Result->Height = Header->Height;

		unsigned int RedMask   = Header->RedMask;
		unsigned int GreenMask = Header->GreenMask;
		unsigned int BlueMask  = Header->BlueMask;
		unsigned int AlphaMask = ~(RedMask | GreenMask | BlueMask);

		bit_scan_result RedShift 	= FindLeastSignificantSetBit(RedMask);
		bit_scan_result GreenShift	= FindLeastSignificantSetBit(GreenMask);
		bit_scan_result BlueShift	= FindLeastSignificantSetBit(BlueMask);
		bit_scan_result AlphaShift	= FindLeastSignificantSetBit(AlphaMask);

		unsigned int *SourceDest = Pixels;
		for (int y = 0; y < Header->Height; ++y)
		{
			for (int x = 0; x < Header->Width; ++x)
			{
				unsigned int C = *SourceDest;
				*SourceDest++ = (
							(((C >> AlphaShift.Index) & 0xFF) << 24) |
							(((C >> RedShift.Index) & 0xFF)   << 16) |
							(((C >> GreenShift.Index) & 0xFF) << 8)  |
							(((C >> BlueShift.Index) & 0xFF)  << 0)
						);
			}
		}

	}

	return Result;
}

int LoadGLTextures()
{
	int Status = FALSE;

	loaded_bitmap *TextureImage[1];
	// TODO(nick): not sure this is necessary?
	memset(TextureImage, 0, sizeof(void *)*1);
	if (TextureImage[0] = LoadBMP("../Data/cube.bmp"))
	{
		Status = TRUE;
		glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, TextureImage[0]->Width, TextureImage[0]->Height, 0, GL_BGRA_EXT,
			     GL_UNSIGNED_BYTE, TextureImage[0]->Pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (TextureImage[0])
		{
			VirtualFree(TextureImage[0], 0, MEM_RELEASE);
		}
	}

	return Status;
}

