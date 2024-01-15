#include "atbash_cipher.h"
#include <string_view>
#include <string>
namespace atbash_cipher {
    std::string encode(std::string cipher) {
        std::string chipher{ " abcdefghijklmnopqrstuvwxyz" };
        std::string enc;
        int i{ 0 };
        int a{ 0 };
        int clock{ 5 };
        std::string newest{};
        while (true) {
            cipher[a] = std::tolower(cipher[a]);
            if (cipher[a] == ' ') {
                ++a;
                continue;
            }
            if ((48 <= (static_cast<int>(cipher[a])) && (static_cast<int>(cipher[a])) <= 57)) {
                newest = newest + cipher[a];
                ++a;
                continue;
            }
            else if ((97 <= (static_cast<int>(cipher[a])) && (static_cast<int>(cipher[a])) <= 122)) {
                newest = newest + chipher[(26 - (static_cast<int>(cipher[a]) - 96) + 1)];
            }
            ++a;
            if (a == static_cast<int>(cipher.length())) {
                break;
            }
        }
        while (true) {
            if (clock == 0) {
                enc = enc + ' ';
                clock = 5;
            }
            enc = enc + newest[i];
            --clock;
            ++i;
            if (i == static_cast<int>(newest.length())) {
                return enc;
            }

        }
        return enc;
    }
    std::string decode(std::string willDec) {
        std::string chipher{ " zyxwvutsrqponmlkjihgfedcba" };
        std::string dec{};
        std::string dec2{};
        int i{ 0 };
        int a{ 0 };
        while (true) {
            if (willDec[i] == ' ') {
                ++i;
                continue;
            }
            dec = dec + willDec[i];
            ++i;
            if (i == static_cast<int>(willDec.length())) {
                break;
            }
        }
        while (true) {
            if (a == static_cast<int>(dec.length())) {
                break;
            }
            if ((48 <= (static_cast<int>(dec[a])) && (static_cast<int>(dec[a])) <= 57)) {
                dec2 = dec2 + dec[a];
                ++a;
                continue;
            }
            dec2 = dec2 + chipher[(26 - (static_cast<int>(chipher.find(dec[a]))) + 1)];
            ++a;
        }
        return dec2;

    }
}  // namespace atbash_cipher