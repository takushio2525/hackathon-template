// ExampleLibrary.h — 共通ライブラリの最小サンプル
//
// このファイルは「複数のマイコンで同じコードを共有したいとき、
// どういう形でライブラリを書けばよいか」の一例です。
//
// 使い方:
//   1. platformio.ini に lib_extra_dirs = ../common/lib を追加
//   2. #include "ExampleLibrary.h"
//
// 必要なくなったら ExampleLibrary/ ごと削除して、
// 自分たちのライブラリ名のディレクトリを新しく作ってください。
#pragma once

#include <stdint.h>

// --- ユーティリティ関数 ---

// 2つの整数を足した値を返す
int32_t exampleAdd(int32_t a, int32_t b);

// 値を min〜max の範囲に収める（センサ値の正規化などに使える）
int32_t exampleClamp(int32_t value, int32_t minVal, int32_t maxVal);

// --- 構造体の例 ---

// ノード間でデータをやり取りするときのパケット構造の例
// 実際のプロジェクトでは用途に合わせて書き換える
struct ExamplePacket {
    uint8_t  senderId;   // 送信元ノードの ID（1〜5）
    uint8_t  command;    // コマンド種別
    int16_t  value;      // データ値
};

// パケットを初期化する
ExamplePacket exampleCreatePacket(uint8_t senderId, uint8_t command, int16_t value);
