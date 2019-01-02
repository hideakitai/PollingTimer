#pragma once
#ifndef STOPWATCH_H
#define STOPWATCH_H

class StopWatch
{
public:

    void start() { play(); us_start_ = micros(); }
    void stop() { pause(); us_start_ = 0; }
    void restart() { stop(); start(); }

    void play() { is_running_ = true; us_elapsed_ = us(); }
    void pause() { is_running_ = false; us_start_ = micros() - us_elapsed_; }

    bool isRunning() { return is_running_; }

    inline void setCurrTime(double sec)
    {
        us_offset_ += sec * 1000000. - us();
    }
    void setOffsetUs(double us_offset) { us_offset_ = us_offset; }
    void setOffsetMs(double ms_offset) { setOffsetUs(1000. * ms_offset); }
    void setOffsetSec(double sec_offset) { setOffsetUs(1000000. * sec_offset); }

    // TODO: how to handle over int32_t range
    inline double us() const
    {
        if (us_start_ == 0) return 0;
        return (double)micros() - us_start_ + us_offset_;
    }
    inline double ms() const { return us() * 0.001; }
    inline double sec() const { return us() * 0.000001; }

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
    , curr_frame_(0)
    , prev_frame_(0)
    , b_zero_start_(false)
    {
    }

    double frame()
    {
        return us() / interval_;
    }

    bool isNextFrame()
    {
        bool b;
        double curr_frame = frame();
        if (b_zero_start_) b = (floor(curr_frame) != floor(prev_frame_));
        else               b = (ceil(curr_frame) != ceil(prev_frame_));
        prev_frame_ = curr_frame;
        return b;
    }

    void setFrameRate(double fps)
    {
        fps_ = fps;
        interval_ = getTargetIntervalMicros();
    }

    void setZeroStart(bool b) { b_zero_start_ = b; }

private:

    double getTargetIntervalMicros() const { return (1000000.0 / fps_); }

    double fps_ {40.0};
    double interval_ {0.0};
    double curr_frame_ {0};
    double prev_frame_ {0};
    bool b_zero_start_ {true};
};


#endif // STOPWATCH_H
