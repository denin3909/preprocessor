#include "preprocessor.h"
#include <stdio.h>
#include <string.h>

static void replace_word(char *line, const char *old_str, const char *new_str) {
    char temp[MAX_LINE * 2];
    char *found;
    int old_len = (int)strlen(old_str);

    while ((found = strstr(line, old_str)) != NULL) {
        temp[0] = '\0';
        strncat(temp, line, (size_t)(found - line));
        strcat(temp, new_str);
        strcat(temp, found + old_len);
        strcpy(line, temp);
    }
}

void handle_macros_file(const char *in_file, const char *out_file) {
    FILE *in = fopen(in_file, "r");
    FILE *out = fopen(out_file, "w");
    if (!in || !out) {
        printf("Cannot open file in macro_handler\n");
        return;
    }

    Macro list[MAX_MACROS];
    int count = 0;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), in) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';

        if (strncmp(line, "#define ", 8) == 0 && count < MAX_MACROS) {
            char *p = line + 8;
            char *lparen = strchr(p, '(');
            char *rparen = strchr(p, ')');
            char *space = strchr(p, ' ');

            Macro m = {0};

            if (lparen != NULL && rparen != NULL && (space == NULL || lparen < space)) {
                int nlen = (int)(lparen - p);
                strncpy(m.name, p, nlen);
                m.name[nlen] = '\0';

                int plen = (int)(rparen - lparen - 1);
                strncpy(m.param, lparen + 1, plen);
                m.param[plen] = '\0';

                strcpy(m.body, rparen + 2);
                m.has_param = 1;
            } else if (space != NULL) {
                int nlen = (int)(space - p);
                strncpy(m.name, p, nlen);
                m.name[nlen] = '\0';

                strcpy(m.body, space + 1);
                m.has_param = 0;
            }

            list[count++] = m;
            fputs("\n", out);
            continue;
        }

        for (int i = 0; i < count; i++) {
            if (list[i].has_param == 0) {
                replace_word(line, list[i].name, list[i].body);
            } else {
                char prefix[128];
                snprintf(prefix, sizeof(prefix), "%s(", list[i].name);

                char *start;
                while ((start = strstr(line, prefix)) != NULL) {
                    char *arg_start = start + strlen(prefix);
                    char *arg_end = strchr(arg_start, ')');
                    if (arg_end == NULL) break;

                    char arg[256];
                    int alen = (int)(arg_end - arg_start);
                    strncpy(arg, arg_start, alen);
                    arg[alen] = '\0';

                    char expanded[512];
                    strcpy(expanded, list[i].body);
                    replace_word(expanded, list[i].param, arg);

                    char call_text[512];
                    int clen = (int)((arg_end + 1) - start);
                    strncpy(call_text, start, clen);
                    call_text[clen] = '\0';

                    replace_word(line, call_text, expanded);
                }
            }
        }

        fputs(line, out);
        fputs("\n", out);
    }

    fclose(in);
    fclose(out);
}