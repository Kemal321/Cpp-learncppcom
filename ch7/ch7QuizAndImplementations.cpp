#include <iostream>
#include "constants.h"
int sumOfX{ 0 };
int accumulate(int x);
int main()
{
	// Question-1
	std::cout << "Enter a positive number: ";
	int num{};
	std::cin >> num;

	if (num < 0){
		std::cout << "Negative number entered.  Making positive.\n";
		num = -num;
	}
	std::cout << "You entered: " << num;



	// Question-2
	std::cout << "How many students are in your class? ";
	int students{};
	std::cin >> students;


	if (students > constants::max_class_size)
		std::cout << "There are too many students in this class";
	else
		std::cout << "This class isn't too large";
	
	std::cout << accumulate(4) << '\n'; // prints 4
	std::cout << accumulate(3) << '\n'; // prints 7
	std::cout << accumulate(2) << '\n'; // prints 9
	std::cout << accumulate(1) << '\n'; // prints 10

	return 0;
}
int accumulate(int x) {	
	sumOfX += x;
	return sumOfX;
}