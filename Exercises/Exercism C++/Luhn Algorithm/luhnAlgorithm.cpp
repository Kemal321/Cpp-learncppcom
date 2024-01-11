#include "luhn.h"
#include <string>
#include <cstring>
namespace luhn {
    bool nonAscii(std::string cardNumber) {
        std::string nonWhiteSpacedString{};
        for (int i{ 0 }; i < static_cast<int>(cardNumber.length()); ++i)
        {
            if (!isspace(cardNumber[i]))
                nonWhiteSpacedString = nonWhiteSpacedString + cardNumber[i];
        }
        if ((static_cast<int>(nonWhiteSpacedString.length()) <= 1)) {
            return false;
        }
        for (int i{ 0 }; i < static_cast<int>(nonWhiteSpacedString.length()); ++i) {
            int a = static_cast<int>(nonWhiteSpacedString[i]);
            if (!(a <= 57 && a >= 48)) {
                return false;
            }
        }
        return true;
    }
    bool luhnCalculator(std::string cardNumber) {
        std::string nonWhiteSpacedString{};
        for (int i{ 0 }; i < static_cast<int>(cardNumber.length()); ++i)
        {
            if (!isspace(cardNumber[i]))
                nonWhiteSpacedString = nonWhiteSpacedString + cardNumber[i];
        }
        int sum{ 0 };
        int ii{ static_cast<int>(nonWhiteSpacedString.length()) - 2 };
        int bb{ static_cast<int>(nonWhiteSpacedString.length()) - 1 };
        char ch{};
        char ch2{};
        while (true) {
            if (ii < 0) {
                break;
            }
            ch = nonWhiteSpacedString[ii];
            if (((ch - '0') * 2) > 9) {
                sum += (((ch - '0') * 2) - 9);
            }
            else {
                sum = sum + ((ch - '0') * 2);
            }

            ii -= 2;
        }
        while (true) {
            if (bb < 0) {
                break;
            }
            ch2 = nonWhiteSpacedString[bb];
            sum = sum + (ch2 - '0');
            bb -= 2;
        }
        return !(sum % 10);
    }
    bool valid(std::string cardNumber) {

        if ((static_cast<int>(cardNumber.length()) <= 1) || !nonAscii(cardNumber)) {
            return false;
        }
        if (static_cast<int>(cardNumber.length()) > 5) {
            return luhnCalculator(cardNumber);
        }
        else {
            return true;
        }
    }
}// namespace luhn