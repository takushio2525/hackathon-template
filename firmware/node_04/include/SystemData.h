// SystemData.h — node_04 が使う Data 構造体の集約（テンプレのみ）
// 各モジュールの Data 構造体を include して，SystemData にまとめる。
// このノードが使わないモジュールの Data はここに含めなくてよい。
#pragma once

#include "CommModule.h"   // CommData
#include "SyncModule.h"   // SyncData
#include "ScoreModule.h"  // ScoreData

struct SystemData {
    CommData  comm;
    SyncData  sync;
    ScoreData score;
    // このノード固有のデータをここに追加していく
    // 例: SpeakerData speaker; SensorData sensor; など
};
