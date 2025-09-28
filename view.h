#ifndef VIEW_H
#define VIEW_H

#include<stdio.h>
#include<string.h>
#include"types.h"

#define MAX_TAG_SIZE 5

typedef struct
{
    // for view file
    char * v_fname;
    char tag[MAX_TAG_SIZE];
    uint size;
    FILE *fptr;

    // 2d array for storing Metadata
    char content[6][100];
}ViewInfo;

/* Check operation type */
OperationType check_operation(char *argv[]);

/* Read and Validations for  */
Status read_and_validation_for_view(int argc, char *argv[], ViewInfo *view);

/* Open file */
Status open_file_for_view(ViewInfo *view);

/* print the content */
Status print_content(ViewInfo *view, int i);

/* Start view */
Status do_view(ViewInfo *view);

/* Help operation */
void display_help();

/* Conversion Big indian to little indian */
int conversion(int num, int size);

#endif