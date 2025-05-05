// #include "PinScan.h"
#include "Settings.h"
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
    pinMode(Settings::Pins::LED_R, OUTPUT);
    pinMode(Settings::Pins::LED_G, OUTPUT);
    digitalWrite(Settings::Pins::LED_R, LOW);
    digitalWrite(Settings::Pins::LED_G, LOW);

    digitalWrite(Settings::Pins::LED_R, HIGH);
    Serial.begin(115200);
    log_d("setup");

    // xTaskCreate(PinScanTask, "PinScanTask", 2048, NULL, 1,
    // &taskHandlePinScan);
    delay(100);
    xTaskCreate(UsbTask, "UsbTask", 2048, NULL, 1, &taskHandleUsb);
    delay(100);
    xTaskCreate(SamplingTask, "SamplingTask", 4096, NULL, 1,
                &taskHandleSampling);
    delay(100);

    // タイマー割り込みの設定
    timer = timerBegin(0, timerCount, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 1000, true);

    delay(1000);

    timerAlarmEnable(timer);

    digitalWrite(Settings::Pins::LED_R, LOW);
}

void loop() {
    // 何もしない
    delay(100000);
}
