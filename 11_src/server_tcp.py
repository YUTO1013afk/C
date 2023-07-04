import socket

# socket.socket(): ソケットオブジェクトの作成
# AF_INET: アドレスファミリ（使うアドレスの種類がまとめられたもの）のうち、IPv4を指定する
# SOCK_STREAM: TCPプロトコルを指定
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# socket.bind(): IPアドレスとポート番号を作成したソケットオブジェクトに紐づける
# 127.0.0.1: ローカルホストを指定する
# 60001: ポート番号のうち60001を指定する（待ち受けポート）

# 再実行したときに、"Address already in use" Errorが出ないようにする
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind(('127.0.0.1', 60001))

# socket.listen(): クライアントからの入力待ち状態になる
# 1: 並列的に処理できるリクエスト数を1つに指定する
s.listen(1)

count = 0
while count < 5:
    # socket.accept(): クライアントからの接続を受け付ける
    # conn: 新しく作成したソケットオブジェクト
    # addr: 受信したIPアドレス
    conn, addr = s.accept()

    # サーバの標準出力に文字列を出す
		# addr: (クライアントのIPアドレス, クライアントのポート番号)
    print(f'Source IP Address: {addr}')

    # クライアントのソケットにデータを送信する
    conn.send(b'Hello World!')

    # クライアントのソケットオブジェクトを削除する
    conn.close()
    count += 1

# サーバのソケットを削除する
s.close()
