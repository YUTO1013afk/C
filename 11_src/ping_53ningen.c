// ping コマンドを実装する (1)
// https://53ningen.com/ping-impl1
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

// 追加
struct icmpechoheader {
    u_int8_t type;
    u_int8_t code;
    u_int16_t checksum;
    u_int16_t id;
    u_int16_t sequence;
};
// 追加
u_int16_t checksum(u_int16_t *buf, int size) {
    u_int32_t sum = 0;

    /*
     *  Our algorithm is simple, using a 32 bit accumulator (sum),
     *  we add sequential 16 bit words to it, and at the end, fold
     *  back all the carry bits from the top 16 bits into the lower
     *  16 bits.
     */
    while (size > 1) {
        sum += *buf++;
        size -= 2;
    }

    /* mop up an odd byte, if necessary */
    if (size == 1) {
        sum += *(unsigned char *)buf;
    }

    sum = (sum >> 16) + (sum & 0xffff); /* add hi 16 to low 16 */
    sum += (sum >> 16);                 /* add carry */
    return ~sum;
}

int main(int argc, char *argv[]) {
    // 宛先の IP アドレスを引数で受け取る
    if (argc != 2) {
        perror("usage: ping DESTINATION");
        exit(1);
    }

    // char[] で受け取った IP アドレスを sockaddr_in 構造体に突っ込む
    struct sockaddr_in dest;
    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr(argv[1]);
    if (dest.sin_addr.s_addr == INADDR_NONE) {
        perror("error: inet_addr");
        exit(1);
    }

    // ICMP Echo Request メッセージの data 部を準備
    // ICMP ヘッダと data 部の先頭に突っ込む timeval の
    // 8 + 16 = 24 bytes 分のオフセットの位置に固定データ(abcd)を流し込む
    char str[] = "abcd";
    char data[28];
    memcpy(&data[24], str, strlen(str));
    int cc = sizeof(data);

    // ICMP Echo Reuqest のヘッダーを構成
    struct icmpechoheader *icp = (struct icmpechoheader *)data;
    icp->type = 0x08;
    icp->code = 0x00;
    icp->checksum = 0x0000;
    icp->id = getpid();
    icp->sequence = 0x0001;

    // data の最初は timeval で埋める
    struct timeval tmp_tv;
    gettimeofday(&tmp_tv, NULL);
    memcpy(icp + 1, &tmp_tv, sizeof(struct timeval));

    // 送信するパケットが固まったのでチェックサム計算
    icp->checksum = checksum((unsigned short *)icp, cc);

    // ソケットを開き、作成したパケットを送信
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0) {
        perror("error: sock");
        exit(1);
    }
    int ret = sendto(sock, icp, cc, 0, (struct sockaddr *)&dest, sizeof(dest));

    if (ret < 1) {
        perror("error: sendto");
        exit(1);
    }

    printf("%s %s\n", "ping:", argv[1]);
    exit(0);
}