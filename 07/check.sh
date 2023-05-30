#!/bin/bash

./a.out

status=$?

echo "プログラムの終了ステータス: $status"
if [ "$status" -ne "0" ]; then
echo "==(X) プログラムが異常終了しました =="
exit 1
fi

if [ "$status" -eq "0" ]; then
echo "==(O) プログラムが正常終了しました =="
exit 0
fi