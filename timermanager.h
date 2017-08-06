#ifndef ITIMERMANAGER_H
#define ITIMERMANAGER_H
#include "iresourceitem.h"
#include <vector>
#include <assert.h>
#include <algorithm>
#include <QDebug>
namespace Vision{
class   ITimer
{
    public:
        virtual void    update(const float& elapsed)   =   0;
};
class TimerManager:public IResourceItem,
        public std::vector<ITimer*>{
#define MAX_TIMERS   20
public:
    int registerTimer(ITimer* timer){
        std::vector<ITimer*>::iterator itr = std::find(begin(),end(),timer) ;
        if(itr== end())
        {
            push_back(timer);
        }
        return 0;
    }
    int unregisterTimer(ITimer* timer){
        int ret = -1;
        std::vector<ITimer*>::iterator    itr =   std::find(begin(),end(),timer);
        assert(itr != end());
        if (itr != end())
        {
            erase(itr);
            ret = 0;
        }
        return ret;

    }
    void update(const float& elapsed){
        std::vector<ITimer*>::iterator    itr =   begin();
        for ( ; itr != end() ; ++ itr )
        {
            (*itr)->update(elapsed);
        }

    }
    int resourceInitialize(){
        reserve(MAX_TIMERS);
        return 0;
    }
    int resourceUnInitialize(){
        qDebug()<<"TimerManager resourceUnInitialize begin ...";
        std::vector<ITimer*>::iterator iter = this->begin();
        while (iter != this->end()) {
           iter = this->erase(iter);
        }
        qDebug()<<"TimerManager resourceUnInitialize end ...";
        return 0;

    }
};
}
#endif // ITIMERMANAGER_H
