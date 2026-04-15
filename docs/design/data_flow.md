# データフロー

システム全体のデータフロー図。決定後に Mermaid 等で更新する。

## 概要

```
[指揮者ノード(or 基準)] ──同期信号──▶ [楽器ノード1〜4]
                                       │
                                       ▼
                                    [Processing]
                                       │
                                       ▼
                                    [スピーカー]
```

## データ構造

- 各ノード内: `SystemData`（[firmware/node_XX/include/SystemData.h](../../firmware/node_01/include/SystemData.h)）
- ノード間: `CommModule` 経由のパケット（[protocol.md](protocol.md)）
- ノード ↔ Processing: シリアル or 無線

## フェーズ別フロー

1. **入力フェーズ**: 各モジュールが `SystemData` にセンサー値・受信データを書く
2. **ロジックフェーズ**: `applyPattern()` が入力を元に出力を決定
3. **出力フェーズ**: 各モジュールが `SystemData` から値を読んでハード制御
