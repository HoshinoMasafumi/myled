# ロボットシステム学　課題１

第7回、第8回で作成したデバイスドライバーをベースに、オリジナリティーある改造をして、GitHubに公開する。

## 実装内容

１つのLEDを使い、アルファベットと数字をモールス信号で表示する。

### 使用した道具

- Raspberry Pi 4 Model B

- LED

- ブレッドボード

- ジャンパーワイヤ 2本

### ビルド

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

