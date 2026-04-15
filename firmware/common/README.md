# firmware/common — 全ノード共有コード

このディレクトリは5ノード（`node_01` ～ `node_05`）が共通で使うファームウェアコードを置く場所。

## 構成

| パス | 内容 |
|---|---|
| `lib/ModuleCore/` | `IModule` / `ModuleTimer` — **変更禁止**（EMAから流用） |
| `lib/CommModule/` | ノード間通信モジュール（スケルトン） |
| `lib/SyncModule/` | 同期アルゴリズムモジュール（スケルトン） |
| `lib/ScoreModule/` | 楽譜データモジュール（スケルトン） |

詳しくは [lib/README.md](lib/README.md) を参照。

## 各ノードからの参照方法

各 `firmware/node_XX/platformio.ini` で以下を設定することで参照している：

```ini
lib_extra_dirs = ../common/lib
build_flags = -I include
```

PIO は `lib_extra_dirs` 配下の各サブディレクトリを自動でインクルードパスに追加する。
