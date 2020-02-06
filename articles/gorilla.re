= TUIツールを作ろう

初めまして、ゴリラ@<fn>{about_gorilla}です。
本章はGoを使ったTUI（Text-based User Interface）ツールの作り方について解説していきます。

//footnote[about_gorilla][https://twitter.com/gorilla0513]

== TUIとは
TUIは簡潔に説明しますと端末上で動作するGUIのようなインタフェースのことです。
GUIと同様、マウスとキーボードを使用できます。

TUIツールとはそのようなインタフェースを持つツールのことを指します。
よくCLI（Command Line Interface）と混合されますが、CLIは名前のとおりコマンドを使って操作するインタフェースです。
たとえば@<code>{ls}などはCLIの一種です。

TUIがCLIと混同されがちな理由は、おそらくどちらもコマンドを使って実行するからなのではないかと考えられます。

=== TUIのメリットとデメリット
TUIツールを使う一番のメリットは、直感的でシンプルに操作できるところです。

たとえば、@<img>{gorilla/about_tui_tool}は筆者が作成したdockerを操作できるdocuiというTUIツールですが、
@<code>{u}でコンテナを起動、@<code>{d}コンテナを削除できます。
これをCLIで行うと次のコマンドを入力して実行する必要があります。

//cmd{
# コンテナの停止
$ docker stop {container name or id}

# コンテナの削除
# docker rm {container name or id}
//}

このように、CLIでは都度コマンドを入力して実行という手順を踏む必要があって面倒です。
そのような面倒を解消するために筆者はTUIツールをよく作っています。

しかし、TUIにもデメリットがあります。TUIはキーボードやマウス、画面などを使用するため自動化に向いていません。
対してCLIは自動化にとても向いています。

このように、TUIとCLIはそれぞれ活かせる場面がありますので、その使い分けもまた大事と筆者は考えています。

//image[gorilla/about_tui_tool][筆者が作ったdockerのTUIツール][scale=0.9]

== TUIツール
TUIについて説明したところで、どんなTUIツールがあるのかを紹介します。

=== docui
TUIとはの節で軽く紹介しましたが、改めて紹介します。
docui@<fn>{about_docui}はdockerの操作をシンプルに、そして初心者でも使いやすいTUIツールです。

主な機能は次です。

 * イメージの検索、取得、削除、インポート、セーブ、ロード
 * コンテナの作成、起動、停止、削除、アタッチ、エクスポート
 * ネットワーク、ボリュームの削除

docuiでは各リソース（イメージやコンテナ）をパネルごとに表示しています。
各パネルでのキーを使って操作します。

たとえばイメージのパネルで@<code>{c}でコンテナの@<img>{gorilla/docui-create-container}のように作成画面が表示され、必要な項目を入力してコンテナを作成できます。
また、@<code>{f}で入力画面が表示され、キーワードを入力してEnterを押すと@<img>{gorilla/docui-search}のようにイメージの検索結果一覧を見れます。

//image[gorilla/docui-create-container][コンテナ作成][scale=0.9]
//image[gorilla/docui-search][イメージの検索][scale=0.9]

//footnote[about_docui][https://github.com/skanehira/docui]

=== lazygit
lazygit@<fn>{about_lazygit}はGitのTUIツールです。GitコマンドをTUIツールでラップしてより使いやすくなっています。

lazygitはファイルの差分確認やステージ追加、コミットの差分確認などを行うときに便利です。
@<img>{gorilla/lazygit-diff}はコミットの差分を表示する画面です。
@<img>{gorilla/lazygit-staging}はファイルの行単位の差分をステージに追加している画面です。

//image[gorilla/lazygit-diff][lazygit][scale=0.9]
//image[gorilla/lazygit-staging][lazygit][scale=0.9]

//footnote[about_lazygit][https://github.com/jesseduffield/lazygit]

=== JSON
JSONといえばjq@<fn>{about_jq}というCLIツールが有名です。
しかし、jqはインタラクティブに値を絞り込みできないので、筆者はJSONをインタラクティブに操作できるtson@<fn>{about_tson}というTUIツールを作りました。

tsonの主な機能は次になります。

 * JSONをツリー状で表示し、キーと値の絞り込みができる
 * ファイルまたは標準入力からJSON文字列を受け取ることができる
 * 編集できる

@<img>{gorilla/tson-edit}はJSONを編集している様子です。

//image[gorilla/tson-edit][tsonによる編集][scale=0.9]

//footnote[about_tson][https://github.com/skanehira/tson]

=== ファイラー
端末で作業しているとディレクトリの移動やファイルのコピーや削除、中身を確認したりすることが多々あります。
これらもすべてコマンドで操作する必要があり、ちょっと面倒です。

そこで、筆者はff@<fn>{about_ff}というTUIツールを作りました。
ffは手軽にディレクトリの移動やファイル、ディレクトリの作成、削除やプレビューを行えることが特徴です。

@<img>{gorilla/about-ff}はffを使ってファイルをプレビューしている様子です。

//image[gorilla/about-ff][ファイラー][scale=0.9]

== TUIツールを作る
TUIツールをいくつか紹介したところで、実際に簡単なTUIツールを作ってみましょう。
今回のTUIツールはファイルのビューアです。ビューアの仕様の次になります。

 * カレントディレクトリのファイル一覧
 * 選択したファイルの中身をプレビュー画面に表示

とてもシンプルなTUIなので、みなさんもぜひ一緒に手を動かしながら読み進めましょう。

=== ライブラリ
今回使用するライブラリはtview@<fn>{about-tview}というTUIライブラリです。筆者は普段このライブラリを使用してTUIツールを作っています。
1点注意ですが、このライブラリはWindowsでは正しく描画されないので、今回作成するアプリもWindowsでも正常に動作しません。

//footnote[about-tview][https://github.com/rivo/tview]
