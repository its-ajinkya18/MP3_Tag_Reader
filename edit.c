#include"edit.h"
#include"view.h"

Status open_file_for_edit(EditInfo *edit)
{
    edit->src_fptr = fopen(edit->src_fname, "r");
    if(edit->src_fptr == NULL)
    {
        perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", edit->src_fname);
    	return e_failure;
    }
    char str[10] = "dest.mp3";
    strcpy(edit->dest_fname, str);
    edit->dest_fptr = fopen(edit->dest_fname, "w");
    if(edit->dest_fptr == NULL)
    {
        perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", edit->dest_fname);
    	return e_failure;
    }
}
Status read_and_validation_for_edit(int argc, char *argv[], EditInfo *edit)
{
    if(argc != 5)
    {
        printf("Error! Invalide number of arguments passed\n");
        return e_failure;
    }
    if(strcmp(argv[2], "-t") == 0 || strcmp(argv[2], "-a") == 0 ||strcmp(argv[2], "-A") == 0 ||
    strcmp(argv[2], "-m") == 0 ||strcmp(argv[2], "-y") == 0 ||strcmp(argv[2], "-c") == 0)
    {
        if(strcmp(argv[2], "-t") == 0)
        {
            char tag[5] = "TIT2";
            strcpy(edit->edit_tag_name, tag);
        }
        if(strcmp(argv[2], "-a") == 0)
        {
            char tag[5] = "TPE1";
            strcpy(edit->edit_tag_name, tag);
        }
        if(strcmp(argv[2], "-A") == 0)
        {
            char tag[5] = "TALB";
            strcpy(edit->edit_tag_name, tag);
        }
        if(strcmp(argv[2], "-y") == 0)
        {
            char tag[5] = "TYER";
            strcpy(edit->edit_tag_name, tag);
        }
        if(strcmp(argv[2], "-m") == 0)
        {
            char tag[5] = "TCON";
            strcpy(edit->edit_tag_name, tag);
        }
        if(strcmp(argv[2], "-c") == 0)
        {
            char tag[5] = "COMM";
            strcpy(edit->edit_tag_name, tag);
        }
    }
    else
    {
        printf("Error! Invalide 3rd argument\n");
        return e_failure;
    }
    strcpy(edit->new_data, argv[3]);
    edit->size_new_data = strlen(edit->new_data);
    strcpy(edit->src_fname, argv[4]);
    if(open_file_for_edit(edit) == e_failure)
        return e_failure;
    char str[4];
    fread(str, 3, 1, edit->src_fptr);
    str[3] = '\0';
    if(strcmp(str, "ID3") != 0)
    {
        printf("Error! MP3 file not found\n");
        return e_failure;
    }
    return e_success;
}
Status do_edit(EditInfo *edit)
{
    if(copy_header(edit) == e_success)
        printf("Copy header data successfully\n");
    else
    {
        printf("Error! Copy header failed\n");
        return e_failure;
    }
    int i;
    char read_tag[5];
    for(i=0;i<6;i++)
    {
        fread(read_tag, 4, 1, edit->src_fptr);
        read_tag[4] = '\0';
        if(strcmp(edit->edit_tag_name, read_tag) == 0)
        {
            if(edit_content(edit) != e_success)
                return e_failure;
            break;
        }
        else
        {
            if(copy_tag_and_data(read_tag, edit) != e_success)
                return e_failure;
        }
    }
    if(remove_and_rename(edit) != e_success)
        return e_failure;
    return e_success;
}
Status copy_header(EditInfo *edit)
{
    rewind(edit->src_fptr);
    char buffer[10];
    fread(buffer, 10, 1, edit->src_fptr);
    fwrite(buffer, 10, 1, edit->dest_fptr);
    return e_success;
}
Status edit_content(EditInfo *edit)
{
    uint src_size;
    char flag_buffer[3];
    fwrite(edit->edit_tag_name, 4, 1, edit->dest_fptr);
    uint b_size = conversion(edit->size_new_data + 1, 4);
    fwrite(&b_size, 4, 1, edit->dest_fptr);
    fread(&src_size, 4, 1, edit->src_fptr);
    src_size = conversion(src_size, 4);
    fread(flag_buffer, 3, 1, edit->src_fptr);
    fwrite(flag_buffer, 3, 1, edit->dest_fptr);
    fwrite(edit->new_data, edit->size_new_data, 1, edit->dest_fptr);
    fseek(edit->src_fptr, src_size - 1, SEEK_CUR);
    if(copy_remaining_data(edit) != e_success)
        return e_failure;
    return e_success;
}
Status copy_tag_and_data(char read_tag[], EditInfo *edit)
{
    uint size;
    fwrite(read_tag, 4, 1, edit->dest_fptr);
    fread(&size, 4, 1, edit->src_fptr);
    fwrite(&size, 4, 1, edit->dest_fptr);
    size = conversion(size, 4);
    char flag_buffer[3];
    fread(flag_buffer, 3, 1, edit->src_fptr);
    fwrite(flag_buffer, 3, 1, edit->dest_fptr);
    char buffer[size];
    fread(buffer, size-1, 1, edit->src_fptr);
    fwrite(buffer, size-1, 1, edit->dest_fptr);
    return e_success;
}
Status copy_remaining_data(EditInfo *edit)
{
    char ch;
    while(fread(&ch, 1, 1, edit->src_fptr) > 0)
        fwrite(&ch, 1, 1, edit->dest_fptr);
    return e_success;
}
Status remove_and_rename(EditInfo *edit)
{
    remove(edit->src_fname);
    rename(edit->dest_fname, edit->src_fname);
    return e_success;
}