#include "preprocessor.h"
#include <stdio.h>
#include <string.h>

void handle_includes_file(const char *in_file, const char *out_file) {
    FILE *in = fopen(in_file, "r");
    FILE *out = fopen(out_file, "w");
    if (!in || !out) {
        printf("Cannot open file in file_inclusion\n");
        return;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), in) != NULL) {
        char *open_bracket = strchr(line, '<');
        char *close_bracket = strchr(line, '>');

        if (strstr(line, "#include") != NULL && open_bracket != NULL && close_bracket != NULL) {
            char filename[256];
            int len = (int)(close_bracket - open_bracket - 1);
            strncpy(filename, open_bracket + 1, len);
            filename[len] = '\0';

            FILE *inc = fopen(filename, "r");
            if (inc != NULL) {
                char inc_line[MAX_LINE];
                while (fgets(inc_line, sizeof(inc_line), inc) != NULL) {
                    fputs(inc_line, out);
                }
                fputs("\n", out);
                fclose(inc);
            } else {
                printf("Could not open header: %s\n", filename);
            }
        } else {
            fputs(line, out);
        }
    }

    fclose(in);
    fclose(out);
}