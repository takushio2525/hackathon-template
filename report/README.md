# report — LaTeX 報告書

提出用の報告書を LaTeX で書くためのディレクトリ。

**GitHub Actions により、`.tex` を push するだけで PDF が自動生成・コミットされる。**
Docker を手元に入れなくても最新 PDF がリポジトリ上で確認できる。

## 構成

```
report/
├── main.tex             # メインファイル（\input で各章を読み込む）
├── sections/
│   ├── 01_introduction.tex  # はじめに
│   ├── 02_purpose.tex       # 目的
│   ├── 03_system_design.tex # システム設計
│   ├── 04_implementation.tex# 実装
│   ├── 05_evaluation.tex    # 評価
│   ├── 06_conclusion.tex    # まとめ
│   └── 99_appendix.tex      # 付録（LaTeX チートシート）
├── fig/                 # 図・画像置き場
├── refs.bib             # 参考文献
├── jex.cls / jex.sty    # 大学指定スタイル
├── plistings.sty        # 日本語コードの文字幅補正
└── .latexmkrc           # latexmk 設定
```

## 書き方

1. `sections/` の各 `.tex` ファイルにチームの内容を書く
2. コミット → push
3. **GitHub Actions が自動で PDF を生成・コミットする**
4. `report/main.pdf` を GitHub 上で開いて確認

## 手元でコンパイルする場合

### Dev Container（推奨）

VSCode で本リポジトリを開き、`Reopen in Container` を選択。
LaTeX Workshop が自動でビルドする。

### Docker を直接使う

```bash
cd report
docker run --rm -v "$(pwd):/workspace" -w /workspace \
  ghcr.io/paperist/texlive-ja:debian latexmk main.tex
```

## 注意

- push すると Actions が PDF を自動コミットするので、**push 後・次の作業前に必ず `git pull`**
- 図は `fig/` ディレクトリに配置する（推奨形式: PDF / PNG）
- LaTeX の基本記法は `99_appendix.tex`（付録）にチートシートとして載っている
