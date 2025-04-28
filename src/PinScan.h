#pragma once
#ifndef PINSCAN_H
#define PINSCAN_H

#include "settings.h"
#include <array>

using PinNumMatrix =
    std::array<std::array<gpio_num_t, Settings::Input::ROW_COLUMN_COUNT>,
               Settings::Input::MatrixIndex_MAX>;
using ValNumMatrix =
    std::array<std::array<bool, Settings::Input::ROW_COLUMN_COUNT>,
               Settings::Input::ROW_COLUMN_COUNT>;

/// @brief ピンをスキャンするタスク
/// @param pvParameters
void PinScanTask(void *pvParameters);

#endif // PINSCAN_H
