#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#define MAX_MACROS 100
#define MAX_LINE 1024

typedef struct {
    char name[64];
    char param[64];      /* used if it has 1 argument, like x in SQUARE(x) */
    char body[256];
    int has_param;     /* 0 = simple macro, 1 = macro with argument */
} Macro;

void remove_comments_file(const char *in_file, const char *out_file);
void handle_includes_file(const char *in_file, const char *out_file);
void handle_macros_file(const char *in_file, const char *out_file);

#endif