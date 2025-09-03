#include "Mascon.h"
#include "Settings.h"
#include <Arduino.h>
#include <array>
#include <driver/gpio.h>

using std::array;
using namespace Settings::Pins;

#pragma region マスコン操作クラス
Mascon::Mascon() {
    pinStatusStore = std::array<std::array<bool, PINNAME_MAX>, ARRAYNAME_MAX>{};
    for (auto &&i : pinStatusStore) {
        i.fill(true);
    }

    prevBrakeNotch = BRAKENOTCH_MAX;
}

Mascon::~Mascon() {}

void Mascon::setupPins() {
    for (auto &&i : pinNums) {
        pinMode(i, INPUT_PULLUP);
        log_d("Pin %d sets as INPUT_PULLUP", i);
    }

    for (size_t i = 0; i < pinStatusStore.size(); i++) {
        samplingPins();
    }
}

bool Mascon::samplingPins() {
    // スキャン後変化有無
    bool isChanged = false;

    // スキャン結果準備：シフト
    pinStatusStore.at(PREVIOUS) = pinStatusStore.at(CURRENT);
    // for (int i = pinStatusStore.size() - 1; i >= 1; i--) {
    //     pinStatusStore.at(i) = pinStatusStore.at(i - 1);
    // }

    // スキャン
    for (size_t i = 0; i < PINNAME_MAX; i++) {
        pinStatusStore.at(CURRENT).at(i) = digitalRead(pinNums.at(i));
        log_d("Pin %d:\t%d", pinNums.at(i), pinStatusStore.at(CURRENT).at(i));
    }

    // スキャン結果比較
    for (size_t i = 0; i < pinStatusStore.at(CURRENT).size(); i++) {
        // 値の変化は2回一致で採用
        bool currentStatsus = pinStatusStore.at(CURRENT).at(i);
        if (currentStatsus != pinStatusStore.at(OUTPUT_VALUE).at(i) &&
            currentStatsus == pinStatusStore.at(PREVIOUS).at(i)) {
            pinStatusStore.at(OUTPUT_VALUE).at(i) = currentStatsus;
            isChanged = true;
        }
    }

    return isChanged;
}

int16_t Mascon::getReverserInt16() const {
    // 入力をビット列で取得
    uint8_t status = pinStatusStore.at(OUTPUT_VALUE).at(R_F) << 0 |
                     pinStatusStore.at(OUTPUT_VALUE).at(R_R) << 1;

    // レバーサー
    int16_t reverser = 0;
    switch (status) {
    case 0b10: // 前進
        reverser = INT16_MAX;
        log_d("Reverser: F");
        break;
    case 0b01: // 後退
        reverser = INT16_MIN;
        log_d("Reverser: R");
        break;
    case 0b11: // 中立
    default:
        reverser = 0;
        log_d("Reverser: N");
        break;
    }

    return reverser;
}

int16_t Mascon::getPowerNotchInt16() const {
    // 入力をビット列で取得
    uint8_t status = pinStatusStore.at(OUTPUT_VALUE).at(P_1) << 0 |
                     pinStatusStore.at(OUTPUT_VALUE).at(P_2) << 1 |
                     pinStatusStore.at(OUTPUT_VALUE).at(P_3) << 2 |
                     pinStatusStore.at(OUTPUT_VALUE).at(P_4) << 3 |
                     pinStatusStore.at(OUTPUT_VALUE).at(P_5) << 4;

    // ノッチ数
    uint8_t powerNotch = 0;
    switch (status) {
    case 0b00000: // P5
        powerNotch = 5;
        log_d("Power Notch: P5");
        break;
    case 0b10000: // P4
        powerNotch = 4;
        log_d("Power Notch: P4");
        break;
    case 0b11000: // P3
        powerNotch = 3;
        log_d("Power Notch: P3");
        break;
    case 0b11100: // P2
        powerNotch = 2;
        log_d("Power Notch: P2");
        break;
    case 0b11110: // P1
        powerNotch = 1;
        log_d("Power Notch: P1");
        break;
    case 0b11111: // P0
    default:
        powerNotch = 0;
        log_d("Power Notch: P0");
        break;
    }

    // 0からINT16_MAXまでの値に変換
    return static_cast<int16_t>(INT16_MAX * powerNotch / POWERNOTCH_MAX);
}

int16_t Mascon::getBrakeNotchInt16() const {
    // 入力をビット列で取得
    // 赤x：1
    // 青o：0
    uint8_t status = pinStatusStore.at(OUTPUT_VALUE).at(B_EB) << 0 |
                     pinStatusStore.at(OUTPUT_VALUE).at(B_NB) << 1 |
                     pinStatusStore.at(OUTPUT_VALUE).at(B_YB) << 2 |
                     pinStatusStore.at(OUTPUT_VALUE).at(B_1_5_6_7) << 3 |
                     pinStatusStore.at(OUTPUT_VALUE).at(B_1_2_3_6_7) << 4 |
                     pinStatusStore.at(OUTPUT_VALUE).at(B_3_4_5_6_7) << 5 |
                     pinStatusStore.at(OUTPUT_VALUE).at(B_7) << 6;

    // ノッチ数
    uint8_t brakeNotch = 0;
    switch (status) {
    case 0b1111111: // B0
        // B7-EB遷移時のチャタ対策
        if (prevBrakeNotch <= 2) {
            brakeNotch = prevBrakeNotch;
            log_d("Brake Notch not changed");
            break;
        }
        brakeNotch = 0;
        log_d("Brake Notch: B0");
        break;
    case 0b1111011: // YB
        brakeNotch = 1;
        log_d("Brake Notch: YB");
        break;
    case 0b1100101: // B1
        brakeNotch = 2;
        log_d("Brake Notch: B1");
        break;
    case 0b1101101: // B2
        brakeNotch = 3;
        log_d("Brake Notch: B2");
        break;
    case 0b1001101: // B3
        brakeNotch = 4;
        log_d("Brake Notch: B3");
        break;
    case 0b1011101: // B4
        brakeNotch = 5;
        log_d("Brake Notch: B4");
        break;
    case 0b1010101: // B5
        brakeNotch = 6;
        log_d("Brake Notch: B5");
        break;
    case 0b1000101: // B6
        brakeNotch = 7;
        log_d("Brake Notch: B6");
        break;
    case 0b0000101: // B7
        brakeNotch = 8;
        log_d("Brake Notch: B7");
        break;
    default:
        // B7-EB遷移時のチャタ対策
        if (prevBrakeNotch) {
            brakeNotch = prevBrakeNotch;
            log_d("Brake Notch not changed");
            break;
        }
        // YB-B1遷移時のチャタ対策
        if (prevBrakeNotch <= 2 || (status & 0b1000011 == 0b0000000)) {
            brakeNotch = prevBrakeNotch;
            log_d("Brake Notch not changed");
            break;
        }
    case 0b1111110: // EB
        brakeNotch = 9;
        log_d("Brake Notch: EB");
        break;
    }

    // 前回のブレーキノッチの値を保存
    if (brakeNotch != prevBrakeNotch) {
        prevBrakeNotch = brakeNotch;
    }

    // 0からINT16_MAXまでの値に変換
    return static_cast<int16_t>(INT16_MAX * brakeNotch / BRAKENOTCH_MAX);
}

uint32_t Mascon::getButtonInt32() const {
    // 入力をビット列で取得
    uint32_t status = pinStatusStore.at(OUTPUT_VALUE).at(SW_KEY) << 0 |
                      pinStatusStore.at(OUTPUT_VALUE).at(SW_ZT) << 1 |
                      pinStatusStore.at(OUTPUT_VALUE).at(SW_GK) << 2 ;

    // 0からINT16_MAXまでの値に変換
    return static_cast<uint32_t>(status);
}
#pragma endregion
