#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include "input.h"
#include "macros.h"

void read_input(unsigned char *buf) {
    unsigned char i = 0;
    unsigned char c;

    while (true) { 
        
        c = cgetc();

        if (c == 0x0D) {
            // Enter - Eingabe beenden
            buf[i] = '\0';
            break;
        } else if (c == 0x14 && i > 0) {
            // Rücktaste - ein Zeichen löschen
            i--;
            buf[i] = '\0';
            gotoxy(wherex() - 1, wherey());  // Cursor zurück
            cputc(' ');                      // Zeichen löschen
            gotoxy(wherex() - 1, wherey());  // Cursor wieder zurück
        } else if (i < INPUT_LENGTH - 1 && c != 0x14) {
            // Normales Zeichen speichern
            buf[i] = c;
            cputc(c);
            i++;
        }
    }
}

void str_upper(unsigned char *s) {
    while (*s) { *s = toupper(*s); s++; }
}