#include "PinScan.h"
#include <Arduino.h>
#include <Settings.h>
#include <array>

using namespace Settings::Input;
using namespace Settings::Pins;

namespace{
    /// @brief スキャンするGPIOのピン配列
    PinNumMatrix pinNumMatrix = {
        {{Settings::Pins::COL0, Settings::Pins::COL1, Settings::Pins::COL2,
          Settings::Pins::COL3, Settings::Pins::COL4, Settings::Pins::COL5},
         {Settings::Pins::ROW0, Settings::Pins::ROW1, Settings::Pins::ROW2,
          Settings::Pins::ROW3, Settings::Pins::ROW4, Settings::Pins::ROW5}}};
}

/// @brief ピンをスキャンするタスク
/// @param pvParameters
void PinScanTask(void *pvParameters) {
#pragma region 初期化部
    // ピンを初期化
    for (auto &&i : pinNumMatrix.at(COLUMN)) {
        pinMode(i, INPUT_PULLUP);
        log_d("Pin %d sets as INPUT_PULLUP", i);
    }
    for (auto &&i : pinNumMatrix.at(ROW)) {
        pinMode(i, OUTPUT_OPEN_DRAIN);
        digitalWrite(i, OPEN_DRAIN);
        log_d("Set pin %d to OUTPUT_OPEN_DRAIN, Initial value is Hi-Z", i);
    }

    delay(1000);

    // 読み取り値の一時保存先
    std::array<bool, SWITCH> valNumMatrixStore = {
        false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false, false, false};

    log_d("Start pin Scan");
#pragma endregion

#pragma region ループ部
    for (;;) {
        // esp_task_wdt_reset();

        // 読み取り値の一時保存先
        std::array<bool, SWITCH> valNumMatrix = {
            false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false,
            false, false, false, false, false, false, false, false, false};

        // スキャン後変化有無
        bool isChanged = false;
        // スキャン結果index
        size_t i = 0;

        // スキャン
        for (auto &&j : pinNumMatrix.at(ROW)) {
            // for (size_t j = 0; j < pinNumMatrix.at(ROW).size(); j++) {
            // Rowを1つLOWに落とす
            digitalWrite(j, LOW);
            delay(1); // 1ms待つ

            for (auto &&k : pinNumMatrix.at(COLUMN)) {
                // for (size_t k = 0; k < pinNumMatrix.at(COLUMN).size(); k++) {
                valNumMatrix.at(i) = static_cast<bool>(digitalRead(k));
                i++;
            }
        }

        log_d("Pin Scaned: %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, "
              "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, "
              "%d, %d, %d",
              valNumMatrix.at(0), valNumMatrix.at(1), valNumMatrix.at(2),
              valNumMatrix.at(3), valNumMatrix.at(4), valNumMatrix.at(5),
              valNumMatrix.at(6), valNumMatrix.at(7), valNumMatrix.at(8),
              valNumMatrix.at(9), valNumMatrix.at(10), valNumMatrix.at(11),
              valNumMatrix.at(12), valNumMatrix.at(13), valNumMatrix.at(14),
              valNumMatrix.at(15), valNumMatrix.at(16), valNumMatrix.at(17),
              valNumMatrix.at(18), valNumMatrix.at(19), valNumMatrix.at(20),
              valNumMatrix.at(21), valNumMatrix.at(22), valNumMatrix.at(23),
              valNumMatrix.at(24), valNumMatrix.at(25), valNumMatrix.at(26),
              valNumMatrix.at(27), valNumMatrix.at(28), valNumMatrix.at(29),
              valNumMatrix.at(30), valNumMatrix.at(31), valNumMatrix.at(32));

        if (valNumMatrixStore == valNumMatrix) {
            valNumMatrixStore = valNumMatrix;

            // portENTER_CRITICAL_ISR(&mutex);
            // someStorage = valNumMatrix;
            // someFlag = true;
            // portEXIT_CRITICAL_ISR(&mutex);
        }
    }
#pragma endregion

    // タスクを削除
    vTaskDelete(nullptr);
}
