# StopWatch
Arduino library to monitor time and frame rate from any time if you want.
This library has two classes, `StopWatch` and `FrameRateCounter`.

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
    if (fps.isRunning())
    {
        if (fps.isNextFrame())
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

## License

MIT
