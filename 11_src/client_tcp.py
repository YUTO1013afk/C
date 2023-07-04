import socket

# ホストのソケットオブジェクトの作成
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# サーバにリクエストを送る
# 127.0.0.1: サーバのIPアドレス
# 60001: サーバが待ち受けするポートを指定する
s.connect(('127.0.0.1', 60001))

# サーバからデータを受信する
data = s.recv(4096)

# クライアントの標準出力に受信したデータを表示する
print(data)

# クライアントのソケットを削除する
s.close()
