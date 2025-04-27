#pragma once

#include <cstdint>

namespace Settings {
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

} // namespace Settings
