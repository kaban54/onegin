#include "onegin.h"

const char  INPUTNAME[] =  "input.txt";
const char OUTPUTNAME[] = "output.txt";

int main(int argc, char *argv[])
{
    char  *input_file_name = (char *)  INPUTNAME;
    char *output_file_name = (char *) OUTPUTNAME;
    
    if (argc >= 2 && strlen(argv[1]) < MAXLEN)  input_file_name = argv[1];
    if (argc >= 3 && strlen(argv[2]) < MAXLEN) output_file_name = argv[2];

    FILE *inp_file = fopen( input_file_name, "r");
    FILE *out_file = fopen(output_file_name, "w");

    if (inp_file == NULL) return  INPUT_ERROR;
    if (out_file == NULL) return OUTPUT_ERROR;
 
    struct Text txt = ReadText (inp_file);
 
    fclose (inp_file);

    Sort1 (txt);
    WriteText (txt, out_file);

    Sort2 (txt);
    WriteText (txt, out_file);

    WriteOriginal (txt, out_file);
    
    fclose (out_file);
    FreeText (txt);

    return 0;
}

