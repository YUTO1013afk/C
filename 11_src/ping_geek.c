// Geekなページ
// https://www.geekpage.jp/programming/linux-network/simple-ping.php

#include <arpa/inet.h>

// 以下のheaderは netinet/ip_icmp.h に記述あり
// #include <netinet/in.h>
// #include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stdio.h>
#include <sys/socket.h>

// memset() は string.h
#include <string.h>

// close() は unistd.h
#include <unistd.h>

struct myicmp {
    uint8_t icmp_type;   /* type of message, see below */
    uint8_t icmp_code;   /* type sub code */
    uint16_t icmp_cksum; /* ones complement checksum of struct */
};

// https://wireless-network.net/raw-socket-icmp/
// より追加
/*ICMPパケットの中身を表示する関数*/
void icmp_packet(struct myicmp *icmp) {
    /*機能名を格納したポインタ配列*/
    char *type[] = {
        "ECHO REPLY",
        "undefined",
        "undefined",
        "DESTINATION UNREACHABLE",
        "SOURCE QUENCH",
        "REDIRECT",
        "undefined",
        "undefined",
        "ECHO REQUEST",
        "ROUTER ADVERTISMENT",
        "ROUTER SELECTION",
        "TIME_EXCEEDED",
        "PARAMETER PROBLEM",
        "TIMESTAMP REQUEST",
        "TIMESTAMP REPLY",
        "INFORMATION REQUEST",
        "INFORMATION REPLY",
        "ADDRESS MASK REQUEST",
        "ADDRESS MASK REPLY"};

    /*タイプ３のコード名を格納したポインタ配列*/
    char *type3_code[] = {
        "Network unreachable",
        "Host unreachable",
        "Protocol unreachable",
        "Port unreachable",
        "Fragmenttation needed anf DF set",
        "Source route falied",
        "Destination network unknown",
        "Destination host unknown",
        "Source host isolated",
        "Destination network administratively prohibited",
        "Destination host administratively prohibited",
        "Network unreachable for TOS",
        "Communication administratively prohibited by filtering",
        "Host precedence violation",
        "Precedence cutoff in effect"};

    /*タイプ５のコード名を格納したポインタ配列*/
    char *type5_code[] = {
        "Redirect for network",
        "Redirect for host",
        "Redirect for TOS and network",
        "Redirect for TOS and host"};

    /*タイプ１１のコード名を格納したポインタ配列*/
    char *type11_code[] = {
        "TTL exceedded in transit",
        "Fragment reassenbly time exceeded"};

    /*タイプ１２のコード名を格納したポインタ配列*/
    char *type12_code[] = {
        "Pointer indicates the error",
        "Missing a reqired option",
        "Bad length"};

    /*ICMPパケットを表示*/
    printf("-------icmp-------\n");
    printf("type = %u ", icmp->icmp_type); // タイプ
    if (icmp->icmp_type <= 18)
        printf("(%s)\n", type[icmp->icmp_type]);
    else
        printf("(undefined)\n");           // タイプ１９以上はポインタ配列に格納していない
    printf("code = %u ", icmp->icmp_code); // コード
    switch (icmp->icmp_type) {
    case 3:
        if (icmp->icmp_code <= 15) {
            printf("(%s)", type3_code[icmp->icmp_code]);
        } else {
            printf("(undefined)\n");
        } // タイプ１５のコード１６以上は未定義
        break;
    case 5:
        if (icmp->icmp_code <= 3) {
            printf("(%s)", type5_code[icmp->icmp_code]);
        } else {
            printf("(undefined)\n");
        } // タイプ３のコード４以上は未定義
        break;
    case 11:
        if (icmp->icmp_code <= 1) {
            printf("(%s)", type11_code[icmp->icmp_code]);
        } else {
            printf("(undefined)\n");
        } // タイプ１１のコード２以上は未定義
        break;
    case 12:
        if (icmp->icmp_code <= 2) {
            printf("(%s)", type12_code[icmp->icmp_code]);
        } else {
            printf("(undefined)\n");
        } // タイプ１２のコード３以上は未定義
        break;
    default:
        break;
    }
    printf("\nchecksum = %u\n", ntohs(icmp->icmp_cksum)); // チェックサム
}
/*
 * チェックサムを計算する関数です。
 * ICMPヘッダのチェックサムフィールドを埋めるために利用します。
 * IPヘッダなどでも全く同じ計算を利用するので、
 * IPヘッダのチェックサム計算用としても利用できます。
 */
unsigned short
checksum(unsigned short *buf, int bufsz) {
    unsigned long sum = 0;

    while (bufsz > 1) {
        sum += *buf;
        buf++;
        bufsz -= 2;
    }

    if (bufsz == 1) {
        sum += *(unsigned char *)buf;
    }

    sum = (sum & 0xffff) + (sum >> 16);
    sum = (sum & 0xffff) + (sum >> 16);

    return ~sum;
}

/* main 文はここからです。*/
int main(int argc, char *argv[]) {
    int sock;
    struct icmphdr hdr;
    struct sockaddr_in addr;
    int n;

    char buf[2000];
    struct icmphdr *icmphdrptr;
    struct iphdr *iphdrptr;

    if (argc != 2) {
        printf("usage : %s IPADDR\n", argv[0]);
        return 1;
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    /* RAWソケットを作成します */
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0) {
        perror("socket");
        return 1;
    }

    memset(&hdr, 0, sizeof(hdr));

    /* ICMPヘッダを用意します */
    hdr.type = ICMP_ECHO;
    hdr.code = 0;
    hdr.checksum = 0;
    hdr.un.echo.id = 0;
    hdr.un.echo.sequence = 0;

    /* ICMPヘッダのチェックサムを計算します */
    hdr.checksum = checksum((unsigned short *)&hdr, sizeof(hdr));
    printf("(send)checksum:%u\n", ntohs(hdr.checksum));

    /* ICMPヘッダだけのICMPパケットを送信します */
    /* ICMPデータ部分はプログラムを簡潔にするために省いています */
    n = sendto(sock,
               (char *)&hdr, sizeof(hdr),
               0, (struct sockaddr *)&addr, sizeof(addr));
    if (n < 1) {
        perror("sendto");
    }

    /* ICMP送信部分はここまでです*/
    /* ここから下はICMP ECHO REPLY受信部分になります */

    memset(buf, 0, sizeof(buf));

    /* 相手ホストからのICMP ECHO REPLYを待ちます */
    n = recv(sock, buf, sizeof(buf), 0);
    if (n < 1) {
        perror("recv");
    }

    /* 受信データからIPヘッダ部分へのポインタを取得します */
    iphdrptr = (struct iphdr *)buf;

    /*
     * 本当はIPヘッダを調べて
     * パケットがICMPパケットかどうか調べるべきです
     */

    /* 受信データからICMPヘッダ部分へのポインタを取得します */
    icmphdrptr = (struct icmphdr *)(buf + (iphdrptr->ihl * 4));

    /* ICMPヘッダからICMPの種類を特定します */
    if (icmphdrptr->type == ICMP_ECHOREPLY) {
        printf("received ICMP ECHO REPLY\n");
    } else {
        printf("received ICMP %d\n", icmphdrptr->type);
    }

    // icmp_packet((struct icmp *)buf);
    icmp_packet((struct myicmp *)icmphdrptr);
    /* 終了 */
    close(sock);

    return 0;
}
