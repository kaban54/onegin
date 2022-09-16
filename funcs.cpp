#include "onegin.h"

size_t GetSize (FILE *inp_file)
{
    struct stat stat_buf {};

    fstat (fileno (inp_file), &stat_buf);
    return stat_buf.st_size;
}

struct Text ReadText (FILE *inp_file)
{
    struct Text txt = {};
    
    if (inp_file == NULL) return txt; //?

    size_t filesize = GetSize (inp_file);

    txt.buffer = (char *) calloc (filesize + 1, sizeof(char));
    if ((txt.buffer) == NULL) return txt;

    txt.buflen = fread (txt.buffer, sizeof(char), filesize, inp_file);

    char *pch = NULL;
    txt.len = 0;

    for (pch = txt.buffer; pch < txt.buffer + txt.buflen; pch++)
    {
        if (*pch == '\n')
        {
            txt.len++;
            *pch = '\0';
        }
    }

    txt.len++;
    *pch = '\0';
    txt.bufend = pch;

    txt.data = (char **) calloc (txt.len + 1, sizeof (char*));
    if ((txt.data) == NULL) return txt; //?

    char **pstr = txt.data;

    *(pstr++) = txt.buffer;

    for (pch = txt.buffer; pch < txt.bufend; pch++)
        if (*pch == '\0') *(pstr++) = pch + 1;
    *pstr = NULL;

    return txt;
}

void WriteText (struct Text txt, FILE *out_file)
{
    if (out_file == NULL) return;
    if (txt.data == NULL) return;

    while (*(txt.data) != NULL)
    {
        fputs (*(txt.data++), out_file);
        //fputc ('\r', out_file);
        fputc ('\n', out_file);
    }
    fputc('\n', out_file);
}


void WriteOriginal (struct Text txt, FILE *out_file)
{
    while (1)
    {
        if (*txt.buffer == '\0')
        {
            if (--txt.len > 0)
            {
                //fputc ('\r', out_file);
                fputc ('\n', out_file);
            }
            else break;
        }
        else
            fputc (*txt.buffer, out_file);
        
        txt.buffer++;
    }
}


void Sort1 (struct Text txt)
{
    int comp1 (const void *p1, const void *p2);

    qsort ((void *)txt.data, txt.len, sizeof (char *), comp1);
}

void Sort2 (struct Text txt)
{
    int comp2 (const void *p1, const void *p2);
    
    Quicksort ((void *)txt.data, txt.len, sizeof (char *), comp2);
}


void FreeText (struct Text txt)
{
    free (txt.buffer);
    free (txt.data);
}