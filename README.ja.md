# c-webserver-by-neco

Cで実装されたWebサーバーです。[neco](https://github.com/tidwall/neco)ライブラリを使用しています。

## デモ
`http://localhost:8080/`にアクセスするとサーバーが起動します。

## 機能
- Cで簡単なWebサーバーを実装
- necоライブラリを使用
- HTML、画像、テキストなどのコンテンツ配信

## 必要環境
- Cコンパイラ

## 使い方
```sh
cc -c server.c neco.c
./a.out 8080
```
`http://localhost:8080/`にアクセス

## ライセンス
ソースコードはMITライセンスで公開されています。