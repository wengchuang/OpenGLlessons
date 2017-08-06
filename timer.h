#ifndef TIMER_H
#define TIMER_H
#include "timermanager.h"
#include "delegate.hpp"
#include <QDebug>
namespace Vision{

class VisionTimer :public ITimer,public Delegate2<int,VisionTimer*,const float&>{
public:
        VisionTimer(TimerManager& timerMgr,float timer = 1,void* /*user*/ = 0)
            :_timerMgr(timerMgr)
            ,_timer(timer)
            ,_elapsed(0)
        {
            _timerMgr.registerTimer(this);
        }
        virtual ~VisionTimer()
        {
            _timerMgr.unregisterTimer(this);
        }

        virtual void    update(const float& elapsed)
        {
            if (_delegate == 0)
            {
                return;
            }
            if (_elapsed >= _timer)
            {
                _delegate->invoke( this, _elapsed );
                _elapsed    =   0;
            }
            _elapsed    +=  elapsed;
        }
        virtual void   setTimer(float timer)
        {
            _timer  =   timer;
        }

        virtual float   getTimer() const
        {
            return  _timer;
        }
        protected:
                TimerManager&   _timerMgr;
                float   _timer;
                float   _elapsed;
        };

}

#endif // TIMER_H
