#include "onegin.h"


int main(int argc, char *argv[])
{
    char  input_file_name[MAXLEN] =  "input.txt";
    char output_file_name[MAXLEN] = "output.txt";
    
    if (argc >= 2 && strlen(argv[1]) < MAXLEN) strcpy ( input_file_name, argv[1]);
    if (argc >= 3 && strlen(argv[2]) < MAXLEN) strcpy (output_file_name, argv[2]);

    FILE *inp_file = NULL;
    FILE *out_file = NULL;

    if ((inp_file = fopen( input_file_name, "r")) == NULL) return  INPUT_ERROR;
    if ((out_file = fopen(output_file_name, "w")) == NULL) return OUTPUT_ERROR;

    char **data = 0;
    char *buffer = 0;

    size_t len = 0;

    data = read_data (inp_file, &len);
    fclose (inp_file);

    buffer = *data;

    sort_data (data, len, comp1);
    write_data (data, out_file);

    fprintf(out_file, "\n\n");

    sort_data (data, len, comp2);
    write_data (data, out_file);

    fprintf(out_file, "\n\n");

    write_buf (buffer, len, out_file);
    
    fclose (out_file);

    free ((void *)data);
    free ((void *)buffer);

    return 0;
}