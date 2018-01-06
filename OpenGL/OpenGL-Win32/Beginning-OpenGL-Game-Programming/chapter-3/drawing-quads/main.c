
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#define global_variable     static
#define internal            static
#define local_persist       static

global_variable BOOL GlobalExiting = FALSE;
global_variable BOOL GlobalFullscreen = FALSE;
global_variable long GlobalWindowWidth = 800;
global_variable long GlobalWindowHeight = 600;
global_variable long GlobalWindowBits = 32;
global_variable HDC GlobalHdc;
global_variable float GlobalOpenGLAngle = 0.0f;

void
OpenGLInit()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void
OpenGLSetupProjection(int width, int height)
{
    // prevent divide by zero
    if (height == 0)
    {
        height = 1;
    }
    glViewport(0, 0, width, height);    // reset the viewport to new dimensions
    glMatrixMode(GL_PROJECTION);        // set projection matrix to current matrix
    glLoadIdentity();                   // reset projection matrix
    gluPerspective(52.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);     // calculate aspect ration of window
    glMatrixMode(GL_MODELVIEW);         // reset modelview matrix
    glLoadIdentity();                   // reset modelview matrix
}

void
OpenGLDrawPoints()
{
    glPointSize(4.0f);
    glBegin(GL_POINTS);
        for (int x = 0; x < 4; x++)
        {
            for (int z = 0; z < 4; z++)
            {
                glVertex3f(x, 0.0f, z);
            }
        }
    glEnd();
}

void
OpenGLDrawTriangles()
{
    glBegin(GL_TRIANGLES);
        for (int x = 0; x < 3; x++)
        {
            for (int z = 0; z < 3; z++)
            {
                glVertex3f(x , 0.0f, z);
                glVertex3f((x + 1.0f), 0.0f, z);
                glVertex3f(x, 0.0f, (z + 1.0f));
            }
        }
    glEnd();
}

void
OpenGLDrawTriangleFan()
{
    glBegin(GL_TRIANGLE_FAN);
        // center vertex fan
        glVertex3f(0.0f, 0.0f, 0.0f);
        // bottom size
        for (int x = 4; x > 0; x--)
        {
            glVertex3f((x - 1), 0.0f, 3.0f);
        }
        // right side
        for (int z = 4; z > 0; z--)
        {
            glVertex3f(3.0f, 0.0f, (z - 1.0f));
        }
    glEnd();
}

void
OpenGLDrawTriangleStrip()
{
    // 3 rows of triangle strips
    for (int x = 0; x < 3; x++)
    {
        glBegin(GL_TRIANGLE_STRIP);
            for (int z = 0; z < 3; z++)
            {
                glVertex3f(x, 0.0f, z);
                glVertex3f((x + 1.0f), 0.0f, z);
                glVertex3f(x, 0.0f, (z + 1.0f));
                glVertex3f((x + 1.0f), 0.0f, (z + 1.0f));
            }
        glEnd();
    }
}

void
OpenGLDrawQuads()
{
    glBegin(GL_QUADS);
        for (int x = 0; x < 3; x++)
        {
            for (int z = 0; z < 3; z++)
            {
                glVertex3f(x, 0.0f, z);
                glVertex3f((x + 1.0f), 0.0f, z);
                glVertex3f((x + 1.0f), 0.0f, (z + 1.0f));
                glVertex3f(x , 0.0f, (z + 1.0f));
            }
        }
    glEnd();
}

void
OpenGLDrawQuadStrip()
{
    for (int x = 0; x < 3; x++)
    {
        glBegin(GL_QUAD_STRIP);
        for (int z = 0; z < 4; z++)
        {
            glVertex3f(x , 0.0f, z);
            glVertex3f((x + 1.0f), 0.0f, z);
        }
        glEnd();
    }
}

void
OpenGLRender(float angle)
{
    // clear screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 10.0, 0.1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // top left
    glPushMatrix();
    glTranslatef(-6.0f, 0.0f, -4.0f);
    OpenGLDrawPoints();
    glPopMatrix();

    // top middle
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glTranslatef(-2.0f, 0.0f, -4.0f);
    OpenGLDrawTriangles();
    glPopMatrix();

    // top right
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glTranslatef(2.0f, 0.0f, -4.0f);
    OpenGLDrawQuads();
    glPopMatrix();

    // bottom left
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glTranslatef(-6.0f, 0.0f, 0.5f);
    OpenGLDrawTriangleStrip();
    glPopMatrix();

    // bottom middle
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glTranslatef(-2.0f, 0.0f, 0.5f);
    OpenGLDrawTriangleFan();
    glPopMatrix();

    // bottom right
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glTranslatef(2.0f, 0.0f, 0.5f);
    OpenGLDrawQuadStrip();
    glPopMatrix();
}

void
SetupPixelFormat(HDC hdc)
{
	int pixelFormat;
	PIXELFORMATDESCRIPTOR pfd = (PIXELFORMATDESCRIPTOR)
	{
		.nSize 		    	= sizeof(PIXELFORMATDESCRIPTOR),
		.nVersion 	    	= 1,
		.dwFlags 	     	= (PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER),
		.iPixelType     	= PFD_TYPE_RGBA,
		.cColorBits	     	= 0,
		.cRedBits	    	= 0,
		.cRedShift	    	= 0,
		.cGreenBits	    	= 0,
		.cGreenShift    	= 0,
		.cBlueBits	    	= 0,
		.cBlueShift	    	= 0,
		.cAlphaBits	    	= 0,
		.cAlphaShift    	= 0,
		.cAccumBits	    	= 0,
		.cAccumRedBits		= 0,
		.cAccumGreenBits	= 0,
		.cAccumBlueBits		= 0,
		.cDepthBits	    	= 16,
		.cStencilBits		= 0,
		.cAuxBuffers	    = 0,
		.iLayerType	    	= PFD_MAIN_PLANE,
		.bReserved	    	= 0,
		.dwLayerMask		= 0,
		.dwVisibleMask		= 0,
		.dwDamageMask		= 0
	};
	pixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);
}

LRESULT CALLBACK
MainWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	local_persist HDC hdc;
	local_persist HGLRC hrc;
	int height = 0;
	int width = 0;

	switch (message)
	{
		case WM_CREATE:
		{
			hdc = GetDC(hwnd);
			SetupPixelFormat(hdc);
			hrc = wglCreateContext(hdc);
			wglMakeCurrent(hdc, hrc);
		} break;

		case WM_DESTROY:
		case WM_QUIT:
		case WM_CLOSE:
		{
			wglMakeCurrent(hdc, NULL);
			wglDeleteContext(hrc);
			PostQuitMessage(0);
		} break;

		case WM_SIZE:
		{
			height = HIWORD(lParam);
			width = LOWORD(lParam);
            OpenGLSetupProjection(width, height);
            GlobalWindowWidth = width;
            GlobalWindowHeight = height;
		} break;

        case WM_ACTIVATEAPP:
            break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
        } break;

        case WM_LBUTTONDOWN:
            break;

        case WM_RBUTTONDOWN:
            break;

        case WM_MOUSEMOVE:
            break;

        case WM_LBUTTONUP:
            break;

        case WM_RBUTTONUP:
            break;

        case WM_KEYUP:
            break;

        case WM_KEYDOWN:
        {
            int fwKeys;
            LPARAM keyData;
            fwKeys = (int) wParam;
            keyData = lParam;
            switch (fwKeys)
            {
                case VK_ESCAPE:
                {
                    PostQuitMessage(0);
                } break;

                default:
                    break;
            }
        } break; 

        default:
            break;
	}

    return DefWindowProc(hwnd, message, wParam, lParam);
}

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX windowClass;
	HWND 	   hwnd;
	MSG	       msg;
	DWORD	   dwExStyle;
	DWORD	   dwStyle;
	RECT	   windowRect;

	windowRect.left   = (long) 0;
	windowRect.right  = (long) GlobalWindowWidth;
	windowRect.top    = (long) 0;
	windowRect.bottom = (long) GlobalWindowHeight;

	windowClass.cbSize 		    = sizeof(WNDCLASSEX);
	windowClass.style 		    = (CS_HREDRAW | CS_VREDRAW);
	windowClass.lpfnWndProc		= MainWindowProc;
	windowClass.cbClsExtra		= 0;
	windowClass.cbWndExtra		= 0;
	windowClass.hInstance		= hInstance;
	windowClass.hIcon		    = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor		    = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground	= NULL;
	windowClass.lpszMenuName	= NULL;
	windowClass.lpszClassName	= "GLClass";
	windowClass.hIconSm		    = LoadIcon(NULL, IDI_WINLOGO);

	if (!RegisterClassEx(&windowClass))
	{
		return 0;
	}

	if (GlobalFullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize     	= sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth	= GlobalWindowWidth;
		dmScreenSettings.dmPelsHeight	= GlobalWindowHeight;
		dmScreenSettings.dmBitsPerPel	= GlobalWindowBits;
		dmScreenSettings.dmFields   	= (DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT);

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			MessageBox(NULL, "Display mode failed", NULL, MB_OK);
			GlobalFullscreen = FALSE;
		}
	}

	if (GlobalFullscreen)
	{
		dwExStyle 	= (WS_EX_APPWINDOW);
		dwStyle 	= (WS_POPUP);
        ShowCursor(FALSE);
	}
	else
	{
		dwExStyle	= (WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
		dwStyle		= (WS_OVERLAPPEDWINDOW);
	}

	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

	hwnd = CreateWindowEx(0,
	        		      "GLClass",
		        	      "OpenGL Win32",
			              (dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS),
                          0, 0,
			              (windowRect.right - windowRect.left),
			              (windowRect.bottom - windowRect.top),
			              NULL,
			              NULL,
			              hInstance,
			              NULL);

	GlobalHdc = GetDC(hwnd);

	if (!hwnd)
	{
		return 0;
	}

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

    OpenGLInit();

	while (!GlobalExiting)
	{
        OpenGLRender(GlobalOpenGLAngle);
        GlobalOpenGLAngle += 0.5f;
        SwapBuffers(GlobalHdc);

        while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
        {
            if (!GetMessage(&msg, NULL, 0, 0))
            {
                GlobalExiting = TRUE;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
	}

    if (GlobalFullscreen)
    {
        ChangeDisplaySettings(NULL, 0);
        ShowCursor(TRUE);
    }

	return msg.wParam;
}
