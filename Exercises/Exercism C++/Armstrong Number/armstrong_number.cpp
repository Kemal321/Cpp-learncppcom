#include "armstrong_numbers.h"
#include <cmath>
namespace armstrong_numbers {
bool is_armstrong_number(int number) {
    if (number <= 0)
        return true;
    int digit = std::log10(number) + 1;
    int digitt = std::log10(number) + 1;
    int sum{ 0 };
    int numCon{ number };
    int digit_seperator{ static_cast<int>(std::pow(10, (digit - 1))) };
    while (digit != 0) {
        int new_number = number / digit_seperator;
        sum += static_cast<int>(std::pow(new_number, digitt));
        number -= (new_number * digit_seperator);
        digit_seperator /= 10;
        --digit;
    }
    if (sum == numCon)
        return true;
    else
        return false;
}
}  // namespace armstrong_numbers
