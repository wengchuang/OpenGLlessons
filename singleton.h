#ifndef SINGLETON_H
#define SINGLETON_H
#include <memory>

using namespace std;

template <class T>
class Singleton
{
public:
    static inline T *instance() {
        static T*  _instance = new T;
        return _instance;
    }

protected:
    Singleton(void) {}
    ~Singleton(void) {}
    Singleton(const Singleton &) {}
    Singleton &operator= (const Singleton &) {}
};
#endif // SINGLETON_H
