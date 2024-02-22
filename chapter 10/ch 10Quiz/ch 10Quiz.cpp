#include <iostream>
// Question 1
/*What type of conversion happens in each of the following cases? Valid answers are: No conversion needed, numeric promotion,
numeric conversion, won’t compile due to narrowing conversion. Assume int and long are both 4 bytes.*/
using Degrees = double;
using Radians = double;
namespace constants
{
    inline constexpr double pi{ 3.14159 };
}

Degrees convertToRadians(Degrees degrees)
{
    return degrees * constants::pi / 180;
}

int main()
{
    // Question 1
    int a{ 5 }; // 1a
    int b{ 'a' }; // 1b
    int c{ 5.4 }; // 1c
    int d{ true }; // 1d
    int e{ static_cast<int>(5.4) }; // 1e

    double f{ 5.0f }; // 1f
    double g{ 5 }; // 1g

    // Extra credit section
    long h{ 5 }; // 1h

    float i{ f }; // 1i (uses previously defined variable f)
    float j{ 5.0 }; // 1j
    /* 
    Answers
    -------
    1- No conversion needed. + 
    2- char to int numeric promotion + 
    3- double to int numeric conversion - False because there is a narrowing conversion. It mean that it won't compile
    4- bool to int numeric promotion +
    5- double to int numeric conversion +
    6- float to double numeric promotion + 
    7- int to double numeric conversion +
    8- int to long numeric promotion  - This is a trivial but still a conversion. The answer is numeric conversion
    9- double to float won't compile narrowing conversion +
    10- double to float won't compile narrowing conversion +
    */

    // Question 2.1 -  Upgrade the following program using type aliases :
    std::cout << "Enter a number of degrees: ";
    Degrees degrees{};
    std::cin >> degrees;

    Radians radians{ convertToRadians(degrees) };
    std::cout << degrees << " degrees is " << radians << " radians.\n";
    // Question 2.2 - Given the definitions for degrees and radians in the previous quiz solution, explain why the following 
    // statement will or won’t compile:
    // radians = degrees; -> This statement will compile I think because radians is a variable in double type and 
    // degrees also is a variable in double type.And there is no narrowing conversion it just assignment degrees value 
    // to radians variable.
    return 0;
}
