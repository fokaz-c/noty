/***    includes    ***/
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <ctype.h>

/***    data    ***/
struct termios original_termios;

/***    terminal    ***/
void noty_kill(const char *source) {
    perror(source);
    exit(1);
}


void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios) == -1)
        noty_kill("tcsetattr");
}


void enableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios) == -1)
        noty_kill("tcsetattr");
    atexit(disableRawMode);

    struct termios raw = original_termios;
    raw.c_iflag &= ~(BRKINT |ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) 
        noty_kill("tcsetattr");
}

/***    init/main   ***/
int main() {
    enableRawMode();
    char c;
    read(STDIN_FILENO, &c , 1); 
    while (1) {
        char c;
        if(read(STDIN_FILENO, &c , 1) == -1 && errno != EAGAIN)
            noty_kill("Read");
        if (iscntrl(c)) {
            printf("%d\r\n", c);
        }
        else{
            printf("%d (%c)\r\n",c,c);
        }
        if (c == 'q') break;
    }
    printf("yeah compiles.\n");
    return 0;
}
