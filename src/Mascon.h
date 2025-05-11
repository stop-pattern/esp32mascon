#pragma onece

#include "settings.h"
#include <array>

class Mascon {
  private:
    /**
     * @brief 前回のブレーキノッチの値
     * @note 0からBRAKENOTCH_MAXまでの値
     */
    mutable uint8_t prevBrakeNotch;

    // GPIOピンの状態を格納する配列
    std::array<std::array<bool, Settings::Pins::PINNAME_MAX>, Settings::Pins::ARRAYNAME_MAX> pinStatusStore;

    // ノッチ最大値
    constexpr static uint8_t POWERNOTCH_MAX = 5;
    // ブレーキ最大値（抑速・非常含む）
    constexpr static uint8_t BRAKENOTCH_MAX = 9;

  public:
    /**
     * @brief コンストラクタ
     */
    Mascon();

    /**
     * @brief デストラクタ
     */
    ~Mascon();

    /**
     * @brief ピンの初期化
     */
    void setupPins();

    /**
     * @brief ピンのスキャン
     * @return スキャン後の状態変化有無
     */
    bool samplingPins();

    /**
     * @brief レバーサーの状態を取得
     * @return レバーサーの状態
     * @note 前進：INT16_MAX、後進：INT16_MIN、中立：0
     */
    int16_t getReverserInt16() const;

    /**
     * @brief パワーノッチの状態を取得
     * @return パワーノッチの状態
     * @note INT16_MINからINT16_MAXまでの値に変換
     */
    int16_t getPowerNotchInt16() const;

    /**
     * @brief ブレーキノッチの状態を取得
     * @return ブレーキノッチの状態
     * @note -INT16_MINからINT16_MAXまでの値に変換
     */
    int16_t getBrakeNotchInt16() const;

    /**
     * @brief ボタンの状態を取得
     * @return ボタンの状態
     * @note 0からUINT32_MAXまでの値に変換
     */
    uint32_t getButtonInt32() const;
};
