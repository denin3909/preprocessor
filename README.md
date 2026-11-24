# Custom C Preprocessor (`mypreprocessor`)

A lightweight, modular C preprocessor built from scratch in C. It processes a `.c` source file by removing comments, expanding `#include` directives, and substituting `#define` macros to generate an extended `.i` source file.

## Features

- **Comment Removal (`comment_removal.c`)**: Strips single-line (`//`) and multi-line (`/* ... */`) comments while preserving line structure and readability.
- **File Inclusion (`file_inclusion.c`)**: Expands `#include <filename>` directives by inserting the contents of the referenced header file.
- **Macro Substitution (`macro_handler.c`)**: Parses and replaces `#define` directives for both:
  - Simple object-like macros (e.g., `#define PI 3.14`)
  - Function-like macros with arguments (e.g., `#define SQUARE(x) ((x)*(x))`)
- **Automated Build (`Makefile`)**: Compiles all modular `.c` and `.h` files into the `mypreprocessor` executable.

To compile the project - make
To run the project     -  .\mypreprocessor.exe inputfile.c(for windows)