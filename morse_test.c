#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "morse.h"

static int exitcode = 0;

void assert(int b, const char* format, ...) {
    if(!b) {
        va_list argptr;
        va_start(argptr, format);
        vfprintf(stderr, format, argptr);
        fprintf(stderr, "\n");
        va_end(argptr);
        exitcode = 1;
    }
}

int main(void) {
     typedef struct testcase {
        char c;
        const char* expect_seq;
    } testcase;

    testcase testcases[] = {
        (struct testcase){.c = 'a', .expect_seq = ".-"},
        (struct testcase){.c = 'b', .expect_seq = "-..."},
        (struct testcase){.c = 'c', .expect_seq = "-.-."},
        (struct testcase){.c = 'd', .expect_seq = "-.."},
        (struct testcase){.c = 'e', .expect_seq = "."},
        (struct testcase){.c = 'f', .expect_seq = "..-."},
        (struct testcase){.c = 'g', .expect_seq = "--."},
        (struct testcase){.c = 'h', .expect_seq = "...."},
        (struct testcase){.c = 'i', .expect_seq = ".."},
        (struct testcase){.c = 'j', .expect_seq = ".---"},
        (struct testcase){.c = 'k', .expect_seq = "-.-"},
        (struct testcase){.c = 'l', .expect_seq = ".-.."},
        (struct testcase){.c = 'm', .expect_seq = "--"},
        (struct testcase){.c = 'n', .expect_seq = "-."},
        (struct testcase){.c = 'o', .expect_seq = "---"},
        (struct testcase){.c = 'p', .expect_seq = ".--."},
        (struct testcase){.c = 'q', .expect_seq = "--.-"},
        (struct testcase){.c = 'r', .expect_seq = ".-."},
        (struct testcase){.c = 's', .expect_seq = "..."},
        (struct testcase){.c = 't', .expect_seq = "-"},
        (struct testcase){.c = 'u', .expect_seq = "..-"},
        (struct testcase){.c = 'v', .expect_seq = "...-"},
        (struct testcase){.c = 'w', .expect_seq = ".--"},
        (struct testcase){.c = 'x', .expect_seq = "-..-"},
        (struct testcase){.c = 'y', .expect_seq = "-.--"},
        (struct testcase){.c = 'z', .expect_seq = "--.."},
        (struct testcase){.c = '1', .expect_seq = ".----"},
        (struct testcase){.c = '2', .expect_seq = "..---"},
        (struct testcase){.c = '3', .expect_seq = "...--"},
        (struct testcase){.c = '4', .expect_seq = "....-"},
        (struct testcase){.c = '5', .expect_seq = "....."},
        (struct testcase){.c = '6', .expect_seq = "-...."},
        (struct testcase){.c = '7', .expect_seq = "--..."},
        (struct testcase){.c = '8', .expect_seq = "---.."},
        (struct testcase){.c = '9', .expect_seq = "----."},
        (struct testcase){.c = '0', .expect_seq = "-----"},
    };

    for(int i = 0; i < sizeof(testcases)/sizeof(testcase); i++) {
        testcase tc = testcases[i];

        uint8_t bits = 0;
        uint8_t bits_n = 0;
        int e = char_bits(tc.c, &bits, &bits_n);
        assert(e == 0, "[%s:%d] unexpected non-zero return code %d for '%c'", __FILE__, __LINE__, e, tc.c);

        const char* seq = code_seq(bits, bits_n);
        assert(strcmp(tc.expect_seq, seq) == 0, "[%s:%d] sequences not equal for '%c': expected '%s', got '%s'", __FILE__, __LINE__, tc.c, tc.expect_seq, seq);
    }

    return exitcode;
}