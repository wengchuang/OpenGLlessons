#ifndef ITIMERMANAGER_H
#define ITIMERMANAGER_H
#include "timer.h"
#include "iresourceitem.h"
class ITimerManager:public IResourceItem{
public:
    virtual int registerTimer(Timer* timer) = 0;
    virtual int unregisterTimer(Timer* timer)= 0;
    virtual ~ITimerManager(){}
};
#endif // ITIMERMANAGER_H
