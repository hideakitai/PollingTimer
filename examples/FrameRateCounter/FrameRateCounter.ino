#include <StopWatch.h>

FrameRateCounter fps(1);

void setup()
{
    Serial.begin(115200);
    delay(5000);

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

    if (fps.frame() >= 10) fps.restart();
}
