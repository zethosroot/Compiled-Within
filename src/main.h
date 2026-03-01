#ifndef MAIN_H
#define MAIN_H

// Funktionen deklarieren
void print_slow(const char *text);
void print_line(const char *text, bool slow, bool centered);
void print_paragraph(const char *text, bool slow, bool centered);
void read_input(unsigned char *buf);
void str_upper(unsigned char *s);
void parse(char *verb, char*noun);
void start();

#endif