#ifndef TIMEREVENT_H
#define TIMEREVENT_H
#ifdef WIN32_WITH_OPENGL_ES2
    #include <windows.h>
#else
#include <sys/time.h>
#ifndef NULL
#define NULL (0)
#endif
#endif
namespace Vision {
class TimeStamp
{
protected:
    #ifdef WIN32
        LARGE_INTEGER   _frequency;
        LARGE_INTEGER   _startCount;
    #else
        timeval         _startCount;
    #endif
public:
    TimeStamp(){
        #ifdef WIN32
            QueryPerformanceFrequency(&_frequency);
            QueryPerformanceCounter(&_startCount);
        #else
            gettimeofday(&_startCount, NULL);
        #endif
    }
    inline void    update()
    {
    #ifdef WIN32
        QueryPerformanceCounter(&_startCount);
    #else
        gettimeofday(&_startCount, NULL);
    #endif
    }
    /**
    *   获取当前秒
    */
   inline double getElapsedSecond()
    {
        return  getElapsedTimeInMicroSec() * 0.000001;
    }
    /**
    *   获取毫秒
    */
    inline double getElapsedTimeInMilliSec()
    {
        return this->getElapsedTimeInMicroSec() * 0.001;
    }
    /**
    *   获取微妙
    */
    inline double getElapsedTimeInMicroSec()
    {
    #ifdef WIN32
        LARGE_INTEGER endCount;
        QueryPerformanceCounter(&endCount);

        double  startTimeInMicroSec =   _startCount.QuadPart * (1000000.0 / _frequency.QuadPart);
        double  endTimeInMicroSec   =   endCount.QuadPart * (1000000.0 / _frequency.QuadPart);
    #else
        timeval endCount;
        gettimeofday(&endCount, NULL);

        double  startTimeInMicroSec =   (_startCount.tv_sec * 1000000.0) + _startCount.tv_usec;
        double  endTimeInMicroSec   =   (endCount.tv_sec * 1000000.0) + endCount.tv_usec;
    #endif

        return endTimeInMicroSec - startTimeInMicroSec;
    }
};



class   FrameEvent
{
    public:
        float   _frameTime;
};

}

#endif // TIMEREVENT_H
