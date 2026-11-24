#include "preprocessor.h"
#include <stdio.h>
#include <string.h>

void remove_comments_file(const char *in_file, const char *out_file) {
    FILE *in = fopen(in_file, "r");
    FILE *out = fopen(out_file, "w");
    if (!in || !out) {
        printf("Cannot open file in comment_removal\n");
        return;
    }

    char line[MAX_LINE];
    int block_comment = 0;

    while (fgets(line, sizeof(line), in) != NULL) {
        char result[MAX_LINE] = "";
        int r = 0;
        int i = 0;

        while (line[i] != '\0') {
            if (block_comment == 1) {
                if (line[i] == '*' && line[i + 1] == '/') {
                    block_comment = 0;
                    i += 2;
                } else {
                    i++;
                }
            } else if (line[i] == '/' && line[i + 1] == '/') {
                break; /* ignore rest of line */
            } else if (line[i] == '/' && line[i + 1] == '*') {
                block_comment = 1;
                i += 2;
            } else {
                result[r++] = line[i++];
            }
        }

        result[r] = '\0';
        if (block_comment == 0 && strchr(line, '\n') != NULL && strchr(result, '\n') == NULL) {
            strcat(result, "\n");
        }
        fputs(result, out);
    }

    fclose(in);
    fclose(out);
}