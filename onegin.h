#ifndef ONEGIN_H
#define ONEGIN_H


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>

const int MAXLEN = 100;

// sort functions ----------------------------------------------------------------------------------------
void  quicksort (void *data, size_t len, size_t size, int (*comp)(const void*, const void*));
void *partition (void *data, size_t len, size_t size, int (*comp)(const void*, const void*));

void swap (void *p1, void *p2, size_t size);

int comp1 (const void *p1, const void *p2);
int comp2 (const void *p1, const void *p2);
// ------------------------------------------------------------------------------------------------------

char **read_data (FILE *inp_file, size_t *plen);

void  write_data (char **data, FILE *out_file);

void  write_buf (char *buffer, size_t len, FILE *out_file);

char **sort_data (char **data, size_t len, int (*comp)(const void*, const void*));


enum ERRORS 
{
    INPUT_ERROR  = 1,
    OUTPUT_ERROR = 2,
};

#endif
