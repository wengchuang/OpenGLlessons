#ifdef UBUNTU_WITH_GL


#ifndef GLUTIMERMANAGER_H
#define GLUTIMERMANAGER_H
#include "itimermanager.h"
#include <map>
typedef std::map<int,Timer*>  TimerMap;
class GLUTimerManager : public ITimerManager
{

public:
    ~GLUTimerManager();
    int registerTimer(Timer* timer);
    int unregisterTimer(Timer* timer);
    int resourceInitialize(){
        return 0;
    }
    int resourceUnInitialize(){
        return 0;
    }
    TimerMap* getTimerMap();
private:
    friend class GLESAppContext;
    GLUTimerManager();
private:
    TimerMap*       timerMap;
    int            curId;
};

#endif // GLUTIMERMANAGER_H
#endif
