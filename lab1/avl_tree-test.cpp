/*
 * avl_tree-test.cc    (c) Tommy Olsson, IDA, 2007-05-02
 */

// Få svenska tecken att fungera på Windows.
// Måste vara innan #include "avl_tree.h", pga bugg i Windows-SDK:
// https://developercommunity.visualstudio.com/content/problem/93889/error-c2872-byte-ambiguous-symbol.html
#ifdef _WIN32
#include <Windows.h>
struct Setup {
    Setup() {
        SetConsoleOutputCP(65001);
        SetConsoleCP(65001);
    }
} setup;
#endif

#include <iostream>
#include "avl_tree.h"

using namespace std;


int main() {
    AVL_Tree<int>  avl_tree;

    for (int i = 1; i <= 11; i++)
        avl_tree.insert(i);

    // avl_tree.insert(9);
    // avl_tree.insert(11);
    // avl_tree.insert(4);

    // avl_tree.insert(10);
    // avl_tree.insert(12);
    // avl_tree.insert(13);
    
    // avl_tree.insert(2);
    // avl_tree.insert(6);
    // avl_tree.insert(1);

    // avl_tree.insert(3);
    // avl_tree.insert(5);

    // avl_tree.insert(7);
    // avl_tree.insert(8);


    try {
        cout << "AVL-träd efter insättning av 1, 2,..., 11:\n\n";
        avl_tree.print_tree(cout);
        cout << endl;
    } catch (const exception& e) {
        cout << '\n' << e.what() << endl;
        cout << "AVL-träd innehåller efter insättning av 1, 2,..., 11:\n\n";
        avl_tree.print(cout);
        cout << endl;
    }

    unsigned int choice;
    unsigned int value;

    while (true) {
        cout << endl;
        cout << "1 - Sätt in.\n";
        cout << "2 - Ta bort.\n";
        cout << "3 - Sök värde.\n";
        cout << "4 - Sök minsta.\n";
        cout << "5 - Sök största.\n";
        cout << "6 - Töm trädet.\n";
        cout << "7 - Skriv ut ordnat.\n";
        cout << "8 - Skriv ut träd.\n";
        cout << "0 - Avsluta.\n" << endl;
        cout << "Val: ";
        cin >> choice;
        cout << endl;

        try {
            switch (choice) {
            case 0:
                cout << "Slut." << endl;
                return 0;
            case 1:
                cout << "Värde att sätta in: ";
                cin >> value;
                avl_tree.insert(value);
                break;
            case 2:
                cout << "Värde att ta bort: ";
                cin >> value;
                avl_tree.remove(value);
                break;
            case 3:
                cout << "Värde att söka efter: ";
                cin >> value;
                if (avl_tree.member(value))
                    cout << "Värdet " << value << " finns i trädet." << endl;
                else
                    cout << "Värdet " << value << " finns ej i trädet." << endl;
                break;
            case 4:
                if (avl_tree.empty())
                    cout << "Trädet är tomt!" << endl;
                else
                    cout << "Minsta värdet i trädet är " << avl_tree.find_min() << endl;
                break;
            case 5:
                if (avl_tree.empty())
                    cout << "Trädet är tomt!" << endl;
                else
                    cout << "Största värdet i trädet är " << avl_tree.find_max() << endl;
                break;
            case 6:
                /* Detta borde förstås bekräftas! */
                avl_tree.clear();
                cout << "Trädet är tömt!" << endl;
                break;
            case 7:
                if (avl_tree.empty()) {
                    cout << "Trädet är tomt!" << endl;
                } else {
                    avl_tree.print(cout);
                    cout << endl;
                }
                break;
            case 8:
                if (avl_tree.empty()) {
                    cout << "Trädet är tomt!" << endl;
                } else {
                    avl_tree.print_tree(cout);
                    cout << endl;
                }
                break;
            default:
                cout << "Felaktigt val!" << '\b' << endl;
                break;
            }
        } catch (const exception& e) {
            cout << e.what() << endl;
        } catch (...) {
            cout << "Ett okänt fel har inträffat." << endl;
        }
    }

    return 0;
}
