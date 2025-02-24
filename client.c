#include "curl.c"
#include <stdio.h>

int main(int argc, char** argv)
{
    if(argc < 2) {
        printf("No arguments given.");
        return 1;
    }

    for(int i = 1; i < argc; i++) {
        printf("%s\n", argv[i]);
        make_file_post_req(argv[1], "./client.c");
    }

    return 0;
}
