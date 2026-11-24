#include "preprocessor.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s inputfile.c\n", argv[0]);
        return 1;
    }

    char out_file[256];
    strcpy(out_file, argv[1]);

    /* Change ".c" at the end to ".i" */
    char *dot = strrchr(out_file, '.');
    if (dot != NULL && strcmp(dot, ".c") == 0) {
        strcpy(dot, ".i");
    } else {
        strcat(out_file, ".i");
    }

    remove_comments_file(argv[1], "step1_no_comments.tmp");
    handle_includes_file("step1_no_comments.tmp", "step2_with_includes.tmp");
    handle_macros_file("step2_with_includes.tmp", out_file);

    remove("step1_no_comments.tmp");
    remove("step2_with_includes.tmp");

    printf("Done! Created %s\n", out_file);
    return 0;
}