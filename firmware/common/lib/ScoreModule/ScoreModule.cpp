// ScoreModule.cpp — 空実装（議論後に埋める）
#include "ScoreModule.h"
#include "SystemData.h"

ScoreModule::ScoreModule(const ScoreConfig& config) : _config(config) {}

bool ScoreModule::init() {
    return true;
}

void ScoreModule::updateInput(SystemData& data) {
    // 現在時刻／拍カウンタから，鳴らすべき音を data.score に書き込む
    (void)data;
}
