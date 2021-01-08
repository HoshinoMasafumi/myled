# ロボットシステム学　課題１

第7回、第8回で作成したデバイスドライバーをベースに、オリジナリティーある改造をして、GitHubに公開する。

### 動作環境

- Ubuntu 20.04 LTS

### 実装内容

１つのLEDを使い、アルファベットと数字をモールス信号で表示する。

### 使用した道具

- Raspberry Pi 4 Model B

- LED

- ブレッドボード

- ジャンパーワイヤ 2本

### デモ動画のリンク

[[デモ動画>https://youtu.be/XIYi1GfzJEE]]

### インストール方法

```
git clone　https://github.com/HoshinoMasafumi/myled.git
cd myled
make
sudo insmod myled.ko
sudo chmod 666 /dev/myled0
```

### 操作方法

```
echo 〇〇 > /dev/myled0
```

〇〇に出力したいアルファベットや数字を入力する。

### ライセンス

[[GNU General Public License v2.0>https://github.com/HoshinoMasafumi/myled/blob/main/COPYING]]
