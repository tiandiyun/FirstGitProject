#ifndef _SINGLETON_LAZY_H_
#define _SINGLETON_LAZY_H_

template <typename T> class LazySingleton
{
public:
    static T& Instance(void)
    {
        static T single;
        return single;
    }
};


#endif