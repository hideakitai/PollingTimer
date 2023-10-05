#include <PollingTimer.h>

PollingTimer timer;

void setup() {
    Serial.begin(115200);
    delay(5000);

    timer.start();
}

void loop() {
    timer.update();  // reqired to trigger events (auto stop, loop, event callbacks, etc.)

    if (timer.isRunning()) {
        Serial.print("millis() : ");
        Serial.print(millis());
        Serial.print(", timer : ");
        Serial.println(timer.msec());
    }

    delay(500);

    if (timer.msec() > 5000) timer.restart();
}
