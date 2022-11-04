# morse
Header only C library to generate morse code

## Usage

To get cstring representation of character:

```c
#include <stdio.h>
#include "morse.h"

int main(void) {
    // obtain bit representation of code sequence and bits count
    uint8_t bits, bits_n;
    int e = char_bits('a', &bits, &bits_n);
    if(e) {
        return e;
    }

    // convert bits to code sequence
    const char* seq = code_seq(bits, bits_n);
    printf("'a' in morse is: %s\n", str);
}
```

To iterate over raw sequence bits (dots and dashes):

```c
#include <stdio.h>
#include "morse.h"

int main(void) {
    // obtain bit representation of code sequence and bits count
    uint8_t bits, bits_n;
    int e = char_bits('a', &bits, &bits_n);
    if(e) {
        return e;
    }

    // iterate over raw bits
    printf("'a' in morse is: ");
    for(int i = 0; i < bits_n; i++) {
        char bit = get_bits(bits, i, 1) ? '-' : '.';
        printf("%c", bit);
    }
}
```
