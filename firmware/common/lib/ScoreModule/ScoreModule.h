// ScoreModule.h — 楽譜データモジュール（スケルトン）
// 楽譜データ形式（JSON / 独自バイナリ等）は議論後に確定する。
#pragma once
#include <Arduino.h>
#include "IModule.h"

struct SystemData;

// 楽譜モジュールの設定
struct ScoreConfig {
    uint16_t bpm = 120;          // テンポ（暫定）
    uint8_t trackIndex = 0;      // このノードが担当する楽譜トラック番号
};

// 楽譜モジュールが SystemData に書き込むデータ
struct ScoreData {
    uint32_t currentStep = 0;    // 現在の演奏ステップ
    uint16_t currentNote = 0;    // 現在鳴らすべき音（MIDIノート番号想定）
    bool isPlaying = false;      // 再生中フラグ
};

class ScoreModule : public IModule {
public:
    explicit ScoreModule(const ScoreConfig& config);

    bool init() override;
    void updateInput(SystemData& data) override;

private:
    ScoreConfig _config;
};
