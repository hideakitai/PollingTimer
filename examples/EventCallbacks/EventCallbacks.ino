#include <IntervalCounter.h>
#include <FrameRateCounter.h>

IntervalCounter interval(1);
FrameRateCounter fps(2);

void setup() {
    Serial.begin(115200);
    delay(5000);

    interval.onUpdate([]() {
        Serial.print("IntervalCounter Event: curr time = ");
        Serial.println(millis());
    });

    fps.onUpdate([]() {
        Serial.print("FrameRateCounter Event: curr time = ");
        Serial.println(millis());
    });

    interval.start();
    fps.start();
}

void loop() {
    interval.update();
    fps.update();
}
