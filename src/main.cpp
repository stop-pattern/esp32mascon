#include "UsbTask.h"
#include <Arduino.h>

namespace {
TaskHandle_t taskHandleUsb = nullptr;
}

void setup() {
    Serial.begin(115200);
    log_d("setup");

    xTaskCreate(UsbTask, "UsbTask", 2048, NULL, 1, &taskHandleUsb);
}

void loop() {
    // 何もしない
    delay(100000);
}
