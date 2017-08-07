#ifdef WIN32_WITH_OPENGL_ES2
#ifndef WINGLES2APP_H
#define WINGLES2APP_H
#include "absgles2app.h"
#include "iglinput.h"

#include <Windows.h>
#include <tchar.h>

#include <EGL/egl.h>
#include <gles2/gl2.h>
#include <TCHAR.h>


class WinGles2App : public AbsGLES2App
{
public:
    WinGles2App(HINSTANCE hInstance);
    virtual ~WinGles2App(){
        UnregisterClass("CELLWinApp",_hInstance);
    }

private:
    //! 实例句柄
    HINSTANCE   _hInstance;
    //! 窗口句柄
    HWND        _hWnd;
    //! 窗口的高度
    int         _width;
    //! 窗口的宽度
    int         _height;

    /// for gles2.0
    EGLConfig   _config;
    EGLSurface  _surface;
    EGLContext  _context;
    EGLDisplay  _display;

    IGLInput    *mInput;
protected:
    virtual LRESULT onEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    static  LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {

        WinGles2App*  pThis   =   (WinGles2App*)GetWindowLong(hWnd,GWL_USERDATA);
        if (pThis)
        {
            return  pThis->onEvent(hWnd,msg,wParam,lParam);
        }
        if (WM_CREATE == msg)
        {
            CREATESTRUCT*   pCreate =   (CREATESTRUCT*)lParam;
            SetWindowLong(hWnd,GWL_USERDATA,(DWORD_PTR)pCreate->lpCreateParams);
        }
        return  DefWindowProc( hWnd, msg, wParam, lParam );
    }
protected:
    int initWindows();
    int onInitOpenGLES();
    void onDestroyOpenGLES();
    void onInputDeviceChanaged(IGLInput*);
    int mainLoop();
};

#endif // WINGLES2APP_H

#endif
