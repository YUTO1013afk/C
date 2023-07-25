#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define BPM 60
#define SECONDS 30

// スレッドAの処理
void *beat_A(void *arg) {
    float wait = 60.0 / BPM; // 秒
    int x, y;
    y = ((int *)arg)[0];
    x = ((int *)arg)[1] - 2;

    // printf("start A\n");
    move(0, 0);
    addstr("start A");
    for (int loop = 0; loop < SECONDS; loop++) {
        // 記号を表示する
        move(y, x);
        addstr("=");
        refresh();
        usleep(wait * 0.5 * 1000000);
        // 記号を非表示にする
        move(y, x);
        addstr(" ");
        refresh();
        usleep(wait * 0.5 * 1000000);
    }

    return NULL;
}

// スレッドBの処理
void *beat_B(void *arg) {
    float wait = 60.0 / BPM / 2.0; // Aの半分
    int x, y;
    y = ((int *)arg)[0];
    x = ((int *)arg)[1];

    // printf("start B\n");
    move(1, 0);
    addstr("start B");
    // Aの倍回す必要が有る
    for (int loop = 0; loop < SECONDS * 2; loop++) {
        move(y, x);
        addstr("+");
        refresh();
        usleep(wait * 0.5 * 1000000);
        move(y, x);
        addstr(" ");
        refresh();
        usleep(wait * 0.5 * 1000000);
    }

    return NULL;
}

// スレッドCの処理
void *beat_C(void *arg) {
    float wait = 60.0 / BPM / 2.0 / 2.0; // Aの半分の半分
    int x, y;
    y = ((int *)arg)[0];
    x = ((int *)arg)[1] + 2;

    // printf("start C\n");
    move(2, 0);
    addstr("start C");
    // Aの4倍回す必要が有る
    for (int loop = 0; loop < SECONDS * 4; loop++) {
        move(y, x);
        addstr("-");
        refresh();
        usleep(wait * 0.5 * 1000000);
        move(y, x);
        addstr(" ");
        refresh();
        usleep(wait * 0.5 * 1000000);
    }

    return NULL;
}

int main(int argc, char const *argv[]) {
    int pos[2], h, w;

    initscr();
    erase();
    getmaxyx(stdscr, h, w);
    pos[0] = h / 2;       // y座標
    pos[1] = (w - 5) / 2; // x座標

    curs_set(0);

    pthread_t th_a;
    pthread_create(&th_a, NULL, beat_A, pos);

    pthread_t th_b;
    pthread_create(&th_b, NULL, beat_B, pos);

    pthread_t th_c;
    pthread_create(&th_c, NULL, beat_C, pos);

    pthread_join(th_a, NULL);
    pthread_join(th_b, NULL);
    pthread_join(th_c, NULL);

    curs_set(1);

    endwin();
    return 0;
}
