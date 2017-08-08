#ifdef WIN32_WITH_OPENGL_ES2
#include "wingles2app.h"
WinGles2App::WinGles2App(HINSTANCE hInstance)
    :AbsGLES2App()
{
    _hInstance = hInstance;
    WNDCLASSEX  winClass;
                winClass.lpszClassName  =  _T("WinFrame");
                winClass.cbSize         =   sizeof(winClass);
                winClass.style          =   CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
                winClass.lpfnWndProc    =   wndProc;
                winClass.hInstance      =   hInstance;
                winClass.hIcon	        =   0;
                winClass.hIconSm	    =   0;
                winClass.hCursor        =   LoadCursor(hInstance, IDC_ARROW);
                winClass.hbrBackground  =   (HBRUSH)GetStockObject(BLACK_BRUSH);
                winClass.lpszMenuName   =   NULL;
                winClass.cbClsExtra     =   0;
                winClass.cbWndExtra     =   0;
                RegisterClassEx(&winClass);
                mInput = NULL;
}
int WinGles2App::initWindows(){
    int x,y,width,height;
    getWindowInfo(&x,&y,&width,&height);
    _hWnd   =   CreateWindowEx( NULL,
                                            _T("WinFrame"),
                                            _T("WinFrame"),
                                            WS_OVERLAPPEDWINDOW,
                                            CW_USEDEFAULT,
                                            CW_USEDEFAULT,
                                            width,
                                            height,
                                            NULL,
                                            NULL,
                                            _hInstance,
                                            this
                                            );
    if (_hWnd == 0)
    {
        return  -1;
    }
    qDebug()<<"_hWnd:"<<_hWnd;
    ShowWindow(_hWnd,SW_SHOW);
    return 0;

}
int WinGles2App::onInitOpenGLES(){
    int ret = -1;
    const EGLint attribs[] =
    {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_DEPTH_SIZE,24,
        EGL_NONE
    };
    EGLint 	format(0);
    EGLint	numConfigs(0);
    EGLint  major;
    EGLint  minor;

    //! 1
    _display	    =	eglGetDisplay(EGL_DEFAULT_DISPLAY);
    qDebug() <<"_display:"<<_display;

    //! 2init
    bool bRet = eglInitialize(_display, &major, &minor);
     qDebug()<<"major:"<<major;
      qDebug()<<"minor:"<<minor;

    qDebug()<<"bRet:"<<bRet;

    //! 3
    eglChooseConfig(_display, attribs, &_config, 1, &numConfigs);
    qDebug() <<"_display:"<<_display;

    eglGetConfigAttrib(_display, _config, EGL_NATIVE_VISUAL_ID, &format);
    qDebug() <<"_config:"<<_config;

    //! 4
    _surface	    = 	eglCreateWindowSurface(_display, _config, _hWnd, NULL);
    qDebug() <<"_surface:"<<_surface;

    //! 5
    EGLint attr[]   =   { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };
    _context 	    = 	eglCreateContext(_display, _config, 0, attr);
    qDebug() <<"_context:"<<_context;
    //! 6
    if (eglMakeCurrent(_display, _surface, _surface, _context) == EGL_FALSE)
    {
        qDebug()<<"init ret:"<<false;
        return ret;
    }

    eglQuerySurface(_display, _surface, EGL_WIDTH,  &_width);
    eglQuerySurface(_display, _surface, EGL_HEIGHT, &_height);

    ret = 0;

    return  ret;

}
void WinGles2App::onDestroyOpenGLES(){
    if (_display != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (_context != EGL_NO_CONTEXT)
        {
            eglDestroyContext(_display, _context);
        }
        if (_surface != EGL_NO_SURFACE)
        {
            eglDestroySurface(_display, _surface);
        }
        eglTerminate(_display);
    }
    _display    =   EGL_NO_DISPLAY;
    _context    =   EGL_NO_CONTEXT;
    _surface    =   EGL_NO_SURFACE;

}
void WinGles2App::onInputDeviceChanaged(IGLInput* input){
    mInput = input;
}
int WinGles2App::mainLoop(){
    MSG msg =   {0};
    while(msg.message != WM_QUIT)
    {
        if (msg.message == WM_DESTROY ||
            msg.message == WM_CLOSE)
        {
           break;
        }

        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        update();
        eglSwapBuffers(_display,_surface);

    }
    return 0;

}


LRESULT WinGles2App::onEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#endif

#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))
#endif

#ifndef GET_WHEEL_DELTA_WPARAM
#define GET_WHEEL_DELTA_WPARAM(wParam)          (int)((short)HIWORD(wParam))
#endif

    switch( msg )
    {
    case WM_SIZE:
        {
            RECT    rt;
            GetClientRect(_hWnd,&rt);
            _width   =   rt.right - rt.left;
            _height  =   rt.bottom - rt.top;

            resize(_width,_height);
        }
        break;
    case WM_LBUTTONDOWN:
        {
            if (mInput)
            {
                mInput->onMousePress(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam),MouseButton::Left);
            }
        }
        break;
    case WM_LBUTTONUP:
        {
            if (mInput)
            {
                mInput->onMouseRelease(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam),MouseButton::Left);
            }
        }
        break;
    case WM_RBUTTONDOWN:
        {
            if (mInput)
            {
                mInput->onMousePress(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam),MouseButton::Right);
            }
        }
        break;
    case WM_RBUTTONUP:
        {
            if (mInput)
            {
                mInput->onMouseRelease(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam),MouseButton::Right);
            }
        }
        break;
    case WM_MOUSEMOVE:
        {
            if (mInput)
            {
                mInput->onMouseMove(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam),0);
            }
        }
        break;

    case WM_MOUSEWHEEL:
        {
            if (mInput)
            {
                mInput->onMouseMove(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam),GET_WHEEL_DELTA_WPARAM(wParam));
            }
        }
        break;
    case WM_CHAR:
        {
            if (mInput)
            {
                mInput->onChar(wParam);
            }
        }
        break;
    case WM_KEYDOWN:
        {
        }
        break;
    case WM_CLOSE:
    case WM_DESTROY:
        {
            ::PostQuitMessage(0);
        }
        break;
    default:
        return DefWindowProc(_hWnd, msg, wParam, lParam );
    }
    return  S_OK;

}
#endif
