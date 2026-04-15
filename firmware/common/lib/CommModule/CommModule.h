// CommModule.h — ノード間通信モジュール（スケルトン）
// 通信方式（BLE / ESP-NOW / RS-485 等）は議論後に確定する。
// 本ヘッダは IModule インターフェースに合わせた空実装の骨だけを提供する。
#pragma once
#include <Arduino.h>
#include "IModule.h"

struct SystemData;

// 通信モジュールの設定
struct CommConfig {
    uint8_t nodeId = 0;          // 自ノードのID（0〜4を想定）
    uint32_t baudrate = 115200;  // シリアル系の場合の通信速度
    // 通信方式が決まり次第，必要な設定を追加する
};

// 通信モジュールが SystemData に書き込むデータ
struct CommData {
    bool isConnected = false;    // 通信確立状態
    uint32_t rxCount = 0;        // 受信パケット数
    uint32_t txCount = 0;        // 送信パケット数
    // 受信メッセージのバッファなどは実装時に追加
};

class CommModule : public IModule {
public:
    explicit CommModule(const CommConfig& config);

    bool init() override;
    void updateInput(SystemData& data) override;
    void updateOutput(SystemData& data) override;
    void deinit() override;

private:
    CommConfig _config;
};
