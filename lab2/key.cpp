#include <iomanip>
#include "key.h"

Key::Key() : digit{} {}

Key::Key(const char *value) : digit{} {
    for (int i{0}; i < C; i++) {
        for (int j{0}; j < R; j++) {
            if (value[i] == ALPHABET[j])
                digit[i] = j;
        }
    } 
}

bool Key::bit(int i) const {
    return (digit[i / B] >> (B - 1 - i % B)) & 1;
}

bool Key::operator ==(const Key &other) const {
    for (int i = 0; i < C; i++) {
        if (digit[i] != other.digit[i])
            return false;
    }
    return true;
}

bool Key::operator !=(const Key &other) const {
    return !(*this == other);
}

bool Key::operator <(const Key &other) const {
    for (int i = 0; i < C; i++) {
        if (digit[i] != other.digit[i])
            return digit[i] < other.digit[i];
    }

    return false;
}

bool Key::operator >(const Key &other) const {
    return other < *this;
}

bool Key::operator <=(const Key &other) const {
    return !(*this > other);
}

bool Key::operator >=(const Key &other) const {
    return !(*this < other);
}

Key Key::operator +(const Key &other) const {
    Key c{};
    int carry{};

    for (int i{C - 1}; i >= 0; --i) {
        c.digit[i] = (digit[i] + other.digit[i] + carry) % R;
        carry      = (digit[i] + other.digit[i] + carry) >= R;
    }

    return c;
}

Key &Key::operator +=(const Key &other) {
    *this = *this + other;
    return *this;
}

Key &Key::operator ++() {
    int i{C - 1};
    byte one{1};
    byte dig  = (digit[i] + one) % R;
    int carry = (digit[i] + one) >= R;
    digit[i] = dig;

    for (i = C - 2; i >= 0; i--) {
        if (!carry)
            break;
        dig   = (digit[i] + carry) % R;
        carry = (digit[i] + carry) >= R;
        digit[i] = dig;
    }

    return *this;
}

Key Key::operator ++(int) {
    Key t = *this;
    ++*this;
    return t;
}

Key Key::operator -(const Key &other) const {
    Key c{};
    int carry{};

    // if lhs >= rhs the following will clearly work
    // if lhs < rhs we will have carry == -1 after the for loop
    // but this is ok since we are working mod 2^N
    for (int i{C - 1}; i >= 0; --i) {
        int t = (int(digit[i]) - int(other.digit[i]) + carry);
        if (t < 0) {
            carry = -1;
            c.digit[i] = byte(t + R) % R;
        } else {
            carry = 0;
            c.digit[i] = byte(t) % R;
        }
    }

    return c;
}

Key &Key::operator -=(const Key &other) {
    *this = *this - other;
    return *this;
}

std::ostream &operator <<(std::ostream &to, const Key &k) {
    for (int i{0}; i < C; i++)
        to << ALPHABET[k.digit[i]];
    to << "  ";
    for (int i{0}; i < C; i++)
        to << std::setw(2) << int(k.digit[i]) << " ";
    to << "  ";
    for (int i{0}; i < N; i++)
       to << k.bit(i);

    return to;
}


Key subset_sum(const Key &key, const Key table[N]) {
    Key sum{};
    for (int i{0}; i < N; ++i) {
        if (key.bit(i))
            sum += table[i];
    }
    return sum;
}

Key subset_sum_verbose(const Key &key, const Key table[N]) {
    Key sum{};
    for (int i{0}; i < N; ++i) {
        if (key.bit(i)) {
            sum += table[i];
            std::cout << std::setw(2) << i << " ";
            std::cout << table[i] << std::endl;
        }
    }

    return sum;
}
