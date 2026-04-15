# hardware — ハードウェア資料

回路図・配線図・部品表・データシートを置くディレクトリ。

## 構成

| ディレクトリ | 内容 |
|---|---|
| `schematics/` | 回路図（KiCad 想定。`.kicad_sch` / `.kicad_pro` / `.kicad_pcb` 等） |
| `wiring/` | 配線図（Fritzing / 画像） |
| `datasheets/` | 使用部品のデータシート PDF |

## 部品表

[parts_list.md](parts_list.md) を参照。

## ガイドライン

- 大きいバイナリ（PDF・画像）は Git LFS 導入検討
- 回路図変更時は該当 PR の description にビューワで開いたスクリーンショットを添付すると分かりやすい
