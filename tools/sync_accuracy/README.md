# sync_accuracy — 同期精度測定

5ノードから取得したタイムスタンプ付きログから，楽器間のタイミング誤差（遅延・ジッタ）を集計する。

## 想定入力

- 各ノードから収集した `events.csv`（列: `node_id, timestamp_ms, event_type`）

## 想定出力

- ペアワイズの平均遅延
- ジッタ（標準偏差）
- ヒストグラム / 箱ひげ図（画像）

## 実装

未実装。Python + `pandas` + `matplotlib` を想定。
