#include <ncurses.h>

int main() {
    initscr();                           // 端末制御の開始
    start_color();                       // カラーの設定
    init_pair(1, COLOR_RED, COLOR_BLUE); // ⾊番号１を⾚⽂字∕⻘地とする
    bkgd(COLOR_PAIR(1));                 // ⾊１をデフォルト⾊とする
    erase();                             // 画⾯表⽰
    move(10, 20);
    addstr("Hello World");
    refresh();
    timeout(-1);
    getch();  // キー⼊⼒
    endwin(); // 端末制御の終了
    return (0);
}
