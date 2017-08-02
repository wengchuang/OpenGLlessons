#ifndef TIMER_H
#define TIMER_H
#include "delegate.hpp"
typedef Delegate<void> timerTask;

class Timer
{
public:

    Timer(unsigned long timeOut = 1000);
    template<typename T,typename R>
    inline void setTimerFun(T*object, R (T::*method)()){
         task.bind(object,method);
    }
    inline unsigned long getTimeOut(){
        return mTimeOut;
    }
    inline void setTimeOut(unsigned long timeOut){
        mTimeOut = timeOut;
    }
    inline void update(){
        task();
    }
private:
    unsigned long  mTimeOut;
    timerTask      task;
};

#endif // TIMER_H
