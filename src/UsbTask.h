#pragma once
#ifndef USBTASK_H
#define USBTASK_H

/// @brief 各軸分解能8bitのテスト
/// @note デモ用関数
void testAxises8();

/// @brief 各軸分解能16bitのテスト
/// @note デモ用関数
void testAxises16();

/// @brief キー入力のテスト
/// @note デモ用関数
void testKeys();

/// @brief ハットスイッチのテスト
/// @note デモ用関数
void testHats();

/// @brief USBを制御するタスク
/// @param pvParameters 
void UsbTask(void *pvParameters);

#endif // USBTASK_H
