# common/lib — 全ノード共通モジュール

全ノード（`node_01` ～ `node_05`）が共有するモジュール層。各ノードの `platformio.ini` に `lib_extra_dirs = ../common/lib` を設定しているため，ここのコードを触ると**全ノード**に影響することに注意。

## モジュール担当表

議論で決まり次第，担当者名を埋めること。

| モジュール | 配置 | 担当者 | 概要 | 状態 |
|---|---|---|---|---|
| ModuleCore | `ModuleCore/` | 共通（変更禁止） | `IModule.h` / `ModuleTimer.h`（Embedded-Module-Architectureから流用） | 完成 |
| CommModule | `CommModule/` | 未定 | ノード間通信（BLE / ESP-NOW / RS-485 等） | 空スケルトン |
| SyncModule | `SyncModule/` | 未定 | 楽器間タイミング同期アルゴリズム | 空スケルトン |
| ScoreModule | `ScoreModule/` | 未定 | 楽譜データ構造・パーサ | 空スケルトン |

## モジュールの追加手順

1. `firmware/common/lib/XxxModule/` を作成（`Xxx` は PascalCase）
2. `XxxModule.h`（宣言）と `XxxModule.cpp`（実装）を分離して配置
3. `XxxConfig` / `XxxData` 構造体を `.h` で定義
4. `IModule` を継承し，`init()` / `updateInput()` / `updateOutput()` / `deinit()` のうち必要なものをオーバーライド
5. 本 README の担当表に追記
6. 全ノードの `include/SystemData.h` / `ProjectConfig.h` に対応する型・Configインスタンスを追加
7. PR を作成（共通モジュールは最低2名レビュー）

## コード規則

[Embedded-Module-Architecture](https://github.com/takushio2525/Embedded-Module-Architecture) の `CLAUDE.md` に準拠する。主要ルールのみ抜粋：

- `SystemData` はヘッダーで前方宣言のみ（`.cpp` でインクルード）
- ピン番号は `Config` 構造体経由でアクセス
- `delay()` の代わりに `ModuleTimer` を使用
- ログは `[モジュール名] メッセージ` の形式
