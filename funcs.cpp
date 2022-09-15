#include "onegin.h"

char **read_data (FILE *inp_file, size_t *plen)
{
    struct stat stat_buf = {};
    char *buffer = 0;
    char *ptr = 0;
    char **str = 0;
    char **data = 0;
    size_t filesize = 0;
    size_t str_count = 0;

    fstat (fileno(inp_file), &stat_buf);
    filesize = stat_buf.st_size;

    if((buffer = (char *`)malloc(filesize + 1)) == NULL) return NULL;

    fread (buffer, sizeof(char), filesize, inp_file);
    
    for (ptr = buffer; ptr < buffer + filesize; ptr++)
    {
        if (*ptr == '\n')
        {
            str_count++;
            *ptr = '\0';
        }
    }
    *ptr = '\0';

    if ((data = (char **)malloc(str_count + 1)) == NULL) return NULL;
    *plen = str_count;

    str = data;
    for (ptr = buffer; ptr < buffer + filesize; ptr++)
        if (*ptr == '\0') *(str++) = ptr;
    
    return data;
}

void write_data (char **data, FILE *out_file)
{
    if (out_file == NULL || data == NULL) return;
    while(*data != NULL) fputs(*data++, out_file);
}

void write_buf (char *buffer, size_t len, FILE *out_file)
{
    for (len; len > 0; len--)
    {
        if (*buffer == '\0')
        {
            fputc ('\r', out_file);
            fputc ('\n', out_file);
        }
        else
            fputc(*buffer, out_file);
        buffer++;
    }
}

char **sort_data (char **data, size_t len, int (*comp)(const void*, const void*))
{
    quicksort ((void *)data, len, sizeof(char*), comp);
    return data;
}