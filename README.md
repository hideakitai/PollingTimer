# StopWatch
Arduino library to monitor time and frame rate from any time if you want.
This library has three classes, `StopWatch` , `FrameRateCounter`, and `IntervalCounter`.

## Usage

### StopWatch

``` C++
#include <StopWatch.h>
StopWatch stopwatch;

void setup()
{
    Serial.begin(115200);
    stopwatch.start();
}

void loop()
{
    if (stopwatch.isRunning())
    {
        Serial.print("millis() : ");
        Serial.print(millis());
        Serial.print(", stopwatch : ");
        Serial.println(stopwatch.ms());
    }
    if (stopwatch.ms() > 5000) stopwatch.restart();
}
```

### FrameRateCounter

``` C++
#include <StopWatch.h>
FrameRateCounter fps(30);

void setup()
{
    Serial.begin(115200);
    fps.start();
}

void loop()
{
    fps.update();

    if (fps.isRunning())
    {
        if (fps.isNext())
        {
            Serial.print("frame no. = ");
            Serial.print(fps.frame());
            Serial.print(", time = ");
            Serial.println(fps.ms());
        }
    }
    if (fps.frame() > 150) fps.restart();
}
```

### IntervalCounter

``` C++
#include <StopWatch.h>
IntervalCounter interval(1.0); // interval is 1.0[sec]

void setup()
{
    Serial.begin(115200);
    interval.start();
}

void loop()
{
    interval.update();

    if (interval.isRunning())
    {
        if (interval.isNext())
        {
            Serial.print("interval count = ");
            Serial.print(interval.count());
            Serial.print(", time = ");
            Serial.println(interval.ms());
        }
    }
    if (interval.count() > 10) interval.restart();
}
```

## APIs

### Common

``` C++
    inline void start()
    inline void stop()
    inline void restart()

    inline void play()
    inline void pause()

    inline bool isRunning()
    inline bool isPausing()

    inline double us() const
    inline double ms() const
    inline double sec() const

    inline void offsetUs(double us)
    inline void offsetMs(double ms)
    inline void offsetSec(double sec)
```

### For FrameRateCounter & IntervalCounter

``` C++
    FrameRateCounter(double fps)
    inline bool update()
    inline bool isNext()
    inline double frame() const
    inline void setFrameRate(double fps)
    inline void setFirstFrameToOne(bool b) // default : false (zero frame is first frame no.)
    inline void offset(int64_t offset)
```

### For FrameRateCounter & IntervalCounter

``` C++
    IntervalCounter(double interval) // second
    inline bool update()
    inline bool isNext()
    inline double count() const
    inline void setInterval(double interval)
    inline void offset(int64_t offset)
```


## License

MIT
