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
