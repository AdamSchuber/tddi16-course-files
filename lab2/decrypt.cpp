#include <iostream>
#include <chrono>
#include <string>
#include "key.h"
#include <unordered_map>
#include <vector>
#include <cmath>
#include <functional>

using namespace std;

// struct KeyHash {
//     size_t operator()(const Key& k) const {
//         string str{};
//         for (int i{}; i < N; ++i) {
//             if (k.bit(i))
//                 str.push_back('1');
//             else
//                 str.push_back('0');
//         }
//         return hash<string>{}(str);
//     }
// };

namespace std 
{
    template <>
    struct hash<Key> {
        size_t operator()(const Key &k) const {  // djb2
            size_t result = 5381;
            for (int i{}; i < N; ++i) {
                if (k.bit(i))
                    result = ((result << 5) + result) + i; 
            }
            return result;
        }
    };
}

int main(int argc, char *argv[]) {
    if (argc != 2)
    {
        cout << "Usage:" << endl;
        cout << argv[0] << " <hashed password> < rand8.txt" << endl;
        return 1;
    }

    // Hashed password.
    Key hashed{argv[1]};

    // Table.
    Key table[N];

    // Read table.
    for (int i{0}; i < N; i++) {
        string buffer;
        if (!(cin >> buffer)) {
            cerr << "Too short table!" << endl;
            return 1;
        }
        table[i] = Key{buffer.c_str()};
    }

    auto begin = chrono::high_resolution_clock::now();

    // count middle
    Key half{};
    int middle{static_cast<int>(pow(2, (N / 2)))};
    for (int i{}; i < middle; ++i) {
        ++half;
    }

    // first half
    //unordered_map<Key, vector<Key>, KeyHash> m;
    unordered_map<Key, vector<Key>> m;
    Key lower{};
    Key enc{};
    do {
        enc = hashed - subset_sum(lower, table);
        m[enc].push_back(lower);
        ++lower;
    } while (lower <= half);

    // second half
    Key higher{};
    Key zero{};
    do {
        higher += half;
        enc = subset_sum(higher, table);
        auto it = m.find(enc);
        if (it != m.end()) {
            for (Key candidate : it->second) {
                cout << higher + candidate << endl;
            }
        }
    } while (higher != zero);

    auto end = chrono::high_resolution_clock::now();
    cout << "Decryption took "
         << std::chrono::duration_cast<chrono::seconds>(end - begin).count()
         << " seconds." << endl;

    return 0;
}
