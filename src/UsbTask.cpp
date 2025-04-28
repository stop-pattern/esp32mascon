#include "UsbTask.h"
#include "Gamepad.h"
#include "Settings.h"
#include <Arduino.h>
#include <USB.h>
#include <USBHIDGamepad.h>

using namespace Settings::USB;

namespace {
/// @brief ゲームパッドのラッパー
Gamepad gamepad;
// USBHIDGamepad gamepad;
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
#pragma endregion

#pragma region タスク
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
        delay(1000);
        // gamepad.setButtons(0x12725277);
    }
    vTaskDelete(NULL);
}
#pragma endregion
