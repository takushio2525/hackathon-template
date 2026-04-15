// ProjectConfig.h — node_03 固有のピン定義と Config インスタンス（テンプレのみ）
// 共有バス（SPI/I2C）のピンはここに constexpr で置く。
// モジュール固有のピン（CS/信号ピン等）は Config インスタンスのリテラルに直書きする。
#pragma once

#include "CommModule.h"
#include "SyncModule.h"
#include "ScoreModule.h"

// ===== 共有バスピン（ボード確定後に実値を入れる） =====
// 例: constexpr int I2C_SDA_PIN = 21;
// 例: constexpr int I2C_SCL_PIN = 22;

// ===== 各モジュールの Config インスタンス =====
// nodeId はこのノードの識別番号（node_03 → 2）
inline const CommConfig COMM_CONFIG = {
    .nodeId = 2,
    .baudrate = 115200,
};

inline const SyncConfig SYNC_CONFIG = {
    .intervalMs = 1000,
    .isConductor = false,  // node_03 を指揮者にする場合は true に変更
};

inline const ScoreConfig SCORE_CONFIG = {
    .bpm = 120,
    .trackIndex = 2,  // node_03 は楽譜トラック0を担当
};
