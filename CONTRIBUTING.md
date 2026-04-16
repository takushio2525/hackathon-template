# コントリビューションガイド

このリポジトリで開発するときのルール集。**Git も共同開発もほぼ初めて**という
メンバーを想定して書いている。慣れている人は「ブランチ戦略」以降を斜め読みでOK。

---

## 🚨 一番大事なルール：作業前に必ず `git pull`

コード編集に取りかかる**前に**、ローカルのリポジトリを最新の状態に揃える。

#### ターミナルで操作する場合

```bash
git switch main      # main ブランチに移動
git pull             # リモート（GitHub）から最新を取り込む
```

#### VS Code で操作する場合

1. 左下のブランチ名をクリック → `main` を選んで切り替え
2. ステータスバーの **同期アイコン（🔄 循環矢印）** をクリック、またはコマンドパレット（`Ctrl+Shift+P` / macOS: `Cmd+Shift+P`）→ `Git: Pull` を実行

**忘れるとどうなるか**：

- Bさんが昨日 main に PR をマージした
- あなたはそれに気づかずに、古い main からブランチを切って作業
- PR を出すときに「謎のコンフリクト」が大量発生して解消に1時間…

GitHub Actions が PDF を自動コミットする仕組みも入っているので、
**自分が push した直後でも**リモートには自分が知らないコミットが増える
ことがある。「作業の最初に必ず pull」を徹底すること。

---

## 0. 最初のセットアップ（Git を初めて使う人向け）

### 0.1 Git のインストール

- macOS: `xcode-select --install` か Homebrew で `brew install git`
- Windows: [Git for Windows](https://gitforwindows.org/) をインストール
- Linux: `sudo apt install git` など

インストールできたか確認：

```bash
git --version
```

### 0.2 VS Code と推奨拡張機能のインストール

このリポジトリでは **VS Code** をエディタとして推奨している。

1. [VS Code 公式サイト](https://code.visualstudio.com/) からインストール
2. VS Code でこのリポジトリのフォルダを開く
3. 右下に「**推奨拡張機能をインストールしますか？**」と通知が出るので、**すべてインストール** を選択

手動で入れる場合は、サイドバーの「拡張機能」アイコン（四角が4つ）を開き、以下を検索してインストール：

| 拡張機能 | 用途 |
|---|---|
| **GitLens** (`eamodio.gitlens`) | Git の履歴・差分・ブランチ管理を GUI で操作 |
| **EditorConfig** | コーディングスタイルの自動統一 |
| **PlatformIO IDE** | Arduino 開発する班向け |
| **LaTeX Workshop** | 報告書（LaTeX）を書く人向け |

> このガイドでは Git 操作を **ターミナル** と **VS Code（GitLens）** の両方で説明する。
> どちらを使ってもよいが、慣れないうちは VS Code の GUI が分かりやすい。

### 0.3 名前とメールアドレスを登録（初回のみ）

commit の作者情報として使われる。GitHub に登録したアドレスを使うと、
GitHub 上であなたのアイコンが表示されて分かりやすい。

#### ターミナルで操作する場合

```bash
git config --global user.name "Your Name"
git config --global user.email "you@example.com"
```

#### VS Code で操作する場合

VS Code 内のターミナル（`` Ctrl+` `` で開く）で上記と同じコマンドを実行する。
Git の初期設定はコマンドで行う必要がある（GUI では設定できない）。

### 0.4 GitHub との認証

HTTPS で clone するなら、push のときに GitHub の**個人アクセストークン（PAT）**を
求められる。パスワードは使えないので注意。

- 参考: [GitHub: 個人アクセストークンの作成](https://docs.github.com/ja/authentication/keeping-your-account-and-data-secure/managing-your-personal-access-tokens)

より楽なのは **SSH 鍵** を登録する方法。一度設定すればパスワード不要になる。

- 参考: [GitHub: SSHでの接続](https://docs.github.com/ja/authentication/connecting-to-github-with-ssh)

---

## 1. リポジトリを手元に持ってくる（clone）

チーム用のリポジトリ URL をリーダーからもらって、手元にコピーする。

#### ターミナルで操作する場合

```bash
# 好きな場所に移動して
cd ~/Documents

# clone
git clone https://github.com/<組織名>/<リポジトリ名>.git
cd <リポジトリ名>
```

#### VS Code で操作する場合

1. コマンドパレット（`Ctrl+Shift+P` / macOS: `Cmd+Shift+P`）を開く
2. `Git: Clone` と入力して選択
3. リポジトリの URL（`https://github.com/<組織名>/<リポジトリ名>.git`）を貼り付けて Enter
4. 保存先フォルダを選ぶ → clone が始まる
5. 「クローンしたリポジトリを開きますか？」と聞かれるので **「開く」** を選択

---

## 2. ブランチ戦略

### 基本ルール

- `main` ブランチへ**直接 push は禁止**
- 機能追加・バグ修正は必ずブランチを切って作業する
- 作業が終わったら Pull Request（PR）を作って、レビューしてからマージ

### ブランチ名の付け方

種類 / 短い説明 の形式：

| 種類 | 例 |
|---|---|
| `feature/` | `feature/add-sensor-reading` |
| `fix/` | `fix/null-pointer-on-startup` |
| `docs/` | `docs/update-readme` |
| `refactor/` | `refactor/split-comm-module` |

- 英語でも日本語でもよいが、短く・内容が分かる名前にする
- スペースは使わない（`-` か `_` でつなぐ）

### ブランチの作り方

#### ターミナルで操作する場合

```bash
git switch main
git pull
git switch -c feature/my-task
```

#### VS Code で操作する場合

1. 左下のブランチ名（例: `main`）をクリック
2. 「**+ 新しいブランチの作成...**」を選択
3. ブランチ名（例: `feature/my-task`）を入力して Enter

> **注意**: 新しいブランチを作る前に、必ず `main` に切り替えて pull しておくこと。
> VS Code でも左下のブランチ名クリック → `main` 選択 → 同期アイコン（🔄）をクリックで pull できる。

### ブランチ切りのコツ

1. **必ず最新の main から切る**（上記の手順）
2. **1ブランチ = 1目的**（レビュー負担を減らす）
3. **長期間持たない**：1週間以上持つとコンフリクト地獄になる。大きい作業は
   途中で PR を分ける
4. **作業中に main が進んだら取り込む**：

   ターミナル：
   ```bash
   git fetch origin          # 最新情報を取得（ローカルは変わらない）
   git merge origin/main     # 自分のブランチに main を取り込む
   ```
   VS Code：コマンドパレット → `Git: Merge Branch...` → `origin/main` を選択

5. **マージされたブランチは消す**：

   ターミナル：
   ```bash
   git switch main
   git pull
   git branch -d feature/my-task   # ローカルのブランチを削除
   ```
   VS Code：コマンドパレット → `Git: Delete Branch...` → 削除するブランチを選択

---

## 3. 作業の流れ（add → commit → push → PR）

### 3.1 作業前の準備

#### ターミナルで操作する場合

```bash
git switch main
git pull
git switch -c feature/my-task
```

#### VS Code で操作する場合

1. 左下のブランチ名をクリック → `main` に切り替え
2. 同期アイコン（🔄）をクリックして pull
3. 再び左下のブランチ名をクリック → 「+ 新しいブランチの作成...」 → ブランチ名を入力

### 3.2 ファイルを編集する

VS Code でファイルを開いて編集する。

### 3.3 変更を確認する

#### ターミナルで操作する場合

```bash
git status       # どのファイルを変更したか
git diff         # 具体的にどう変わったか
```

#### VS Code で操作する場合

1. サイドバーの「**ソース管理**」アイコン（`Ctrl+Shift+G` / macOS: `Cmd+Shift+G`）をクリック
2. 「変更」セクションに変更されたファイルの一覧が表示される
3. ファイル名をクリックすると**差分（diff）** が表示される（左が変更前、右が変更後）

> GitLens を入れていると、エディタ上で各行の最終変更者・日時がインライン表示される。

### 3.4 ステージング（`git add`）

コミットしたいファイルだけを選ぶ。

#### ターミナルで操作する場合

```bash
git add path/to/file.c            # 特定のファイル
git add path/to/dir/              # ディレクトリ丸ごと
# git add -A や git add . は便利だが、意図しないファイル（.env 等）まで
# 含めがちなので、慣れるまではファイル名を直接指定するのが安全
```

#### VS Code で操作する場合

1. 「ソース管理」パネルを開く（`Ctrl+Shift+G`）
2. 「変更」セクションで、ステージしたいファイルの右側にある **「+」ボタン** をクリック
3. クリックしたファイルが「**ステージされている変更**」セクションに移動する
4. 間違えたら「ステージされている変更」のファイル右側の **「−」ボタン** で戻せる

> 全ファイルを一括ステージしたい場合は「変更」セクションのタイトル右側の「+」を押す。
> ただし `.env` 等を含めないよう注意。

### 3.5 コミット

#### ターミナルで操作する場合

```bash
git commit -m "[機能追加] センサ読み取り処理を追加"
```

#### VS Code で操作する場合

1. 「ソース管理」パネル上部の**メッセージ入力欄**にコミットメッセージを入力
   - 例: `[機能追加] センサ読み取り処理を追加`
2. **✓（チェックマーク）ボタン** をクリック、または `Ctrl+Enter`（macOS: `Cmd+Enter`）

コミットメッセージの書式は [#コミットメッセージ規約](#4-コミットメッセージ規約) を参照。

### 3.6 リモートに push

#### ターミナルで操作する場合

```bash
# 初回（ブランチを GitHub に作るとき）
git push -u origin feature/my-task

# 2回目以降
git push
```

#### VS Code で操作する場合

1. 「ソース管理」パネルの **「…」メニュー** → **「Push」** を選択
2. 初回は「リモートブランチがありません。公開しますか？」と聞かれるので **「OK」** を選択
3. または、ステータスバーの **↑ アイコン（雲マーク）** をクリックしても push できる

### 3.7 Pull Request を作る

1. GitHub のリポジトリページをブラウザで開く
2. 黄色いバナー「Compare & pull request」が出ているのでクリック
3. PR テンプレートが自動で入るので、埋めて「Create pull request」
4. レビュアーを指定（CONTRIBUTING のルールに合わせる）

> VS Code で **GitHub Pull Requests** 拡張（`GitHub.vscode-pull-request-github`）を入れると、
> VS Code 内から PR の作成・レビューもできる。

### 3.8 レビュー指摘に対応する

1. 同じブランチで編集 → ステージ → コミット → push（ターミナルでも VS Code でもOK）
2. PR のページが自動で更新される（コメントを書いて「Resolve conversation」）

### 3.9 マージ

- レビュー承認がついたらマージボタンを押す
- マージ後はローカルのブランチを消す（前述）

---

## 4. コミットメッセージ規約

`[種別] 変更内容の概要` の形式で書く。

| 種別 | 用途 |
|------|------|
| `[機能追加]` | 新機能の実装 |
| `[修正]` | バグ修正 |
| `[改善]` | 既存機能の改善・パラメータ調整など |
| `[リファクタ]` | コード整理（機能変更なし） |
| `[ドキュメント]` | ドキュメントのみの変更 |
| `[スタイル]` | 見た目・UI の変更 |

### コツ

- 機能単位で**細かく分割**する（無関係な変更を1コミットにまとめない）
- コードの変更と、そのコードに対応する README 更新は**同じコミット**に入れる
- 「なぜ」を意識する（「追加した」ではなく「〇〇のために追加した」の視点）

---

## 5. レビュー観点

PR のレビュー時は以下をチェックする。

### コード全般
- 命名規則に従っているか
- 不要なコメントアウト・`print` / `Serial.println` のデバッグ出力が残っていないか
- エラーケースが考慮されているか

### ドキュメント
- README に書いてある挙動と実装が一致しているか
- 設計判断が大きい変更の場合、`docs/decisions/` に ADR を追加したか

### CI
- GitHub Actions が全部成功しているか（❌ のままマージしない）

---

## 6. コンフリクト（衝突）の解消

マージ時に「conflict（衝突）」と出ることがある。2人が同じ行を別々に編集したときに起きる。

### ターミナルで解消する場合

```bash
# 自分のブランチで
git fetch origin
git merge origin/main
# → CONFLICT (content): ... と出たら

# 1. 対象ファイルを開くと、以下のようなマーカーが入っている
#    <<<<<<< HEAD
#    あなたの変更
#    =======
#    相手の変更
#    >>>>>>> origin/main

# 2. 正しい内容になるよう編集（マーカーは消す）

# 3. 直したファイルを add して commit
git add path/to/conflicted-file
git commit
```

### VS Code で解消する場合

1. ターミナルまたはコマンドパレットで merge を実行すると、コンフリクトが発生したファイルが「**ソース管理**」パネルの「**マージの変更**」セクションに表示される
2. コンフリクトしたファイルを開くと、該当箇所に色付きのハイライトとボタンが表示される：
   - **「現在の変更を取り込む（Accept Current Change）」** — 自分の変更を採用
   - **「入力側の変更を取り込む（Accept Incoming Change）」** — 相手（main）の変更を採用
   - **「両方の変更を取り込む（Accept Both Changes）」** — 両方残す
   - **「変更の比較（Compare Changes）」** — 差分を横並びで確認
3. 正しい内容に編集できたら、ファイルを保存
4. 「ソース管理」パネルで解消済みファイルの **「+」ボタン** でステージ
5. コミットメッセージを入力して ✓ ボタンでコミット

> **ヒント**: どちらの変更が正しいか分からないときは、GitLens の「File History」で
> そのファイルの変更履歴を確認すると判断しやすい。

**一人で悩まず、相手に聞く**のが一番早い。

---

## 7. よくあるミスと対処

### ❌ main に直接 commit してしまった

まだ push していないなら：

```bash
git switch -c feature/my-task   # 今のコミットをブランチに移す
git switch main
git reset --hard origin/main    # main をリモート状態に戻す
git switch feature/my-task
```

push してしまった場合は、リーダーに相談。

### ❌ `git add` で意図しないファイルを混ぜた

ターミナル：
```bash
git reset path/to/file   # ステージから外す（中身は消えない）
```

VS Code：「ソース管理」パネルの「ステージされている変更」で、外したいファイルの **「−」ボタン** をクリック。

### ❌ コミットメッセージをタイポした

まだ push していない直前のコミットなら：

```bash
git commit --amend -m "[機能追加] 正しいメッセージ"
```

push した後は、PR の説明欄でフォローするのが安全。

### ⚠️ `git push --force` はやらない

他人のコミットを消してしまう事故のもと。**必要になったら必ずリーダーに相談**。

---

## 8. Issue で作業を管理する

- 分担タスクは Issue を立てて管理する
- [`.github/ISSUE_TEMPLATE/task.md`](.github/ISSUE_TEMPLATE/task.md) を使うと書式が揃う
- PR の説明文に `Closes #NN` と書くと、マージ時に自動で Issue が閉じる

---

## 9. 困ったら

- まずは PR / Issue に**質問を書く**（誰かが答えてくれる）
- Slack / Discord などチームのコミュニケーションツールで聞く
- `git` は取り返しのつくこと・つかないことがある。破壊的操作（`reset --hard` /
  `push --force` / `rebase`）は不安なら相談してから実行する
