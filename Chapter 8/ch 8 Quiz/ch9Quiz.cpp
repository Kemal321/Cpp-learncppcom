/*In a quiz for lesson 8.x -- Chapter 8 summary and quiz, we implemented a game of Hi-Lo.

Update your previous solution to handle invalid guesses (e.g. ‘x’), out of bounds guesses (e.g. 0 or 101), or valid guesses that have extraneous characters (e.g. 43x). Also handle the user entering extra characters when the game asks them whether they want to play again.

Hint: Write a separate function to handle the user inputting their guess (along with the associated error handling).*/
#include <iostream>
#include "Random.h" // https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/
#include <limits>
// returns true if the user won, false if they lost
void ignoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
int getGuess(int count) {
	std::cout << "Guess #" << count << ": ";
	int guess{};
	std::cin >> guess;
	while(true){
		if (guess < 0 || guess > 100 || !std::cin) {
			std::cin.clear();
			ignoreLine();
			std::cout << "Please enter your guess as an integer between 0 - 100: ";
			std::cin >> guess;
			continue;
		}
		return guess;
	}
}
bool playGame(int guesses, int number)
{
	// Loop through all of the guesses
	for (int count{ 1 }; count <= guesses; ++count)
	{

		int guess = getGuess(count);

		if (guess > number)
			std::cout << "Your guess is too high.\n";
		else if (guess < number)
			std::cout << "Your guess is too low.\n";
		else // guess == number
			return true;
	}

	return false; // if the user lost
}

bool playAgain()
{
	// Keep asking the user if they want to play again until they pick y or n.
	while (true)
	{
		char ch{};
		std::cout << "Would you like to play again (y/n)? ";
		std::cin >> ch;

		switch (ch)
		{
		case 'y': return true;
		case 'n': return false;
		}
	}
}

int main()
{
	constexpr int guesses{ 7 }; // the user has this many guesses

	do
	{
		int number{ Random::get(1,100) }; // this is the number the user needs to guess

		std::cout << "Let's play a game. I'm thinking of a number between 1 and 100. You have " << guesses << " tries to guess what it is.\n";

		bool won{ playGame(guesses, number) };
		if (won)
			std::cout << "Correct! You win!\n";
		else
			std::cout << "Sorry, you lose. The correct number was " << number << '\n';
	} while (playAgain());

	std::cout << "Thank you for playing.\n";

	return 0;
}