#pragma once
#ifndef HT_INTERVALCOUNTER_H
#define HT_INTERVALCOUNTER_H

#include "PollingTimer.h"

class IntervalCounter : public PollingTimer {
    double interval_us {1.};  // 1us == minimum interval
    double cnt {0.};

protected:
    std::function<void(void)> func;

public:
    explicit IntervalCounter(const double sec = 0.)
    : interval_us(constrain_interval_us(sec * 1000000.)), cnt(0.) {
    }

    virtual ~IntervalCounter() {}

    inline void startFromCount(const double from_count) {
        startIntervalUsecFromForCount(this->interval_us, from_count, 0, false);
    }
    inline void startForCount(const double for_count, const bool loop = false) {
        startIntervalUsecFromForCount(this->interval_us, 0., for_count, loop);
    }
    inline void startFromForCount(const double from_count, const double for_count, const bool loop = false) {
        startIntervalUsecFromForCount(this->interval_us, from_count, for_count, loop);
    }

    inline void startIntervalSec(const double interval_sec) {
        startIntervalFromForSec(interval_sec, 0., 0., false);
    }
    inline void startIntervalMsec(const double interval_ms) {
        startIntervalFromForMsec(interval_ms, 0., 0., false);
    }
    inline void startIntervalUsec(const double interval_us) {
        startIntervalFromForUsec(interval_us, 0., 0., false);
    }

    inline void startIntervalFromSec(const double interval_sec, const double from_sec) {
        startIntervalFromForSec(interval_sec, from_sec, 0., false);
    }
    inline void startIntervalFromMsec(const double interval_ms, const double from_ms) {
        startIntervalFromForMsec(interval_ms, from_ms, 0., false);
    }
    inline void startIntervalFromUsec(const double interval_us, const double from_us) {
        startIntervalFromForUsec(interval_us, from_us, 0., false);
    }
    inline void startIntervalSecFromCount(const double interval_sec, const double from_count) {
        startIntervalSecFromForCount(interval_sec, from_count, 0., false);
    }
    inline void startIntervalMsecFromCount(const double interval_ms, const double from_count) {
        startIntervalMsecFromForCount(interval_ms, from_count, 0., false);
    }
    inline void startIntervalUsecFromCount(const double interval_us, const double from_count) {
        startIntervalUsecFromForCount(interval_us, from_count, 0., false);
    }

    inline void startIntervalForSec(const double interval_sec, const double for_sec, const bool loop = false) {
        startIntervalFromForSec(interval_sec, 0., for_sec, loop);
    }
    inline void startIntervalForMsec(const double interval_ms, const double for_ms, const bool loop = false) {
        startIntervalFromForMsec(interval_ms, 0., for_ms, loop);
    }
    inline void startIntervalForUsec(const double interval_us, const double for_us, const bool loop = false) {
        startIntervalFromForUsec(interval_us, 0., for_us, loop);
    }
    inline void startIntervalSecForCount(const double interval_sec, const double for_count, const bool loop = false) {
        startIntervalSecFromForCount(interval_sec, 0., for_count, loop);
    }
    inline void startIntervalMsecForCount(const double interval_ms, const double for_count, const bool loop = false) {
        startIntervalMsecFromForCount(interval_ms, 0., for_count, loop);
    }
    inline void startIntervalUsecForCount(const double interval_us, const double for_count, const bool loop = false) {
        startIntervalUsecFromForCount(interval_us, 0., for_count, loop);
    }

    inline void startIntervalFromForSec(const double interval_sec, const double from_sec, const double for_sec, const bool loop = false) {
        startIntervalFromForUsec(interval_sec * 1000000., from_sec * 1000000., for_sec * 1000000., loop);
    }
    inline void startIntervalFromForMsec(const double interval_ms, const double from_ms, const double for_ms, const bool loop = false) {
        startIntervalFromForUsec(interval_ms * 1000., from_ms * 1000., for_ms * 1000., loop);
    }
    inline void startIntervalFromForUsec(const double interval_us, const double from_us, const double for_us, const bool loop = false) {
        this->interval_us = constrain_interval_us(interval_us);
        this->cnt = from_us / this->interval_us;
        startFromForUsec(from_us, for_us, loop);
    }
    inline void startIntervalSecFromForCount(const double interval_sec, const double from_count, const double for_count, const bool loop = false) {
        startIntervalUsecFromForCount(interval_sec * 1000000., from_count, for_count, loop);
    }
    inline void startIntervalMsecFromForCount(const double interval_ms, const double from_count, const double for_count, const bool loop = false) {
        startIntervalUsecFromForCount(interval_ms * 1000., from_count, for_count, loop);
    }
    inline void startIntervalUsecFromForCount(const double interval_us, const double from_count, const double for_count, const bool loop = false) {
        this->interval_us = constrain_interval_us(interval_us);
        this->cnt = from_count;
        startFromForUsec(from_count * this->interval_us, for_count * this->interval_us, loop);
    }

    inline void startOnce() {
        startForCount(1);
    }
    inline void startOnceAfterSec(const double after_sec) {
        startIntervalForSec(after_sec, 1);
    }
    inline void startOnceAfterMsec(const double after_ms) {
        startIntervalForMsec(after_ms, 1);
    }
    inline void startOnceAfterUsec(const double after_us) {
        startIntervalForUsec(after_us, 1);
    }

    inline void stop() {
        PollingTimer::stop();
        cnt = 0;
    }

    inline void restart() {
        IntervalCounter::stop();
        start();
    }

    inline double count() {
        if (isPausing()) update();
        return (double)cnt;
    }

    inline double getIntervalUsec64() const { return int64_t(interval_us); }
    inline double getIntervalUsec() const { return interval_us; }
    inline double getIntervalMSec() const { return interval_us * 0.001; }
    inline double getIntervalSec() const { return interval_us * 0.000001; }

    inline void setIntervalUsec64(const int64_t u64) { interval_us = constrain_interval_us((double)u64); }
    inline void setIntervalUsec(const double us) { interval_us = constrain_interval_us(us); }
    inline void setIntervalMsec(const double ms) { interval_us = constrain_interval_us(ms * 1000.); }
    inline void setIntervalSec(const double sec) { interval_us = constrain_interval_us(sec * 1000000.); }

    inline bool hasInterval() const { return interval_us != 1.; }

    inline void setOffsetCount(const double count) {
        setOffsetUsec(interval_us * count);
    }

    inline void onUpdate(const std::function<void(void)>& f) {
        func = f;
    }

    inline bool hasEventOnUpdate() const {
        return (bool)func;
    }

    inline void removeEventOnUpdate() {
        func = nullptr;
    }

    inline bool update() {
        const double us = this->usec();
        double prev_cnt = cnt;
        cnt = us / interval_us;
        bool b = (floor(cnt) > 0.) && (floor(cnt) > floor(prev_cnt));
        if (b && func) func();
        return b;
    }

private:
    inline double constrain_interval_us(const double interval_us) {
        if (interval_us <= 1.)
            return 1.;
        else if (interval_us >= 1000000000.)
            return 1000000000.;
        else
            return interval_us;
    }
};

#endif  // HT_INTERVALCOUNTER_H
