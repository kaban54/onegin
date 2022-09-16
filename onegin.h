#ifndef ONEGIN_H
#define ONEGIN_H


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>


const int MAXLEN = 100;


struct Text
{
    size_t len    = 0;
    size_t buflen = 0;
    char *buffer = NULL;
    char *bufend = NULL;
    char **data  = NULL;
};


void Quicksort (void *data, size_t len, size_t size, int (*comp)(const void *elem1, const void *elem2));

void swap (void *p1, void *p2, size_t size);


struct Text ReadText (FILE *inp_file);

size_t GetSize (FILE *inp_file)

void WriteText     (struct Text txt, FILE *out_file);
void WriteOriginal (struct Text txt, FILE *out_file);

void Sort1 (struct Text txt);
void Sort2 (struct Text txt);

void FreeText (struct Text txt);


enum ERRORS 
{
    INPUT_ERROR  = 1,
    OUTPUT_ERROR = 2,
};



#endif
