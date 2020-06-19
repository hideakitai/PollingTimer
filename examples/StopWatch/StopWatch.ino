#include <StopWatch.h>

StopWatch stopwatch;

void setup()
{
    Serial.begin(115200);
    delay(5000);

    stopwatch.start();
}

void loop()
{
    if (stopwatch.isRunning())
    {
        Serial.print("millis() : ");
        Serial.print(millis());
        Serial.print(", stopwatch : ");
        Serial.println(stopwatch.msec());
    }

    delay(500);

    if (stopwatch.msec() > 5000) stopwatch.restart();
}
