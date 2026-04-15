// CommModule.cpp — 空実装（議論後に埋める）
#include "CommModule.h"
#include "SystemData.h"

CommModule::CommModule(const CommConfig& config) : _config(config) {}

bool CommModule::init() {
    // 通信方式が決まり次第，実装する
    return true;
}

void CommModule::updateInput(SystemData& data) {
    // 受信したデータを data.comm に反映する
    (void)data;
}

void CommModule::updateOutput(SystemData& data) {
    // data.comm の送信要求を処理する
    (void)data;
}

void CommModule::deinit() {
    // リソース解放が必要になったら実装する
}
