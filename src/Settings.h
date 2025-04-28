#pragma once

#include <cstdint>
#include <driver/gpio.h>

/// @brief 設定を格納する名前空間
namespace Settings {

/// @brief USB関連
namespace USB {
/// @brief ベンダーID
/// @note default: 0x303A
/// @note VID/PID is from V-USB
constexpr uint16_t VID = 0x16c0;

/// @brief プロダクトID
/// @note default: 0x1001
/// @note VID/PID is from V-USB
constexpr uint16_t PID = 0x005df;

/// @brief シリアル番号
/// @note meaning: trial
constexpr const char *SERIAL_NUMBER = "T0001";

/// @brief ファームウェアのバージョン
constexpr uint16_t FIRMWARE_VERSION = 0x100;

/// @brief USBのバージョン
constexpr uint16_t USB_VERSION = 0x0200;

/// @brief USBの電源電流
constexpr uint16_t USB_POWER = 0x500;

/// @brief WebUSBの設定
constexpr bool WEB_USB = true;

/// @brief プロダクト名
constexpr const char *PRODUCT_NAME = "ESP32S3 USB Gamepad";

/// @brief メーカー名
/// @note Email address is required to use V-USB's VID/PID
constexpr const char *MANUFACTURER_NAME =
    "stop-pattern: contact@hollyelectric.net";
} // namespace USB


/// @brief ゲームパッドのインターフェース
namespace Interface {
    /// @brief Number of available axes
    constexpr size_t AXIS = 8;

    /// @brief Number of available push switches
    constexpr size_t BUTTON = 32;

    /// @brief Number of available hat switches
    constexpr size_t HAT = 4;
} // namespace Interface


/// @brief GPIOのピン
// todo: ピン番号の初期値を決める
namespace Pins {
/// @brief 0列目
/// @details output(open drain))
/// @note 0/Hi-Z
constexpr gpio_num_t ROW0 = GPIO_NUM_0;

/// @brief 1列目
/// @details output(open drain))
/// @note 0/Hi-Z
constexpr gpio_num_t ROW1 = GPIO_NUM_1;

/// @brief 2列目
/// @details output(open drain))
/// @note 0/Hi-Z
constexpr gpio_num_t ROW2 = GPIO_NUM_2;

/// @brief 3列目
/// @details output(open drain))
/// @note 0/Hi-Z
constexpr gpio_num_t ROW3 = GPIO_NUM_3;

/// @brief 4列目
/// @details output(open drain))
/// @note 0/Hi-Z
constexpr gpio_num_t ROW4 = GPIO_NUM_4;

/// @brief 5列目
/// @details output(open drain))
/// @note 0/Hi-Z
constexpr gpio_num_t ROW5 = GPIO_NUM_5;

/// @brief 0行目
/// @details input(pullup)
/// @note default: 1
constexpr gpio_num_t COL0 = GPIO_NUM_6;

/// @brief 1行目
/// @details input(pullup)
/// @note default: 1
constexpr gpio_num_t COL1 = GPIO_NUM_7;

/// @brief 2行目
/// @details input(pullup)
/// @note default: 1
constexpr gpio_num_t COL2 = GPIO_NUM_8;

/// @brief 3行目
/// @details input(pullup)
/// @note default: 1
constexpr gpio_num_t COL3 = GPIO_NUM_9;

/// @brief 4行目
/// @details input(pullup)
/// @note default: 1
constexpr gpio_num_t COL4 = GPIO_NUM_10;

/// @brief 5行目
/// @details input(pullup)
/// @note default: 1
constexpr gpio_num_t COL5 = GPIO_NUM_11;
} // namespace Pins


/// @brief 入力GPIOのピンの設定
namespace Input {
    /// @brief Number of available buttons switches
    constexpr size_t SWITCH = Interface::BUTTON + Interface::HAT;

    /// @brief 
    // constexpr size_t MatrixIndex_MAX = 6;

    /// @brief 行/列の長さ
    constexpr size_t ROW_COLUMN_COUNT = 6;

    /// @brief 行/列のインデックス
    enum MatrixIndex : size_t {
        COLUMN,
        ROW,
        MatrixIndex_MAX
    };
} // namespace Input

} // namespace Settings
