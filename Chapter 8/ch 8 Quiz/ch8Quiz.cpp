#include <iostream>
#include "constants.h"
#include <cassert>
#include "Random.h"

double calculateHeight(double initialHeight, int seconds)
{
    double distanceFallen{ myConstants::gravity * seconds * seconds / 2 };
    double heightNow{ initialHeight - distanceFallen };

    // Check whether we've gone under the ground
    // If so, set the height to ground-level
    if (heightNow < 0.0)
        return 0.0;
    else
        return heightNow;
}

void calculateAndPrintHeight(double initialHeight, int time)
{
    std::cout << "At " << time << " seconds, the ball is at height: " << calculateHeight(initialHeight, time) << '\n';
}

//Question 2
/*bool isPrime(int x) {
    if (x % 2 == 0 && x != 2)
        return true;
    int counter{ 0 };
    for (int i{ 2 }; i < 10; ++i) {
        if (i == x) {
            ++counter;
            continue;
        }
        if (x % i == 0)
            ++counter;
    }
    if (x == 1)
        return false;
    return (counter > 1) ? false : true;

}*/

bool isPrime(int x)
{
    if (x <= 1)     // if x is negative, 0, or 1 then the number is not prime
        return false;
    if (x == 2)     // the number 2 is the only even prime
        return true;
    if (x % 2 == 0) // any other even number is not prime
        return false;
    // Also see https://stackoverflow.com/questions/5811151/why-do-we-check-up-to-the-square-root-of-a-number-to-determine-if-the-number-is
    for (int test{ 3 }; test <= std::sqrt(x); test += 2)
    {
        if (x % test == 0) // if x is evenly divisible
            return false;  // then this number isn't prime
    }

    return true; // if we didn't find any divisors, then x must be prime
}

void hiLo(){
    int numberForGuess{ Random::get(1,100) };
    int guess{};
    char again{};
    std::cout << "Let's play a game. I'm thinking of a number between 1 and 100. You have 7 tries to guess what it is.\n";
    for (int i{ 0 }; i < 7; ++i) {
        std::cout << "Guess #" << (i + 1) << ": ";
        std::cin >> guess;
        if (guess == numberForGuess) {
            std::cout << "Correct! You win!";
            std::cout << "Would you like to play again (y/n)?";
            std::cin >> again;
            if (again == 'y')
                hiLo();
            else
                std::cout << "Thank you for playing.";
            break;
        }

        if (guess < numberForGuess)
            std::cout << "Your guess is too low.\n";
        else
            std::cout << "Your guess is too high.\n";
    }
    std::cout << "Sorry, you lose. The correct number was " << numberForGuess;
}
int main()
{/*
    std::cout << "Enter the initial height of the tower in meters: ";
    double initialHeight{};
    std::cin >> initialHeight;
    int i{ 0 };
    while (calculateHeight(initialHeight,i) >= 0.0) {
        calculateAndPrintHeight(initialHeight, i);
        if (calculateHeight(initialHeight, i) == 0.0)
            break;
        ++i;
    }
    */
  /*  // Question 2
    assert(!isPrime(0));
    assert(!isPrime(1));
    assert(isPrime(2));
    assert(isPrime(3));
    assert(!isPrime(4));
    assert(isPrime(5));
    assert(isPrime(7));
    assert(!isPrime(9));
    assert(isPrime(11));
    assert(isPrime(13));
    assert(!isPrime(15));
    assert(!isPrime(16));
    assert(isPrime(17));
    assert(isPrime(19));
    assert(isPrime(97));
    assert(!isPrime(99));
    assert(isPrime(13417));

    std::cout << "Success!\n";
    */ 
    // Question 3
    
    hiLo();
    return 0;
}