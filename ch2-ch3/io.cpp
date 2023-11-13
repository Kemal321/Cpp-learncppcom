#include <iostream>
#include "io.h"

int readNumber() {
    std::cout << "Enter an integer: ";
    int number{};
    std::cin >> number;

    return number;
}

void writeAnswer(int num1, int num2) {
    std::cout << "The answer is " << (num1 + num2);
}
