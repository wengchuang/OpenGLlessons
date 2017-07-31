#ifndef WINDOWADAPTER_H
#define WINDOWADAPTER_H
#include "windowsystem.h"
struct WindowAdapter
{
   int (*adapterInit)();
   int (*adapterUninit)();
   struct WindowEventCallBacks*(*getWindowEventCallBacks)(void);
};
struct WindowAdapter*getWindowAdapter();

#endif // WINDOWADAPTER_H
