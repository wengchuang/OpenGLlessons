#ifdef UBUNTU_WITH_GL

#include "glutimermanager.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "absgles2app.h"
static TimerMap* g_imerMap = NULL;
static void timerProc(int id)
{
    TimerMap::iterator itr = g_imerMap->find(id);
    if(itr != g_imerMap->end()){
        Timer* timer = itr->second;
        unsigned long timeOut = timer->getTimeOut();
        if(timeOut > 0){
            timer->update();
            glutTimerFunc(timeOut,timerProc,id);//需要在函数中再调用一次，才能保证循环
        }else{
           g_imerMap->erase(itr);
        }
    }

}
GLUTimerManager::GLUTimerManager()
{
    curId = 0;
    timerMap = new TimerMap;
    g_imerMap = this->timerMap;
}

int GLUTimerManager::registerTimer(Timer* timer){
    glutTimerFunc(timer->getTimeOut(),timerProc,curId);
    this->timerMap->insert(make_pair(curId,timer));
    int id = curId;
    curId++;
    return id;

}
int GLUTimerManager::unregisterTimer(Timer* timer){
    for(int i=0;i<curId;i++){
        TimerMap::iterator itr = timerMap->find(i);
         if(itr != timerMap->end()){
             if(timer == itr->second){
                timer->setTimeOut(0);
             }
         }
    }
    return 0;
}
GLUTimerManager::~GLUTimerManager(){
    delete this->timerMap;
}
#endif
