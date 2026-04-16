# hackathon-template

ハッカソン・チーム開発用のテンプレートリポジトリ。

このテンプレートは「**共同開発のためのフォルダ構成と進め方の教材**」として作られている。
使うテーマ（音楽・ゲーム・ロボット・Web アプリ…）は問わない。必要なフォルダだけを
使い、いらないフォルダは**丸ごと削除してよい**。

---

## 🚨 一番大事なこと

> **コード編集を始める前に、必ず `git pull` でリポジトリを最新化してください。**
>
> このリポジトリは `.tex` ファイルが更新されると GitHub Actions が PDF を
> 自動でコミットする仕組みが入っています。**自分が push した直後でも**
> リモートには自分が知らないコミットが増えていることがあります。
> 作業の最初に pull、これを徹底してください。
>
> 詳しい理由と具体的な手順は [CONTRIBUTING.md](CONTRIBUTING.md) を読んでください。

---

## このテンプレートの考え方

- 各フォルダは「**こう分担すると開発がしやすい**」という**例**
- 中身のコードは空 or 最小サンプル。**自分たちのプロジェクトに合わせて書き換える**
- いらないフォルダは削除してよい（`firmware/`、`processing/`、`hardware/`、`assets/` など、テーマ次第で不要になる）
- 各フォルダの `README.md` に「何のフォルダか・どう使うか・不要なら削除OK」が書いてあるので、迷ったらまずそれを読む

---

## クイックスタート

### Step 1. このテンプレートから新しいリポジトリを作る

1. GitHub でこのテンプレートリポジトリを開く
2. 右上の緑の **「Use this template」** → **「Create a new repository」** をクリック
3. Owner（組織 or 個人）とリポジトリ名を入力 → **「Create repository」**

### Step 2. 手元に clone する

```bash
cd ~/Documents               # 好きな場所に移動
git clone https://github.com/<あなたの組織名>/<新しいリポジトリ名>.git
cd <新しいリポジトリ名>
```

### Step 3. チームでルールに合意する

[CONTRIBUTING.md](CONTRIBUTING.md) をチーム全員で読み、ブランチ戦略と
コミットメッセージ規約に合意する。

### Step 4. 不要なフォルダを削除する

テーマ・技術スタックに合わせて**使わないフォルダを削除**する。
各フォルダの `README.md` の末尾に「不要な班は丸ごと削除してよい」と
書いてあるので、チームで相談して決める。

例：
- Web アプリ中心 → `firmware/`, `hardware/`, `processing/`, `assets/` を削除
- Arduino 中心 → `processing/` は残すかどうかチーム判断、`assets/` は設定値置き場に流用
- ゲーム中心 → `firmware/`, `hardware/` を削除、`assets/` は「マップ・シナリオ置き場」に流用

### Step 5. 自分たちのコードを書き始める

- WBS・ガントチャートの記入 → [`meetings/`](meetings/)
- 設計ドキュメント → [`docs/`](docs/)
- 実装 → 各フォルダの README を読んで、自分たちのプロジェクトに合うフォルダ構成に書き換えていく
- 報告書 → [`report/`](report/)（LaTeX）

---

## ディレクトリ構成

| ディレクトリ | 用途 | 例として示していること |
|---|---|---|
| [`firmware/`](firmware/) | マイコン用ファームウェア | **複数マイコンを分担開発**するときの構成（PlatformIO、node_01〜05） |
| [`processing/`](processing/) | PC 側のサブシステム | 本体とは別言語で GUI・可視化を作る場合の置き場 |
| [`hardware/`](hardware/) | 回路図・配線図・部品表 | ハードを使うときの資料一式の管理例 |
| [`assets/`](assets/) | プロジェクト固有のデータ | マップ・シナリオ・設定ファイル・テストデータなどの置き場 |
| [`tools/`](tools/) | 補助スクリプト | ベンチマーク・解析スクリプトの置き場 |
| [`docs/`](docs/) | 設計ドキュメント・ADR | 設計判断を残すドキュメントの例 |
| [`meetings/`](meetings/) | 議事録・WBS・ガント | 進捗管理ドキュメントのテンプレ |
| [`report/`](report/) | LaTeX 報告書 | 提出用 PDF 報告書の雛形 |
| `.devcontainer/` | LaTeX コンパイル環境 | VSCode の Dev Container 設定 |
| `.github/` | PR / Issue テンプレ、GitHub Actions | 自動化の例 |
| `.vscode/` | VSCode 推奨拡張・設定 | エディタ環境の共有 |

---

## 自動ビルドについて

### LaTeX 報告書

`report/` 配下の `.tex` / `.bib` / `.sty` / `.cls` を**どのブランチでも**更新して
push すると、GitHub Actions が自動でコンパイルし、`report/main.pdf` を**同じ
ブランチへ自動コミット**する。手元で Docker を持っていなくても、**チームの誰か
が push すれば最新の PDF がリポジトリ上で見られる**。

- 自動コミットの差分が流れてくるので、**作業前に必ず `git pull`**
- PR では PDF は Artifact として Actions タブからダウンロードできる

### PlatformIO（Arduino ビルド）

`firmware/` の内容を push すると、全ノード（node_01〜05）のビルドが走る。
ビルドに失敗すると PR がブロックされる。

Arduino を使わない班は `.github/workflows/pio-build.yml` を削除してよい。

---

## 手元でのビルド

### ファームウェア（Arduino 使う班のみ）

VSCode に [PlatformIO 拡張](https://platformio.org/install/ide?install=vscode) を入れ、
`firmware/node_01/` をフォルダとして開く。または：

```bash
cd firmware/node_01
pio run
```

### LaTeX 報告書

VSCode で `.devcontainer/` を **「Reopen in Container」** で開くのが一番楽
（LaTeX 環境がすべて含まれている）。または Docker を直接使う：

```bash
cd report
docker run --rm -v "$(pwd):/workspace" -w /workspace \
  ghcr.io/paperist/texlive-ja:debian latexmk main.tex
```

---

## 開発ルール

[CONTRIBUTING.md](CONTRIBUTING.md) を参照。Git / 共同開発が初めての人向けに、
clone から PR、コンフリクト解消までを丁寧に書いてある。

---

## ライセンス

チームで合意した上で後から決定する。
