#include<iostream>

/*
void doNothing(int&) // Don't worry about what & is for now, we're just using it to trick the compiler into thinking variable x is used
{
}
*/
int main() {
	/*
		std::cout << 3;   -> Stands for console output in input/output library std::cout We can print anything text, characters or numbers


		*/


		/*

		int myNumber{ 3 };

		std::cout <<"This was my class number when I was in middle school: "<< myNumber;

		*/

		/*
		**********std::cin -> Console input uses extraction operator >>
		*
		*
		// EXAMPLE 1

		std::cout << "Enter a number: "; // ask user for a number

		int x{ }; // define variable x to hold user input (and zero-initialize it)
		std::cin >> x; // get number from keyboard and store it in variable x

		std::cout << "You entered " << x << '\n';




		// EXAMPLE 2
		std::cout << "Enter two numbers separated by a space: ";

		int x{ }; // define variable x to hold user input (and zero-initialize it)
		int y{ }; // define variable y to hold user input (and zero-initialize it)
		std::cin >> x >> y; // get two numbers and store in variable x and y respectively

		std::cout << "You entered " << x << " and " << y << '\n';

		*/


		/// QUESTÝON 1 
		/*A- You entered 0
		  B- You entered 3 in two cases
		  C- You entered 0
		  D- You entered 2147483647
		  E- input 123abc output: You entered 123
		  */


		  /*
		  std::cout << "Enter a number: "; // ask user for a number
		  int x{}; // define variable x to hold user input
		  std::cin >> x; // get number from keyboard and store it in variable x
		  std::cout << "You entered " << x << '\n';
		  return 0;
		  */


		  /*Baþlatýlmamýþ deðiþkeni kullanmaya izin vermiyor. Sonunda oldu
		  Ve sonuç gösterdi ki This is the primary reason for the “always initialize your variables” best practice.


		  // define an integer variable named x
		  int x; // this variable is uninitialized because we haven't given it a value
		  doNothing(x);
		  // print the value of x to the screen
		  std::cout << x << '\n'; // who knows what we'll get, because x is uninitialized



		  Adlandýrmalar kýsaca :genel bir kural olarak, bir tanýmlayýcýnýn uzunluðunu kullaným sýklýðýna orantýlý hale getirmek iyidir.
		  */

	/*
	* 
	* 
	//Multiply by 2 Exercise chapter 1.10
	std::cout << "Enter an integer: ";
	int givenNum{  };

	std::cin >> givenNum;

	std::cout << "Double "<< givenNum <<" is: " << (givenNum * 2) << std::endl ;
	std::cout << "Triple " << givenNum << " is: " << (givenNum * 3) << "\n";


	*/

	int firstNumber{};
	int secondNumber{};

	std::cout << "Enter an integer: ";
	std::cin >> firstNumber;

	std::cout << "Enter another integer: ";
	std::cin >> secondNumber;

	std::cout << firstNumber << " + " << secondNumber << " is: " << firstNumber + secondNumber << "." << '\n';
	std::cout << firstNumber << " - " << secondNumber << " is " << firstNumber - secondNumber <<"."<< std::endl;


	/*
	
	Chapter 1 bitti hocanýn son dersi 1.x kýsmýndaki özet kýsým güzeldi onlar okunabilir. 27.06.2023 17.01 de bitti


	
	
	
	
	
	
	*/






	return 0;
}