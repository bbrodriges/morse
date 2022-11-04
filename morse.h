#ifndef __MORSE_H
#define __MORSE_H

#include <errno.h>
#include <stdlib.h>

#if defined(CHAR_BIT) && CHAR_BIT < 8
    #error CHAR_BIT must be at least 8
#endif // CHAR_BIT

#define SIZE_BITS 3

/** Each uint8_t is a set of bits of morse code.
 * First 3 bits is a number of valuable bits of actual code sequence,
 * up to 5 next bits is code sequence itself.
 * In code sequence part bit 1 represents dash and 0 represents dot.
 *
 * For the letter X bits are as follows:
 * 
 * |    0    |  1  0  0  1  |  1  0  0  |
 *  ------------------------------------
 * | padding |  -  *  *  -  | 3bit size |
 */
static const uint8_t codes[36] = {
    0b10010,    // A
    0b0001100,  // B
    0b0101100,  // C
    0b001011,   // D
    0b0001,     // E
    0b0100100,  // F
    0b011011,   // G
    0b0000100,  // H
    0b00010,    // I
    0b1110100,  // J
    0b101011,   // K
    0b0010100,  // L
    0b11010,    // M
    0b01010,    // N
    0b111011,   // O
    0b0110100,  // P
    0b1011100,  // Q
    0b010011,   // R
    0b000011,   // S
    0b1001,     // T
    0b100011,   // U
    0b1000100,  // V
    0b110011,   // W
    0b1001100,  // X
    0b1101100,  // Y
    0b0011100,  // Z
    0b11111101, // 0
    0b11110101, // 1
    0b11100101, // 2
    0b11000101, // 3
    0b10000101, // 4
    0b00000101, // 5
    0b00001101, // 6
    0b00011101, // 7
    0b00111101, // 8
    0b01111101, // 9
};

/** Returns requested number of bits from number
 * @param bits bits to extract from
 * @param i start bit
 * @param n number of bits to extract
 * @returns desired bits in form of integer value
 */
inline extern const uint8_t get_bits(uint8_t number, uint8_t i, uint8_t n) {
    return (((1 << n) - 1) & (number >> i));
}

/** Returns bits and their count for given morse character
 * @param c desired character
 * @param bits pointer to load morse sequence bits to
 * @param bits_n pointer to load number of morse sequence bits to
 * @returns non-zero int if error occured
 */
int char_bits(const char c, uint8_t* bits, uint8_t* bits_n) {
    char lc = c >= 'A' && c <= 'Z' ? c|0x60 : c;
    bool is_char = lc >= 'a' && lc <= 'z';
    bool is_digit = lc >= '0' && lc <= '9';
    if(!is_char && !is_digit) {
        return EINVAL;
    }

    uint8_t i = is_char ? lc - 'a' : ('z' - 'a') + (lc - '0') + 1;
    *bits_n = get_bits(codes[i], 0, SIZE_BITS);
    *bits = get_bits(codes[i], SIZE_BITS, *bits_n);
    return 0;
}

/** Returns character representation of morse sequence from bits of length bits_n
 * @param bits bits
 * @param bits_n number of morse sequence bits
 * @returns null-terminated cstring of morse codes
 */
const char* code_seq(uint8_t bits, uint8_t bits_n) {
    char* seq = malloc(sizeof(char)+1);
    seq[bits_n+1] = '\0';
    for(int i = 0; i < bits_n; i++) {
        seq[i] = get_bits(bits, i, 1) ? '-' : '.';
    }
    return seq;
}

#endif // __MORSE_H