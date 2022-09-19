#ifndef ONEGIN_H
#define ONEGIN_H


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <locale.h>

const size_t SEP_LEN = 107;

struct Text
{
    size_t len    = 0;
    size_t buflen = 0;
    char  *buffer = NULL; 
    struct Line *data = NULL;
};

struct Line
{
    size_t len = 0;
    char *str = NULL;
};


void Quicksort (void *data, size_t len, size_t size, int (*comp)(const void *elem1, const void *elem2));

void SortTwo (void *data, size_t size, int (*comp)(const void*, const void*));

void *partition (void *data, size_t len, size_t size, int (*comp)(const void*, const void*));

void swap (void *p1, void *p2, size_t size);

int CompFwd (const void *p1, const void *p2);

int CompBwd (const void *p1, const void *p2);


int ReadText (const char *input_file_name, struct Text *txt);

size_t GetSize (FILE *inp_file);

size_t CharReplace (char *str, char ch1, char ch2);

int SetLines (struct Text *txt);


int WriteText     (struct Text *txt, FILE *out_file, int write_param);

int WriteOriginal (struct Text *txt, FILE *out_file, int write_param);

int PrintSep (FILE *out_file);


void FreeText (struct Text *txt);


enum ERRORS 
{
     INPUT_ERROR = 1,
    OUTPUT_ERROR = 2,
    ACCESS_ERROR = 3,
     ALLOC_ERROR = 4,
};

enum WRITE_PARAMS
{
    NSKIP_EMPTY = 0,
     SKIP_EMPTY = 1,
};



#endif
