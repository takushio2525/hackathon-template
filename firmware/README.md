# firmware — Arduino ファームウェア

5ノード（`node_01` ～ `node_05`）の PlatformIO プロジェクト群と，全ノード共有コード（`common/`）。

## ノード一覧（役割分担表）

担当と役割が決まり次第，このテーブルを更新する。

| ノード | 役割（例） | ハードウェア | 担当者 | 備考 |
|---|---|---|---|---|
| node_01 | 未定（指揮者 / 楽器1 など） | 未定 | 未定 | |
| node_02 | 未定 | 未定 | 未定 | |
| node_03 | 未定 | 未定 | 未定 | |
| node_04 | 未定 | 未定 | 未定 | |
| node_05 | 未定 | 未定 | 未定 | |

## 構造（各ノード共通）

```
node_XX/
├── platformio.ini      # lib_extra_dirs = ../common/lib
├── include/
│   ├── SystemData.h    # このノードが使う Data の集約
│   └── ProjectConfig.h # このノードのピン / Config インスタンス
├── src/
│   └── main.cpp        # 3フェーズループの骨格
├── lib/                # このノード固有モジュール（空）
└── test/               # Unity テスト置き場（空）
```

## ビルド方法

```bash
# 例: node_01 をビルド
cd firmware/node_01
pio run                 # ビルドのみ
pio run -t upload       # 書き込み
pio device monitor      # シリアルモニタ
```

全ノードを一括ビルドしたい場合は `.github/workflows/pio-build.yml` を有効化し，Actions からまとめて実行する（現状は同ワークフロー未同梱。必要になったら追加）。

## 共通モジュール

[common/lib/README.md](common/lib/README.md) を参照。
