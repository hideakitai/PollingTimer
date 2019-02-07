#pragma once
#ifndef STOPWATCH_H
#define STOPWATCH_H

class StopWatch
{
protected:

    const int64_t UNAVAILABLE              = 0xFFFFFFFFFFFFFFFF;
    const int64_t UINT32_NUMERIC_LIMIT_MAX = 0x00000000FFFFFFFF;

public:

    virtual ~StopWatch() {}

    inline void start()
    {
        running = true;
        prev_us = micros();
        origin = now = (int64_t)prev_us;
        overflow = offset = 0;
    }
    inline void stop()
    {
        running = false;
        prev_us = 0;
        origin = now = UNAVAILABLE;
        overflow = offset = 0;
    }
    inline void play()
    {
        if (isPausing())
        {
            running = true;
            uint32_t curr_us = micros();
            if (curr_us > prev_us)
                origin += (int64_t)(curr_us - prev_us);
            else
                origin += UINT32_NUMERIC_LIMIT_MAX - (int64_t)(prev_us - curr_us);
            prev_us = curr_us;
        }
        else if (isRunning()) ;
        else                  start();
    }
    inline void pause()
    {
        if      (isRunning()) { microsec(); running = false; }
        else if (isPausing()) ;
        else                  stop();
    }
    inline void restart() { stop(); start(); }

    inline bool isRunning() const { return running; }
    inline bool isPausing() const { return (!running && (origin != UNAVAILABLE)); }

    inline double us() { return (double)microsec(); }
    inline double ms() { return us() * 0.001; }
    inline double sec() { return us() * 0.000001; }

    inline void offsetUs(double us) { offset = (int64_t)us; }
    inline void offsetMs(double ms) { offsetUs(1000. * ms); }
    inline void offsetSec(double sec) { offsetUs(1000000. * sec); }

protected:

    inline int64_t microsec()
    {
        if      ( isPausing()) ;
        else if (!isRunning()) return 0;
        else
        {
            uint32_t curr_us = micros();
            if (curr_us < prev_us) overflow += UINT32_NUMERIC_LIMIT_MAX + (int64_t)1;
            prev_us = curr_us;
            now = (int64_t)curr_us + overflow;
        }
        return (double)(now - origin + offset);
    }

private:

    bool running {false};
    uint32_t prev_us {0};
    int64_t origin {UNAVAILABLE};
    int64_t now {UNAVAILABLE};
    int64_t overflow {0};
    int64_t offset {0};
};

class IntervalCounter : public StopWatch
{
public:

    explicit IntervalCounter (double sec)
    : available(false)
    , interval((uint32_t)(sec * 1000000.))
    , next(interval)
    , cnt(0)
    {}

    virtual ~IntervalCounter() {}

    inline void start() { StopWatch::start(); next = interval; cnt = 0; }
    inline void stop() { StopWatch::stop(); next = UNAVAILABLE; cnt = 0; }
    inline void restart() { IntervalCounter::stop(); IntervalCounter::start(); }

    inline bool update()
    {
        if (microsec() > next)
        {
            available = true;
            next = interval * (cnt++ + 1);
        }
        else
            available = false;

        return available;
    }

    inline bool isNext() const { return available; }
    inline double count() const { return cnt; }
    inline void setInterval(double i) { interval = (int64_t)(i * 1000000.); }
    inline void offset(int64_t offset) { offsetUs(interval * offset); cnt += offset; }

private:

    bool available {false};
    int64_t interval {0};
    int64_t next {0};
    int64_t cnt {0};
};

class FrameRateCounter : public IntervalCounter
{
public:

    explicit FrameRateCounter(double fps) // second
    : IntervalCounter(1.0 / fps)
    { }
    virtual ~FrameRateCounter() {}

    inline double frame() const { return is_one_start ? (count() + 1.0) : count(); }
    inline void setFrameRate(double fps) { setInterval(1. / fps); }
    inline void setFirstFrameToOne(bool b) { is_one_start = b; }

private:

    bool is_one_start {false};
};



#endif // STOPWATCH_H
