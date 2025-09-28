#include"view.h"

void display_help()
{
    printf("MP3 Tag Reader\n");
    printf("1. -v -> to view mp3 file contents\n");
    printf("2. -e -> to edit mp3 file contents\n");
    printf("\tEdit tags --> -t/-a/-A/-y/-m/-c\n");
    printf("\t2.1  -t -> to edit song title\n\t2.2  -a -> to edit artist name\n\t2.3  -A -> to edit album name\n\t2.4  -y -> to edit year\n\t2.5  -m -> to edit content\n\t2.6  -c -> to edit comment\n");
    printf("3. --help -> to view help\n");
}