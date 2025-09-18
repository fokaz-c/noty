#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <ctype.h>

struct termios original_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}


void enableRawMode() {
    tcgetattr(STDIN_FILENO, &original_termios);
    atexit(disableRawMode);

    struct termios raw = original_termios;
    raw.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


int main() {
    enableRawMode();
    char c;
    while (read(STDIN_FILENO, &c , 1) == 1 && c != 'q') {
        if (iscntrl(c)) {
            printf("%d\n", c);
        }
        else{
            printf("%d (%c)\n",c,c);
        }
    }
    printf("yeah compiles.\n");
    return 0;
}
