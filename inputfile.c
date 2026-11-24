#include <test.h>
#define PI 3.14
#define SQUARE(x) ((x)*(x))

// Single-line comment should disappear
/* Multi-line comment
   should also disappear */
int main(void) {
    double val = PI * SQUARE(5);
    return add_two((int)val);
}
