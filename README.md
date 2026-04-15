# hackathon-template

千葉工業大学 情報工学科「ハッカソン1」向け，複数Arduinoチーム開発用のテンプレートリポジトリ。

Arduino 5台を使ったオーケストラシステム（楽器間同期演奏）を想定して作成されているが，特定テーマに縛られない汎用的な雛形として使える。

## 特徴

- PlatformIO (VSCode) によるArduinoファームウェア構成
- 5ノード並列開発（`firmware/node_01` ～ `node_05`）
- 共有ライブラリをモノレポ構成（`firmware/common/lib/`）で管理，全ノードが `lib_extra_dirs` で参照
- LaTeX 報告書（`report/`）＋ DevContainer による統一コンパイル環境
- GitHub Actions による LaTeX 自動ビルド＋PDF配信
- IModule / 3フェーズ実行モデル（`takushio2525/Embedded-Module-Architecture` 準拠）

## クイックスタート（このテンプレートから新しいリポジトリを作る）

1. GitHub のリポジトリページで「**Use this template**」→「Create a new repository」
2. ローカルに clone

   ```bash
   git clone https://github.com/<あなたの組織名>/<新しいリポジトリ名>.git
   cd <新しいリポジトリ名>
   ```

3. `CONTRIBUTING.md` を読み，チームのブランチ戦略・レビュー規約に合意
4. `firmware/node_01/` を VSCode で開いて `pio run` が通るか確認
5. `report/` を Dev Container で開いて `latexmk main.tex` が通るか確認

## ディレクトリ構成

```
.
├── firmware/          # Arduinoファームウェア（PlatformIO）
│   ├── common/lib/    # 全ノード共通モジュール（分担開発対象）
│   └── node_01〜05/   # 各ノードのPIOプロジェクト
├── processing/        # Processing スケッチ（音源・可視化）
├── hardware/          # 回路図・配線図・部品表
├── scores/            # 楽譜データ（JSON等）
├── tools/             # 評価・測定スクリプト
├── meetings/          # 議事録・WBS・ガントチャート
├── docs/              # 設計ドキュメント・ADR
├── report/            # LaTeX 報告書
└── .devcontainer/     # LaTeX コンパイル環境
```

## ビルド

### ファームウェア

```bash
cd firmware/node_01
pio run
```

### 報告書

```bash
cd report
docker run --rm -v "$(pwd):/workspace" -w /workspace ghcr.io/paperist/texlive-ja:debian latexmk main.tex
```

または VSCode で `report/` を Dev Container として開き，LaTeX Workshop でビルド。

## 開発ルール

- `CONTRIBUTING.md` のブランチ戦略・commit 規約・レビュー規約に従うこと
- 共通モジュール（`firmware/common/lib/`）の変更 PR は最低2名レビュー必須
- コード規則は [Embedded-Module-Architecture](https://github.com/takushio2525/Embedded-Module-Architecture) に準拠

## ライセンス

チームで合意した上で後から決定。
