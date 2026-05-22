#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>

class Person {
private:
    std::string firstName;
    std::string surname;
    std::vector<int>* homeworks; // Using pointer to vector to explicitly demonstrate the Rule of Three
    int examScore;

    double calculateAverage() const;
    double calculateMedian() const;

public:
    // Constructors & Rule of Three
    Person();
    Person(std::string fName, std::string sName, const std::vector<int>& hw, int exam);
    Person(const Person& other);                // Copy Constructor
    Person& operator=(const Person& other);     // Copy Assignment Operator
    ~Person();                                  // Destructor

    // Getters
    std::string getFirstName() const { return firstName; }
    std::string getSurname() const { return surname; }
    double getFinalGrade(bool useAverage) const;

    // Random Generator Support
    void generateRandomGrades(int hwCount);

    // Friend Overloaded Operators for I/O
    friend std::istream& operator>>(std::istream& in, Person& p);
    friend std::ostream& operator<<(std::ostream& out, const Person& p);
};

#endif
