#include "rotational_cipher.h"
#include <iostream>
#include <string_view>
#include <cwctype>
#include <cctype>
namespace rotational_cipher {
std::string rotate(std::string ciphered, int key) {
    std::string_view plain{ "abcdefghijklmnopqrstuvwxyz" };
    std::string_view cipher{ "nopqrstuvwxyzabcdefghijklm" };
    std::string encoded{};
    
    int i{ 0 };
    int index{};
    bool flag{};
    while (true) {
        if (std::iswdigit(ciphered[i])) {
            encoded = encoded + ciphered[i];
            ++i;
            continue;
        }
        if (std::islower(ciphered[i])) {
            flag = true;
        }
        else {
            flag = false;
        }
        ciphered[i] = std::tolower(ciphered[i]);
        if (std::iswalnum(ciphered[i])) {
            index = static_cast<int>(cipher.find(ciphered[i])) + key;
            if (flag) {
                encoded = encoded + cipher[index % 26];
            }
            else {
                char a = std::toupper(cipher[index % 26]);
                encoded = encoded + a;
            }
        }
        else {
            encoded = encoded + ciphered[i];
        }
        ++i;
        if (i == static_cast<int>(ciphered.length())) {
            break;
        }
    }
    return encoded;
}
}  // namespace rotational_cipher