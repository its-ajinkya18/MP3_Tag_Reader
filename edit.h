#ifndef EDIT_H
#define EDIT_H

#include<stdio.h>
#include<string.h>
#include"types.h"

#define MAX_TAG_SIZE 5
typedef struct
{
    FILE *src_fptr;
    FILE *dest_fptr;
    char src_fname[20];
    char dest_fname[20];
    uint src_size;
    uint dest_size;
    char src_tag_name[MAX_TAG_SIZE];
    char edit_tag_name[MAX_TAG_SIZE];
    char new_data[100];
    uint size_new_data;
}EditInfo;

/* Read and Validation for edit */
Status read_and_validation_for_edit(int argc, char *argv[], EditInfo *edit);

/* Perform edit operation */
Status do_edit(EditInfo *edit);

/* Open files */
Status open_file_for_edit(EditInfo *edit);

/* Copy header data */
Status copy_header(EditInfo *edit);

/* edit content */
Status edit_content(EditInfo *edit);

/* Copy tag and data */
Status copy_tag_and_data(char read_tag[], EditInfo *edit);

/* Copy remaining data */
Status copy_remaining_data(EditInfo *edit);

/* Remove and rename */
Status remove_and_rename(EditInfo *edit);

#endif