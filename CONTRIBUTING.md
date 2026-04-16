# コントリビューションガイド

このリポジトリで開発するときのルール集。**Git も共同開発もほぼ初めて**という
メンバーを想定して書いている。慣れている人は「ブランチ戦略」以降を斜め読みでOK。

---

## 🚨 一番大事なルール：作業前に必ず `git pull`

コード編集に取りかかる**前に**、ローカルのリポジトリを最新の状態に揃える。

```bash
git switch main      # main ブランチに移動
git pull             # リモート（GitHub）から最新を取り込む
```

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

### 0.2 名前とメールアドレスを登録（初回のみ）

commit の作者情報として使われる。GitHub に登録したアドレスを使うと、
GitHub 上であなたのアイコンが表示されて分かりやすい。

```bash
git config --global user.name "Your Name"
git config --global user.email "you@example.com"
```

### 0.3 GitHub との認証

HTTPS で clone するなら、push のときに GitHub の**個人アクセストークン（PAT）**を
求められる。パスワードは使えないので注意。

- 参考: [GitHub: 個人アクセストークンの作成](https://docs.github.com/ja/authentication/keeping-your-account-and-data-secure/managing-your-personal-access-tokens)

より楽なのは **SSH 鍵** を登録する方法。一度設定すればパスワード不要になる。

- 参考: [GitHub: SSHでの接続](https://docs.github.com/ja/authentication/connecting-to-github-with-ssh)

---

## 1. リポジトリを手元に持ってくる（clone）

チーム用のリポジトリ URL をリーダーからもらって、手元にコピーする。

```bash
# 好きな場所に移動して
cd ~/Documents

# clone
git clone https://github.com/<組織名>/<リポジトリ名>.git
cd <リポジトリ名>
```

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

### ブランチ切りのコツ

1. **必ず最新の main から切る**
   ```bash
   git switch main
   git pull
   git switch -c feature/my-task
   ```
2. **1ブランチ = 1目的**（レビュー負担を減らす）
3. **長期間持たない**：1週間以上持つとコンフリクト地獄になる。大きい作業は
   途中で PR を分ける
4. **作業中に main が進んだら取り込む**：
   ```bash
   git fetch origin          # 最新情報を取得（ローカルは変わらない）
   git merge origin/main     # 自分のブランチに main を取り込む
   ```
5. **マージされたブランチは消す**：
   ```bash
   git switch main
   git pull
   git branch -d feature/my-task   # ローカルのブランチを削除
   ```

---

## 3. 作業の流れ（add → commit → push → PR）

### 3.1 作業前の準備

```bash
git switch main
git pull
git switch -c feature/my-task
```

### 3.2 ファイルを編集する

好きなエディタで編集。

### 3.3 変更を確認する

```bash
git status       # どのファイルを変更したか
git diff         # 具体的にどう変わったか
```

### 3.4 ステージング（`git add`）

コミットしたいファイルだけを選ぶ。

```bash
git add path/to/file.c            # 特定のファイル
git add path/to/dir/              # ディレクトリ丸ごと
# git add -A や git add . は便利だが、意図しないファイル（.env 等）まで
# 含めがちなので、慣れるまではファイル名を直接指定するのが安全
```

### 3.5 コミット

```bash
git commit -m "[機能追加] センサ読み取り処理を追加"
```

コミットメッセージの書式は [#コミットメッセージ規約](#4-コミットメッセージ規約) を参照。

### 3.6 リモートに push

```bash
# 初回（ブランチを GitHub に作るとき）
git push -u origin feature/my-task

# 2回目以降
git push
```

### 3.7 Pull Request を作る

1. GitHub のリポジトリページを開く
2. 黄色いバナー「Compare & pull request」が出ているのでクリック
3. PR テンプレートが自動で入るので、埋めて「Create pull request」
4. レビュアーを指定（CONTRIBUTING のルールに合わせる）

### 3.8 レビュー指摘に対応する

1. 同じブランチで編集 → add → commit → push
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

### 手順

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

```bash
git reset path/to/file   # ステージから外す（中身は消えない）
```

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
