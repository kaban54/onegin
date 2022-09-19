#include "onegin.h"


const char  INPUTNAME[] =  "input.txt";
const char OUTPUTNAME[] = "output.txt";

int main(int argc, char *argv[])
{   
    setlocale (LC_ALL, "Rus");
    
    const char  *input_file_name =  INPUTNAME;
    const char *output_file_name = OUTPUTNAME;
    
    if (argc >= 2)  input_file_name = argv[1];
    if (argc >= 3) output_file_name = argv[2];

    struct Text text = {};
    struct Text *txt = &text;
    
    ReadText (input_file_name, txt);

    FILE *out_file = fopen (output_file_name, "w");
    if (out_file == NULL) return OUTPUT_ERROR;

    qsort     ((void *) (txt -> data), txt -> len, sizeof ((txt -> data)[0]), CompFwd);
    WriteText (txt, out_file, SKIP_EMPTY);

    Quicksort ((void *) (txt -> data), txt -> len, sizeof ((txt -> data)[0]), CompBwd);
    WriteText (txt, out_file, SKIP_EMPTY);

    WriteOriginal (txt, out_file, NSKIP_EMPTY);
    
    fclose (out_file);
    FreeText (txt);

    return 0;
}

