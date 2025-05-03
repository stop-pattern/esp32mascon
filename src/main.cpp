// #include "PinScan.h"
#include "UsbTask.h"
#include <Arduino.h>

namespace {
// TaskHandle_t taskHandlePinScan = nullptr;
TaskHandle_t taskHandleUsb = nullptr;
TaskHandle_t taskHandleSampling = nullptr;

/// @brief 割り込み用タイマー
hw_timer_t *timer = NULL;

/// @brief タイマー割り込みのディバイダー
/// @note 1us単位
const uint16_t timerCount = getApbFrequency() / 1000000;
} // namespace

void setup() {
    Serial.begin(115200);
    log_d("setup");

    // xTaskCreate(PinScanTask, "PinScanTask", 2048, NULL, 1, &taskHandlePinScan);
    xTaskCreate(UsbTask, "UsbTask", 2048, NULL, 1, &taskHandleUsb);
    xTaskCreate(SamplingTask, "SamplingTask", 2048, NULL, 1,
                &taskHandleSampling);

    // タイマー割り込みの設定
    timer = timerBegin(0, timerCount, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 1000, true);
    timerAlarmEnable(timer);
}

void loop() {
    // 何もしない
    delay(100000);
}
