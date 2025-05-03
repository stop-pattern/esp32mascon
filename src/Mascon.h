#pragma onece

#include "settings.h"
#include <array>

class Mascon {
  private:
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
    void setupPins() const;

    /**
     * @brief ピンのスキャン
     * @return スキャン後の状態変化有無
     */
    bool samplingPins();

    /**
     * @brief レバーサーの状態を取得
     * @return レバーサーの状態
     * @note 前進：INT32_MAX、後進：INT32_MIN、中立：0
     */
    int32_t getReverserInt32() const;

    /**
     * @brief パワーノッチの状態を取得
     * @return パワーノッチの状態
     * @note INT32_MINからINT32_MAXまでの値に変換
     */
    int32_t getPowerNotchInt32() const;

    /**
     * @brief ブレーキノッチの状態を取得
     * @return ブレーキノッチの状態
     * @note -INT32_MINからINT32_MAXまでの値に変換
     */
    int32_t getBrakeNotchInt32() const;
};
