# Custom C Preprocessor (`mypreprocessor`)

A lightweight, modular C preprocessor built from scratch in C. It processes a `.c` source file by removing comments, expanding `#include` directives, and substituting `#define` macros to generate an extended `.i` source file.

## Features

- **Comment Removal (`comment_removal.c`)**: Strips single-line (`//`) and multi-line (`/* ... */`) comments while preserving line structure and readability.
- **File Inclusion (`file_inclusion.c`)**: Expands `#include <filename>` directives by inserting the contents of the referenced header file.
- **Macro Substitution (`macro_handler.c`)**: Parses and replaces `#define` directives for both:
  - Simple object-like macros (e.g., `#define PI 3.14`)
  - Function-like macros with arguments (e.g., `#define SQUARE(x) ((x)*(x))`)
- **Automated Build (`Makefile`)**: Compiles all modular `.c` and `.h` files into the `mypreprocessor` executable.

## Build & Run

1. **Compile the project:**
   ```bash
   make
   ```

2. **Run the preprocessor on a C source file:**
   - **Linux / macOS / Git Bash:**
     ```bash
     ./mypreprocessor inputfile.c
     ```
   - **Windows (PowerShell / Command Prompt):**
     ```bat
     .\mypreprocessor.exe inputfile.c
     ```

3. **Output:**
   Generates `inputfile.i` in the same directory containing the preprocessed source code.

4. **Clean build artifacts:**
   ```bash
   make clean
   ```
