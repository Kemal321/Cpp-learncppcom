#include <iostream>
#include <string>
#include <cmath>

int to_decimal(std::string trinaryNumber);           // This function will print output
int string_to_integer(std::string strToNumber);      // This Function makes string to integer
std::string concatenationBack(int numberForTrinary); // This function will give you trinary number back as a string ( !!! Reversed number )
std::string lastVersionTrinary(std::string trinaryNumber); 
int to_decimal2(std::string trinaryNumber);


int char_to_int(char ch) {
    return ch - '0';
}

int to_decimal2(std::string trinaryNumber) {
    int sum = 0;

    for (int i = 0; i < static_cast<int>(trinaryNumber.length()); ++i) {
        char ch = trinaryNumber[i];
        int digit = char_to_int(ch);
        int power = static_cast<int>(trinaryNumber.length()) - 1 - i;
        sum += digit * std::pow(3, power);
    }

    return sum;
}

int main()
{
   
    std::cout << to_decimal2("101");
    return 0;
}

int to_decimal(std::string trinaryNumber) {

    int firstInt{ string_to_integer(trinaryNumber) };
    std::string firstStr{ concatenationBack(firstInt) };
    std::string firstTri{ lastVersionTrinary(firstStr) };
    return string_to_integer(firstTri);   

}
int string_to_integer(std::string trinaryNumber) {
    int counter{ 0 };
    char convert{};
    int swithKey{};
    int sum{ 0 };
    while (counter <= (static_cast<int>(trinaryNumber.length()) - 1)) {
        convert = trinaryNumber[counter];
        swithKey = static_cast<int>(convert);
        ++counter;
        switch (swithKey)
        {
        case 49:
            sum += (1 * std::pow(10, (static_cast<int>(trinaryNumber.length()) - counter)));
            break;
        case 50:
            sum += (2 * std::pow(10, (static_cast<int>(trinaryNumber.length()) - counter)));
            break;
        case 51:
            sum += (3 * std::pow(10, (static_cast<int>(trinaryNumber.length()) - counter)));
            break;
        case 52:
            sum += (4 * std::pow(10, (static_cast<int>(trinaryNumber.length()) - counter)));
            break;
        case 53:
            sum += (5 * std::pow(10, (static_cast<int>(trinaryNumber.length()) - counter)));
            break;
        case 54:
            sum += (6 * std::pow(10, (static_cast<int>(trinaryNumber.length()) - counter)));
            break;
        case 55:
            sum += (7 * std::pow(10, (static_cast<int>(trinaryNumber.length()) - counter)));
            break;
        case 56:
            sum += (8 * std::pow(10, (static_cast<int>(trinaryNumber.length()) - counter)));
            break;
        case 57:
            sum += (9 * std::pow(10, (static_cast<int>(trinaryNumber.length()) - counter)));
            break;
        default:
            break;
        }
    }
    return sum;

}

std::string concatenationBack(int numberForTrinary) {

    std::string concatenatedTrinaryNumber{};
    while( true ) {
        concatenatedTrinaryNumber = concatenatedTrinaryNumber +  (std::to_string(numberForTrinary % 3));
        numberForTrinary = numberForTrinary / 3;
        if (numberForTrinary < 3) {
            concatenatedTrinaryNumber = concatenatedTrinaryNumber + (std::to_string(numberForTrinary));
            break;
        }
    }
    return concatenatedTrinaryNumber;
}
std::string lastVersionTrinary(std::string trinaryNumber) {

    std::string reversedTrinary{};
    int counter{(static_cast<long int>(trinaryNumber.length()) - 1) };
    for (int i{ 1 }; i <= trinaryNumber.length(); ++i) {
        reversedTrinary += trinaryNumber[counter];
        --counter;
    }
    return reversedTrinary;

}