#pragma once
#ifndef HT_ONESHOTTIMER_H
#define HT_ONESHOTTIMER_H

#include "IntervalCounter.h"

class OneshotTimer : public IntervalCounter
{
public:

    OneshotTimer(const double sec, const std::function<void(void)>& f)
    : IntervalCounter(sec)
    {
        IntervalCounter::addFunction(f);
    }

    void start()
    {
        IntervalCounter::startForCount(1);
    }

    inline bool update()
    {
        if (usec64() == 0)
        {
            if (hasFinished())
            {
                if  (hasFunction())
                {
                    IntervalCounter::func();
                    return true;
                }
            }
        }
        return false;
    }
};

#endif // HT_ONESHOTTIMER_H
