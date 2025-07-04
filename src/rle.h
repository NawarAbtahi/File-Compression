#ifndef RLE_H
#define RLE_H

#include <stdio.h>

char* RLEncodeFile(FILE *fp);
char* RLDecodeFile(FILE *fp);

#endif
