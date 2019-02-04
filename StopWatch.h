#pragma once
#ifndef STOPWATCH_H
#define STOPWATCH_H

class StopWatch
{
public:
    virtual ~StopWatch() {}

    inline void start() { play(); us_start_ = micros(); }
    inline void stop() { pause(); us_start_ = 0; }
    inline void restart() { stop(); start(); }

    inline void play() { is_running_ = true; us_elapsed_ = us(); }
    inline void pause() { is_running_ = false; us_start_ = micros() - us_elapsed_; }

    inline bool isRunning() const { return is_running_; }

    // TODO: how to handle over int32_t range
    inline double us() const
    {
        if (us_start_ == 0) return 0;
        return (double)micros() - us_start_ + us_offset_;
    }
    inline double ms() const { return us() * 0.001; }
    inline double sec() const { return us() * 0.000001; }

    inline void setCurrTime(double sec) { us_offset_ += sec * 1000000. - us(); }
    inline void setOffsetUs(double us_offset) { us_offset_ = us_offset; }
    inline void setOffsetMs(double ms_offset) { setOffsetUs(1000. * ms_offset); }
    inline void setOffsetSec(double sec_offset) { setOffsetUs(1000000. * sec_offset); }

private:

    double us_start_ {0.0};
    double us_elapsed_ {0.0};
    double us_offset_ {0.0};
    bool is_running_ {false};
};


class FrameRateCounter : public StopWatch
{
public:

    FrameRateCounter(double fps)
    : fps_(fps)
    , interval_(getTargetIntervalMicros())
    , prev_frame_(0)
    , b_one_start_(true)
    {}

    virtual ~FrameRateCounter() {}

    inline void start() { prev_frame_ = currIntFrame(); this->StopWatch::start(); }
    inline void stop() { prev_frame_ = 0.0; this->StopWatch::stop(); }
    inline void restart() { stop(); start(); }

    inline bool isNext()
    {
        double curr_frame = currIntFrame();
        bool b = (curr_frame != prevIntFrame());
        prev_frame_ = curr_frame;
        return b;
    }

    inline double frame() const { return us() / interval_; }

    inline void setFrameRate(double fps)
    {
        fps_ = fps;
        interval_ = getTargetIntervalMicros();
    }

    inline void setFirstFrameToOne(bool b) { b_one_start_ = b; }

private:

    inline double currIntFrame() const { return floor(b_one_start_ ? frame() + 1.0 : frame()); }
    inline double prevIntFrame() const { return floor(prev_frame_); }

    inline double getTargetIntervalMicros() const { return (1000000.0 / fps_); }

    double fps_ {40.0};
    double interval_ {0.0};
    double prev_frame_ {0};
    bool b_one_start_ {false};
};


class IntervalCounter : public FrameRateCounter
{
public:

    IntervalCounter(double interval) // second
    : FrameRateCounter(1.0 / interval)
    { }
    ~IntervalCounter() {}

    inline double count() const { return frame(); }

    inline void setInterval(double interval) { setFrameRate(1.0 / interval); }
};


#endif // STOPWATCH_H
