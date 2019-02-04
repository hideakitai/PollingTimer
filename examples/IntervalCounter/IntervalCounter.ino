#include <StopWatch.h>
// IntervalCounter interval(1.0); // interval is 1.0[sec]
FrameRateCounter interval(1.0);


void setup()
{
    Serial.begin(115200);
    interval.start();
}

void loop()
{
    if (interval.isRunning())
    {
        if (interval.isNext())
        {
            // Serial.print("interval count = ");
            // Serial.print(interval.count());
            // Serial.print(", time = ");
            // Serial.println(interval.ms());
        }
    }
    // if (interval.count() > 10) interval.restart();
}