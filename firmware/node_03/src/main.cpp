// main.cpp — node_03 エントリーポイント
// 3フェーズ実行モデル: 入力 → ロジック → 出力
//
// このファイルは「骨格のみ」。実際のモジュール構成はチーム内の議論で決まったら
// 下記の inputModules[] / outputModules[] に追加していく。
#include <Arduino.h>
#include "SystemData.h"
#include "ProjectConfig.h"
#include "ModuleTimer.h"

// ===== システムデータ =====
SystemData systemData;

// ===== モジュールインスタンス =====
// 共通モジュール（雛形）
CommModule  commModule(COMM_CONFIG);
SyncModule  syncModule(SYNC_CONFIG);
ScoreModule scoreModule(SCORE_CONFIG);

// ===== モジュール配列（並び順 = 実行順） =====
IModule* inputModules[] = {
    &commModule,
    &syncModule,
    &scoreModule,
};
const int INPUT_COUNT = sizeof(inputModules) / sizeof(inputModules[0]);

IModule* outputModules[] = {
    &commModule,  // 全データ確定後に送信
};
const int OUTPUT_COUNT = sizeof(outputModules) / sizeof(outputModules[0]);

// ===== ロジックフェーズ =====
void applyPattern(SystemData& data) {
    // ここに「入力から出力を決めるロジック」を書く。
    // 例: data.sync.beatCount を見て data.score.currentNote を決める など。
    (void)data;
}

// ===== モジュール初期化ヘルパ =====
static void initModules() {
    IModule* allModules[] = {
        &commModule,
        &syncModule,
        &scoreModule,
    };
    const int ALL_COUNT = sizeof(allModules) / sizeof(allModules[0]);
    for (int i = 0; i < ALL_COUNT; i++) {
        if (!allModules[i]->init()) {
            // Serial.printf は一部ボード（Uno R4 等の UART クラス）で未実装のため使わない
            Serial.print("[System] Module ");
            Serial.print(i);
            Serial.println(": init failed, disabled");
            allModules[i]->enabled = false;
        }
    }
}

// ===== セットアップ =====
void setup() {
    Serial.begin(115200);
    Serial.println("[System] node_03 起動");

    // 共有バス初期化はここで呼ぶ（バスを使うモジュールができたら追加する）
    // 例: Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

    initModules();

    Serial.println("[System] node_03 起動完了");
}

// ===== メインループ =====
void loop() {
    // 1. 入力フェーズ
    for (int i = 0; i < INPUT_COUNT; i++) {
        if (inputModules[i]->enabled) {
            inputModules[i]->updateInput(systemData);
        }
    }

    // 2. ロジックフェーズ
    applyPattern(systemData);

    // 3. 出力フェーズ
    for (int i = 0; i < OUTPUT_COUNT; i++) {
        if (outputModules[i]->enabled) {
            outputModules[i]->updateOutput(systemData);
        }
    }
}
