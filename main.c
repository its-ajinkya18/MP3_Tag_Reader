#include "view.h"
#include "edit.h"

int main(int argc, char *argv[])
{
    ViewInfo view;
    EditInfo edit;

    if (argc < 2)
    {
        printf("--------------------------------------------------------------------------------------\n");
        printf("ERROR: ./a.out : INVALID ARGUMENTS\nUSAGE :\nTo view please pass like: ./a.out -v mp3filename\n");
        printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\nTo get help pass like: ./a.out --help\n");
        printf("---------------------------------------------------------------------------------------\n");
        return e_failure;
    }
    if(check_operation(argv) == e_view)
    {
        if(read_and_validation_for_view(argc, argv, &view) == e_success)
        {
            if(do_view(&view) == e_success)
                return e_success;
            else
            {
                printf("Error! Can't view details\n");
                return e_failure;
            }
        }
        else
        {
            printf("Error! Read and validation failed\n");
            printf("Can't view details\n");
            return e_failure;
        }
    }
    else if(check_operation(argv) == e_edit)
    {
        if(read_and_validation_for_edit(argc, argv, &edit) == e_success)
        {
            printf("Read and validation executed sucessfully\n");
            if(do_edit(&edit) == e_success)
            {
                printf("Data edited successfully\n");
            }
            else
            {
                printf("Error! Can't edit Information\n");
                return e_failure;
            }
        }
        else
        {
            printf("Error! Read and validation failed\n");
            printf("Can't edit Information\n");
            return e_failure;
        }
    }
    else if(check_operation(argv) == e_help)
        display_help();
    else
        printf("Unsupported operation type\n");
    return 0;
}
OperationType check_operation(char *argv[])
{
    if(strcmp(argv[1], "-v") == 0)
        return e_view;
    if(strcmp(argv[1], "-e") == 0)
        return e_edit;
    if(strcmp(argv[1], "--help") == 0)
        return e_help;
    return e_unsupported;   
}
int conversion(int num, int size)
{
    char temp;
    char *ptr = (char *)&num;
    for(int i=0;i<size/2;i++)
    {
        temp = ptr[i];
        ptr[i] = ptr[size-1-i];
        ptr[size-1-i] = temp;
    }
    return num;
}