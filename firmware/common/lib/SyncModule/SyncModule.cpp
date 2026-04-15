// SyncModule.cpp — 空実装（議論後に埋める）
#include "SyncModule.h"
#include "SystemData.h"

SyncModule::SyncModule(const SyncConfig& config) : _config(config) {}

bool SyncModule::init() {
    return true;
}

void SyncModule::updateInput(SystemData& data) {
    // 受信した同期信号を data.sync に反映する
    (void)data;
}

void SyncModule::updateOutput(SystemData& data) {
    // data.sync の情報を元に他ノードへ同期信号を送出する
    (void)data;
}
