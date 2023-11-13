// #include <iostream> Gerek yok zaten diðerinde ekli orada kullanýyoruz main fonksiyonu olarak zaten bir girdi çýktý iþlemi ile uðraþmýyoruz. 
#include "io.h"
/*Commented for quiz question 3
int readNumber();
void writeAnswer(int num1, int num2);
*/
int main()
{
    int num1{ readNumber() };
    int num2{ readNumber() };
    writeAnswer(num1, num2);
    return 0;

}
/*
int readNumber() {
    std::cout << "Enter an integer: ";
    int number{};
    std::cin >> number;

    return number;
}

void writeAnswer(int num1, int num2) {
    std::cout << "The answer is " << (num1 + num2 );
}*/

/*AUTHOR'S SOLUTÝON 
#include <iostream>

int readNumber()
{
    std::cout << "Enter a number to add: ";
    int x {};
    std::cin >> x;
    return x;
}

void writeAnswer(int x)
{
    std::cout << "The answer is " << x << '\n';
}

int main()
{
    int x { readNumber() };
    int y { readNumber() };
    writeAnswer(x + y); // using operator+ to pass the sum of x and y to writeAnswer()
    return 0;
}*/