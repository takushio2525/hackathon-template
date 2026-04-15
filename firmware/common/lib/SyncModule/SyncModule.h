// SyncModule.h — ノード間同期モジュール（スケルトン）
// 同期方式（LED点滅 / 音 / ジェスチャ / 時刻同期など）は議論後に確定する。
#pragma once
#include <Arduino.h>
#include "IModule.h"

struct SystemData;

// 同期モジュールの設定
struct SyncConfig {
    uint32_t intervalMs = 1000;  // 基本同期周期（ms）
    bool isConductor = false;    // 指揮者ノードかどうか
};

// 同期モジュールが SystemData に書き込むデータ
struct SyncData {
    uint32_t beatCount = 0;      // 直近の拍カウンタ
    uint32_t driftMs = 0;        // 推定時刻ずれ（ms）
    bool inSync = false;         // 同期が取れているか
};

class SyncModule : public IModule {
public:
    explicit SyncModule(const SyncConfig& config);

    bool init() override;
    void updateInput(SystemData& data) override;
    void updateOutput(SystemData& data) override;

private:
    SyncConfig _config;
};
