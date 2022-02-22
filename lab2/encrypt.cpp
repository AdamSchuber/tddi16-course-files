/**********************************************************************
 *  Encrypt a file using subset-sum algorithm.
 *
 *  Execution:      % encrypt password < rand8.txt
 *                  vbskbezp
 *
 *  Note: need to set C = 8 in key.h before compiling and executing
 *        with rand8.txt.
 *
 **********************************************************************/

#include <iostream>
#include "key.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage:" << endl;
        cout << argv[0] << " <password> < randN.txt" << endl;
        return 1;
    }

    // Original password.
    Key password{argv[1]};
    cout << "   " << password << endl;

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

    // Compute subset sum.
    Key hashed = subset_sum_verbose(password, table);

    // Print result.
    cout << "   " << hashed << endl;
    return 0;
}
