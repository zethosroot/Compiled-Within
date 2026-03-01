#ifndef PRINT_H
#define PRINT_H
#include <stdbool.h>

void print_slow(const char *text);
void print_line(const char *text, bool slow, bool centered);
void print_paragraph(const char *text, bool slow, bool centered);

#endif