#include "view.h"

Status open_file_for_view(ViewInfo *view)
{
    view->fptr = fopen(view->v_fname, "r");
    if (view->fptr == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", view->v_fname);
    	return e_failure;
    }
    return e_success;
}
Status read_and_validation_for_view(int argc, char * argv[], ViewInfo *view)
{
    char str[4];
    if(argc == 3)
    {
        view->v_fname = argv[2];
        if(open_file_for_view(view) == e_failure)
            return e_failure;
        fread(str, 3, 1, view->fptr);
        str[3] = '\0';
        if(strcmp(str, "ID3") != 0)
        {
            printf("MP3 file not found\n");
            return e_failure;
        }
    }
    else
    {
        printf("Error! Invalide number of arguments passed\n");
        return e_failure;
    }
    return e_success;
}

Status do_view(ViewInfo *view)
{
    /* Skip Another 7 bytes */
    if (fseek(view->fptr, 7, SEEK_CUR) != 0)
    {
        perror("Error skipping bytes");
        fclose(view->fptr);
        return e_failure;
    }
    int i;
    char tag[5];
    char content[100];
    int size;
    for(i=0;i<6;i++)
    {
        fread(tag, 4, 1, view->fptr);
        strcpy(view->tag, tag);
        fread(&size, 4, 1, view->fptr);
        view->size = conversion(size, 4);
        if (fseek(view->fptr, 3, SEEK_CUR) != 0)
        {
            perror("Error skipping bytes");
            fclose(view->fptr);
            return e_failure;
        }
        fread(content, view->size - 1, 1, view->fptr);
        content[view->size-1] = '\0';
        strcpy(view->content[i], content);
        if(print_content(view, i) == e_failure)
        {
            printf("Print Metadata failed\n");
            return e_failure;
        }
    }
    printf("-------------------------------------------------------------------\n");
    return e_success;
}
Status print_content(ViewInfo *view, int i)
{
    printf("-------------------------------------------------------------------\n");
    if(strcmp(view->tag, "TIT2") == 0)
        printf("Title\t|\t%-50s|\n",view->content[i]);
    if(strcmp(view->tag, "TPE1") == 0)
        printf("Artist\t|\t%-50s|\n",view->content[i]);
    if(strcmp(view->tag, "TALB") == 0)
        printf("Album\t|\t%-50s|\n",view->content[i]);
    if(strcmp(view->tag, "TYER") == 0)
        printf("Year\t|\t%-50s|\n",view->content[i]);
    if(strcmp(view->tag, "TCON") == 0)
        printf("Content\t|\t%-50s|\n",view->content[i]);
    if(strcmp(view->tag, "COMM") == 0)
        printf("Comment\t|\t%-50s|\n",view->content[i]);
    return e_success;
}