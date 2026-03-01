#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include "sound.h"
#include "print.h"
#include "config.h"


// Basisfunction: Gibt Text langsam aus
void print_slow(const char *text) {
    volatile int i;
    static int j;
    for (j = 0; text[j] != '\0'; j++) {
        if (text[j] == ' ') {
            cputc(' ');
        } else {
            play_click();
            cputc(text[j]);
            for (i = 0; i < PRINT_SPEED; i++);
        }
    }
}

// Gibt einen Absatz mit Zeilenumbruch aus, optional zentriert und/oder langsam
void print_paragraph(const char *text, bool slow, bool centered) {
    static char buf[256];
    static char linebuf[41];
    char *word;
    unsigned char col = 0;
    unsigned char wordlen;

    strcpy(buf, text);
    linebuf[0] = '\0';
    word = strtok(buf, " ");

    while (word != NULL) {
        wordlen = strlen(word);

        if (col + wordlen > 38) {
            /* Leerzeichen am Ende entfernen */
            if (col > 0) linebuf[col - 1] = '\0';
            print_line(linebuf, slow, centered);
            linebuf[0] = '\0';
            col = 0;
        }       

        strcat(linebuf, word);
        strcat(linebuf, " ");
        col += wordlen + 1;

        word = strtok(NULL, " ");
    }

    if (col > 0) {
        linebuf[col - 1] = '\0';
        print_line(linebuf, slow, centered);
    }
}

// Gibt eine Zeile aus, optional zentriert und/oder langsam
void print_line(const char *text, bool slow, bool centered) {
    int i;
    if (centered) {
        unsigned char padding = (40 - strlen(text)) / 2;
        for (i = 0; i < padding; i++) cputc(' ');
    }
    if (slow) print_slow(text);
    else cprintf("%s", text);
    cprintf("\r\n");
}
