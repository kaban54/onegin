#include "onegin.h"


int ReadText (const char *input_file_name, struct Text *txt)
{    
    if (input_file_name == NULL) return  INPUT_ERROR;
    if           (txt == NULL) return ACCESS_ERROR;

    FILE *inp_file = fopen (input_file_name, "r");
    if (inp_file == NULL) return INPUT_ERROR;

    size_t filesize = GetSize (inp_file);

    txt -> buffer = (char *) calloc (filesize + 1, sizeof((txt -> buffer)[0]));
    if ((txt -> buffer) == NULL) return ALLOC_ERROR;

    txt -> buflen = fread (txt -> buffer, sizeof((txt -> buffer)[0]), filesize, inp_file);
    *(txt -> buffer + txt -> buflen) = '\0';
    
    fclose (inp_file);

    txt -> len = CharReplace (txt -> buffer, '\n', '\0') + 1;

    SetLines (txt);

    return 0;
}

size_t GetSize (FILE *inp_file)
{
    if (inp_file == NULL) return 0;
    struct stat stat_buf = {};

    fstat (fileno (inp_file), &stat_buf);
    return stat_buf.st_size;
}

size_t CharReplace (char *str, char ch1, char ch2)
{
    if (str == NULL) return 0;

    size_t count = 0;
    str = strchr (str, ch1);

    while (str != NULL)
    {
        count++;
        *str = ch2;
        str = strchr (str + 1, ch1);
    }

    return count;
}

int SetLines (struct Text *txt)
{
    if (txt == NULL) return ACCESS_ERROR;

    txt -> data = (struct Line*) calloc (txt -> len + 1, sizeof ((txt -> data)[0]));
    if ((txt -> data) == NULL) return ALLOC_ERROR;

    char *str_ptr = txt -> buffer;
    size_t length = 0;

    for (unsigned int index = 0; index < txt -> len; index++)
    {
        length = strlen (str_ptr);

        (txt -> data + index) -> str = str_ptr;
        (txt -> data + index) -> len =  length;

        str_ptr += length + 1;
    }

    (txt -> data + txt -> len) -> str = NULL;
    (txt -> data + txt -> len) -> len = 0;

    return 0;
}


int WriteText (struct Text *txt, FILE *out_file, int write_param)
{
    if (out_file == NULL) return OUTPUT_ERROR;
    if (txt      == NULL) return ACCESS_ERROR;

    PrintSep (out_file);

    for (unsigned int index = 0; index < txt -> len; index++)
    {
        if (write_param == SKIP_EMPTY && strcmp ("", (txt -> data + index) -> str) == 0)
            continue;

        fputs ((txt -> data + index) -> str, out_file);
        //fputc ('\r', out_file);
        fputc ('\n', out_file);
    }
    fputc('\n', out_file);

    PrintSep (out_file);

    return 0;
}


int WriteOriginal (struct Text *txt, FILE *out_file, int write_param)
{
    if (out_file == NULL) return OUTPUT_ERROR;
    if (txt      == NULL) return ACCESS_ERROR;
 
    PrintSep (out_file);

    char *str = txt -> buffer;
    while (str < txt -> buffer + txt -> buflen)
    {
        if (write_param == SKIP_EMPTY && strcmp ("", str) == 0)
            continue;

        fputs (str,  out_file);
        // fputc ('\r', out_file);
        fputc ('\n', out_file);
        str = strchr (str, '\0') + 1;
    }

    PrintSep (out_file);

    return 0;
}

int PrintSep (FILE *out_file)
{
    if (out_file == NULL) return OUTPUT_ERROR;

    for (unsigned int _ = 0; _ <= SEP_LEN; _++) fputc ('=', out_file);
    fputc ('\n', out_file);

    return 0;
}

void FreeText (struct Text *txt)
{
    free (txt -> buffer);
    free (txt ->   data);
}