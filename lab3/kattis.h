#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <functional> // std::hash

using std::vector;
using std::string;

typedef unsigned char byte;

/**
 * Fil med hjälpfunktioner för att hantera tecknen å, ä, ö och é korrekt i C++, vilket krävs för en
 * accepterad lösning i Kattis.
 *
 * I C++ använder man oftast typen 'char' för att representera text. En 'char' är en byte stor, och
 * kan därför inte representera alla tecken som är definierade i Unicode-standarden. På grund av det
 * brukar man använda en teckenkodning som heter UTF-8, där alla tecken i ASCII (kör 'man ascii' i
 * terminalen för att se alla tecken i ASCII) representeras med en byte, men resten kräver flera
 * bytes. Tecknen å, ä, ö och é ligger tyvärr utanför ASCII och kommer därför vara representerade
 * som flera tecken. I detta fall representeras dem som sekvenserna 0xC3 0xA5, 0xC3 0xA4, 0xC3 0xB6
 * och 0xC3 0xA9 respektive. Detta måste vi ta hänsyn till för att kunna manipulera strängarna
 * korrekt.
 *
 * Här löser vi problemet genom att omvandla tecknen å, ä, ö och é till tecknen '{', '|', '}' och
 * '~' respektive. Det är inte den snyggaste lösningen, men i det här fallet är det smidigt eftersom
 * de tecknen ligger precis efter 'z' i ASCII. Med hjälp av den här transformationen kan vi alltså
 * fortfarande iterera över alla tecken smidigt med en loop:
 *
 * for (char i{'a'}; i <= '~'; i++)
 *
 * Den här filen implementerar två sätt att hantera strängar av den här typen. Ett manuellt sätt,
 * där du själv måste komma ihåg att anropa 'from_utf8' och 'to_utf8' på lämpliga ställen, och en
 * typ 'kattis_string' som ser till att göra det åt dig så länge du använder 'cin' och 'cout' för
 * in/utmatning. Det finns också en vector, 'alphabet', som innehåller alla tecken i alfabetet, så
 * att du enkelt kan iterera över alla tecken.
 */

/**
 * Alla tecken i alfabetet, efter transformation till ASCII.
 */
const vector<char> alphabet = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
    'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
    'y', 'z', '{', '|', '}', '~'
};

/**
 * Manuell metod:
 */

// Konvertera från UTF-8 till vår representation.
string from_utf8(const string &utf8) {
    std::ostringstream out;

    for (size_t i = 0; i < utf8.size(); i++) {
        if (byte(utf8[i]) == 0xC3) {
            switch (byte(utf8[i + 1])) {
            case 0xA5: // å
                out << '{';
                break;
            case 0xA4: // ä
                out << '|';
                break;
            case 0xB6: // ö
                out << '}';
                break;
            case 0xA9: // é
                out << '~';
                break;
            }
            i++;
        } else {
            // Kontrollera om det råkade vara iso-latin-1 i indatan (vanligt på Windows)
            switch (byte(utf8[i])) {
            case 0xE5: // å
                out << '{';
                break;
            case 0xE4: // ä
                out << '|';
                break;
            case 0xF6: // ö
                out << '}';
                break;
            case 0xE9: // é
                out << '~';
                break;
            default:
                out << utf8[i];
                break;
            }
        }
    }

    return out.str();
}

// Konvertera från vår representation tillbaka till utf-8.
string to_utf8(const string &our) {
    std::ostringstream out;

    for (auto i : our) {
        switch (i) {
        case '{':
            out << "å";
            break;
        case '|':
            out << "ä";
            break;
        case '}':
            out << "ö";
            break;
        case '~':
            out << "é";
            break;
        default:
            out << i;
            break;
        }
    }

    return out.str();
}


/**
 * Semi-automatisk metod. Så länge all in- och utmatning sker med strömmar så sköts omvandlingen
 * automatiskt.
 */
class kattis_string : public std::string {
public:
    kattis_string() : string() {}
    kattis_string(const string &src) : string(from_utf8(src)) {}
    kattis_string(const kattis_string &src) = default;
};

// Tillåt användning i unordered_set och unordered_map.
namespace std {
    template <>
    struct hash<kattis_string> {
        hash<string> original;

        std::size_t operator () (const kattis_string &k) const {
            return original(k);
        }
    };
}

std::ostream &operator <<(std::ostream &to, const kattis_string &from) {
    return to << to_utf8(from);
}

std::istream &operator >>(std::istream &from, kattis_string &to) {
    string tmp;
    if (from >> tmp)
        to = kattis_string(tmp);
    return from;
}

namespace std {

    istream &getline(istream &from, kattis_string &to) {
        string tmp;
        getline(from, tmp);
        to = tmp; // Notera: Konverterar strängen korrekt.
        return from;
    }

}
