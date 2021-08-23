#include <FrameRateCounter.h>

FrameRateCounter fps(1);

void setup() {
    Serial.begin(115200);
    delay(5000);

    fps.onStart([]() {
        Serial.println("onStart");
    });

    fps.onUpdate([&]() {
        Serial.print("onUpdate: frame = ");
        Serial.println(fps.frame());
    });

    fps.onPause([]() {
        Serial.println("onPause");
    });

    fps.onStop([]() {
        Serial.println("onStop");
    });

    fps.start();
}

void loop() {
    fps.update();

    while (Serial.available()) {
        char c = Serial.read();
        switch (c) {
            case '1': fps.start(); break;
            case '2': fps.pause(); break;
            case '3': fps.play(); break;
            case '4': fps.stop(); break;
            default: break;
        }
    }
}
