#include "Person.h"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cstdlib>

// Constructor
Person::Person() : firstName(""), surname(""), examScore(0) {
    homeworks = new std::vector<int>();
}

Person::Person(std::string fName, std::string sName, const std::vector<int>& hw, int exam)
    : firstName(fName), surname(sName), examScore(exam) {
    homeworks = new std::vector<int>(hw);
}

// Copy Constructor (Rule of Three)
Person::Person(const Person& other) {
    firstName = other.firstName;
    surname = other.surname;
    examScore = other.examScore;
    homeworks = new std::vector<int>(*other.homeworks); // Deep copy
}

// Copy Assignment Operator (Rule of Three)
Person& Person::operator=(const Person& other) {
    if (this != &other) {
        delete homeworks; // Free existing resource

        firstName = other.firstName;
        surname = other.surname;
        examScore = other.examScore;
        homeworks = new std::vector<int>(*other.homeworks); // Deep copy
    }
    return *this;
}

// Destructor (Rule of Three)
Person::~Person() {
    delete homeworks;
}

double Person::calculateAverage() const {
    if (homeworks->empty()) return 0.4 * 0 + 0.6 * examScore;
    double sum = std::accumulate(homeworks->begin(), homeworks->end(), 0.0);
    return sum / homeworks->size();
}

double Person::calculateMedian() const {
    if (homeworks->empty()) return 0.0;
    std::vector<int> temp = *homeworks;
    std::sort(temp.begin(), temp.end());
    size_t size = temp.size();
    if (size % 2 == 0) {
        return (temp[size / 2 - 1] + temp[size / 2]) / 2.0;
    } else {
        return temp[size / 2];
    }
}

double Person::getFinalGrade(bool useAverage) const {
    double hwResult = useAverage ? calculateAverage() : calculateMedian();
    return 0.4 * hwResult + 0.6 * examScore;
}

void Person::generateRandomGrades(int hwCount) {
    homeworks->clear();
    for (int i = 0; i < hwCount; ++i) {
        homeworks->push_back(rand() % 11); // Grades 0 to 10
    }
    examScore = rand() % 11;
}

// Overloaded cin
std::istream& operator>>(std::istream& in, Person& p) {
    std::cout << "Enter First Name: "; in >> p.firstName;
    std::cout << "Enter Surname: "; in >> p.surname;
    
    p.homeworks->clear();
    std::string input;
    std::cout << "Enter HW grades (Enter 'q' when finished):\n";
    while (true) {
        std::cout << "HW " << p.homeworks->size() + 1 << ": ";
        in >> input;
        if (input == "q" || input == "Q") break;
        try {
            int grade = std::stoi(input);
            if (grade >= 0 && grade <= 10) p.homeworks->push_back(grade);
            else std::cout << "Please enter a grade between 0 and 10.\n";
        } catch (...) {
            std::cout << "Invalid input. Enter a number or 'q' to stop.\n";
        }
    }
    std::cout << "Enter Exam Grade: "; in >> p.examScore;
    return in;
}

// Overloaded cout
std::ostream& operator<<(std::ostream& out, const Person& p) {
    out << std::left << std::setw(12) << p.firstName 
        << std::setw(15) << p.surname 
        << std::fixed << std::setprecision(2) << std::setw(15) << p.getFinalGrade(true)
        << " | " << std::setw(15) << p.getFinalGrade(false);
    return out;
}
