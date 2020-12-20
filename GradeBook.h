#pragma once
#include<string>
#include<array>
#include<iomanip>
#include<iostream>

class GradeBook {
public:
	//constant number of students who took the lecture
	static const size_t students{ 10 };

	//construcyor initializes courseName and grades array
	GradeBook(const std::string& name,
		const std::array<int, students>& gradesArray)
		:courseName{ name }, grades{ gradesArray }{}

	//function to set the course name 
	void setCourseName(const std::string& name) {
		courseName = name;
	}

	//function to retrieve the course name 
	const std::string& getCourseName() const {
		return courseName;
	}

	//display a welcome message to the GradeBook user
	void displayMessage() const {
		std::cout << "Welcome to the grade book for\n" << getCourseName() << "!" << std::endl;
	}

	//perform various operations on the data (none modify the data)
	void processGrades() const {
		outputGrades();//output graqdes array

		//call function get average to calculate the average grade 
		std::cout << std::setprecision(2) << std::fixed;
		std::cout << "\nClass average is " << getAverage() << std::endl;

		std::cout << "Lowest grade is " << getMinimum()
			<< "\nHighest grade is " << getMaximum() << std::endl;

		outputBarChart();// displat grade distribution chart
	}

	//find minmum grade
	int getMinimum() const {
		int lowGrade{ 100 }; // assume lowest grade is 100
		//loop through grades array 
		for (int grade : grades) {
			//if current grade lower than lowGrade , assign it to lowGrade
			if (grade < lowGrade) {
				lowGrade = grade;//new lowest grade
			}
		}
		return lowGrade;
	}

	//find maximum grade
	int getMaximum() const {
		int highGrade{ 0 }; // assume lowest grade is 0
		//loop through grades array 
		for (int grade : grades) {
			//if current grade higher than highGrade , assign it to highGrade
			if (grade > highGrade) {
				highGrade = grade;//new highest grade
			}
		}
		return highGrade;
	}


	double getAverage()const {
		int total{ 0 };

		for (int grade : grades) {
			total += grade;
		}
		return static_cast<double>(total) / grades.size();
	}

	void outputBarChart() const {
		std::cout << "\Grade distribution:" << std::endl;
		const size_t frequencySize{ 11 };
		std::array<unsigned int, frequencySize> frequency{};
		for (int grade : grades) {
			++frequency[grade / 10];
		}
		for (size_t count{ 0 }; count < frequencySize; ++count) {
			if (0 == count) {
				std::cout << "  0-9 ";
			}
			else if (10 == count) {
				std::cout << "  100: ";
			}
			else {
				std::cout << count * 10 << "-" << (count * 10) + 9 << ": ";
			}
			for (unsigned int stars{ 0 }; stars < frequency[count]; ++stars) {
				std::cout << '*';
			}
		}
		std::cout << std::endl;
	}

	void outputGrades()const {
		std::cout << "\nThe grades are: \n\n";

		for (size_t student{ 0 }; student < grades.size(); ++student) {
			std::cout << "Student " << std::setw(2) << student + 1 << ": "
				<< std::setw(3) << grades[student] << std::endl;
		}
	}
private:
	std::string courseName;
	std::array<int, students>grades;
};
