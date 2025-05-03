#include "UsbTask.h"
#include "Gamepad.h"
#include "Mascon.h"
#include "Settings.h"
#include <Arduino.h>
#include <USB.h>
#include <USBHIDGamepad.h>

using namespace Settings::USB;

namespace {
/// @brief ゲームパッドのラッパー
Gamepad gamepad;

/// @brief セマフォハンドル
SemaphoreHandle_t timerSemaphore = xSemaphoreCreateBinary();

/// @brief セマフォハンドル
SemaphoreHandle_t gamepadSemaphore = xSemaphoreCreateBinary();
} // namespace

#pragma region デモ用関数群
void testAxises8() {
    // -255から255までの値を1つずつ入力
    for (int i = INT8_MIN; i <= INT8_MAX; i++) {
        gamepad.leftStick(i, i);
        delay(10);
    }
    delay(100);
    for (int i = INT8_MIN; i <= INT8_MAX; i++) {
        gamepad.rightStick(i, i);
        delay(10);
    }
    delay(100);
    for (int i = INT8_MIN; i <= INT8_MAX; i++) {
        gamepad.leftTrigger(i);
        delay(10);
    }
    delay(100);
    for (int i = INT8_MIN; i <= INT8_MAX; i++) {
        gamepad.rightTrigger(i);
        delay(10);
    }
    gamepad.leftStick(0, 0);
    gamepad.rightStick(0, 0);
    gamepad.leftTrigger(0);
    gamepad.rightTrigger(0);
}
void testAxises16() {
    // -32767から32768までの値を1つずつ入力
    for (int i = 0; i <= INT16_MAX; i++) {
        gamepad.setAxes(i, i, i, i, i, i, i, i);
        log_i("setAxes: %x", i);
    }
    delay(100);
    gamepad.setAxes(0, 0, 0, 0, 0, 0, 0, 0);
}
void testKeys() {
    // 0から32までのキーを1つずつ押す
    for (int i = 0; i < 32; i++) {
        gamepad.pressButton(i);
        delay(100);
        gamepad.releaseButton(i);
    }
}
void testHats() {
    // 0から7までのキーを1つずつ押す
    for (int i = 0; i < 8; i++) {
        gamepad.hat(i);
        delay(100);
    }
    gamepad.hat(0);
}
void test() {
    log_d("test: axises");
    testAxises16();
    delay(1000);
    log_d("test: hat");
    testHats();
    delay(1000);
    gamepad.hat(0);
    log_d("test: btn");
    delay(1000);
    testKeys();
}
#pragma endregion

#pragma region UsbTask
/// @brief USBを制御するタスク
/// @param pvParameters
void UsbTask(void *pvParameters) {
    Serial.begin(115200);
    log_d("setup");

    gamepad.begin();

    // USB settings
    // VID/PID is from V-USB
    USB.VID(VID);
    USB.PID(PID);
    USB.serialNumber(SERIAL_NUMBER);
    // USB.firmwareVersion(FIRMWARE_VERSION);
    // USB.usbVersion(USB_VERSION);
    // USB.usbPower(USB_POWER);
    // USB.webUSB(WEB_USB);
    USB.productName(PRODUCT_NAME);
    USB.manufacturerName(MANUFACTURER_NAME);
    USB.begin();

    delay(1000);

    for (;;) {
        if (xSemaphoreTake(gamepadSemaphore, 1) == pdTRUE) {
            gamepad.write();
        }
    }

    // タスク削除
    vTaskDelete(NULL);
}
#pragma endregion

#pragma region onTimer
void IRAM_ATTR onTimer() {
    // タイマー割り込みが発生したらセマフォを通してSamplingTaskに通知
    xSemaphoreGiveFromISR(timerSemaphore, NULL);
}
#pragma endregion

#pragma region SamplingTask
void SamplingTask(void *pvParameters) {
    auto mascon = Mascon();
    mascon.setupPins();
    for (;;) {
        // セマフォを取得するまで待機
        if (xSemaphoreTake(timerSemaphore, 1) == pdTRUE) {
            // GPIOの状態を読み取る
            bool ischanged = mascon.samplingPins();
            if (ischanged) {
                // 変化があった場合、USBに送信する
                gamepad.setAxes(mascon.getPowerNotchInt16(),
                                mascon.getReverserInt16(),
                                mascon.getBrakeNotchInt16(), 0, 0, 0);
                xSemaphoreGive(gamepadSemaphore);
            }
        }
    }

    // タスク削除
    vTaskDelete(NULL);
}
#pragma endregion
