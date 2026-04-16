# processing — PC 側サブシステムの置き場（例）

このディレクトリは「**PC 側で動くサブシステムをリポジトリに同梱したいとき**」の例。
サンプルとして [Processing](https://processing.org/) のスケッチを置いている。

Processing 以外の言語で PC 側ツール（Python の可視化、Unity のビューア等）を
作りたい場合は、ここを削除して自分たちの技術スタックに合うディレクトリ名に
作り直してよい（例: `viewer/`, `desktop_app/`, `web/` など）。

## こんなときに使う

- マイコンから PC へシリアルでデータを送って可視化したい
- PC 側で音・映像を生成したい
- 操作用の GUI を作りたい

## 構成

| ディレクトリ | 内容 |
|---|---|
| `example_sketch/` | 最小の Processing スケッチ（書き方のサンプル） |

## 実行方法（Processing の場合）

1. [Processing IDE](https://processing.org/download) をインストールする
2. `example_sketch/example_sketch.pde` を Processing IDE で開く
3. 「Run」ボタンを押す

## スケッチを追加する

Processing のお約束として、スケッチのフォルダ名と `.pde` のファイル名は
**同じ名前**にする必要がある。

```
processing/
└── my_sketch/
    └── my_sketch.pde   # フォルダと同じ名前
```

## 不要な班は

`processing/` ディレクトリを丸ごと削除してよい。
