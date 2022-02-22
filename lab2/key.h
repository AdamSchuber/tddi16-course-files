#ifndef KEY_H
#define KEY_H

#include <iostream>

#define C 10         // number of characters in password
#define B 5         // number of bits per character
#define R (1 << B)  // size of alphabet (32)
#define N (B * C)   // number of bits per password

#define ALPHABET "abcdefghijklmnopqrstuvwxyz012345"

typedef unsigned char byte;

/**
 * Representation of a decimal number in base R (size of the alphabet). Addition
 * and subtraction are performed modulo 2^N.
 */
class Key {
public:
    // Initialize to zero.
    Key();

    // Initialize to the number specified by the string in the parameter.
    Key(const char *value);

    // The actual data for all digits. Each digit is in the range 0-(R-1).
    byte digit[C];

    // Check if bit number 'i' is set.
    bool bit(int i) const;

    // Comparison operators.
    bool operator ==(const Key &other) const;
    bool operator !=(const Key &other) const;
    bool operator >(const Key &other) const;
    bool operator <(const Key &other) const;
    bool operator >=(const Key &other) const;
    bool operator <=(const Key &other) const;

    // Arithmetic operations.
    Key operator +(const Key &other) const;
    Key operator -(const Key &other) const;

    Key &operator ++();
    Key operator ++(int);

    Key &operator +=(const Key &other);
    Key &operator -=(const Key &other);
};

// Output a string representation of a key.
std::ostream &operator <<(std::ostream &to, const Key &k);

// Perform a subset sum operation. Add all elements in table[i] for which i:th bit
// in 'key' is set.
Key subset_sum(const Key &key, const Key table[N]);

// Like above, but will output all keys actually selected.
Key subset_sum_verbose(const Key &key, const Key table[N]);

#endif
