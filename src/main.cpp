#include "PinScan.h"
#include "UsbTask.h"
#include <Arduino.h>

namespace {
TaskHandle_t taskHandlePinScan = nullptr;
TaskHandle_t taskHandleUsb = nullptr;
} // namespace

void setup() {
    Serial.begin(115200);
    log_d("setup");

    xTaskCreate(PinScanTask, "PinScanTask", 2048, NULL, 1, &taskHandlePinScan);
    xTaskCreate(UsbTask, "UsbTask", 2048, NULL, 1, &taskHandleUsb);
}

void loop() {
    // 何もしない
    delay(100000);
}
