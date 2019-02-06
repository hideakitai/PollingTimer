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
