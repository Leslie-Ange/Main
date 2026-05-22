#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include "Person.h"

// Comparator function to sort by Name
bool compareByFirstName(const Person& a, const Person& b) {
    return a.getFirstName() < b.getFirstName();
}

void createSampleFile() {
    std::ofstream outFile("Students.txt");
    outFile << "Name        Surname    HW1   HW2   HW3   HW4   HW5   Exam\n";
    outFile << "Leslie      Ngassam      8     9    10     6    10      9\n";
    outFile << "Kristina    Viln         7    10     8     5     4      6\n";
    outFile << "Alex        Smith        6     8     7     9     7      8\n";
    outFile.close();
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    std::vector<Person> students;
    
    std::cout << "1. Manual/Random Input Processing\n2. File Input Processing (Students.txt)\nChoose option: ";
    int option;
    std::cin >> option;

    if (option == 1) {
        char more = 'y';
        while (more == 'y' || more == 'Y') {
            Person p;
            std::cout << "Generate randomly? (y/n): ";
            char choice;
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                std::string fName, sName;
                std::cout << "Enter First Name: "; std::cin >> fName;
                std::cout << "Enter Surname: "; std::cin >> sName;
                p = Person(fName, sName, {}, 0);
                p.generateRandomGrades(5); // Generates 5 random grades
            } else {
                std::cin >> p;
            }
            students.push_back(p);
            std::cout << "Add another student? (y/n): "; std::cin >> more;
        }
    } else {
        createSampleFile(); // Ensures local file exists for test run
        std::ifstream inFile("Students.txt");
        if (!inFile) {
            std::cerr << "Error opening file!\n";
            return 1;
        }

        std::string line;
        std::getline(inFile, line); // Skip header line

        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string firstName, surname;
            ss >> firstName >> surname;
            
            std::vector<int> hwGrades;
            int grade, exam;
            
            // Read values until the last one (which will be treated as the exam)
            while (ss >> grade) {
                hwGrades.push_back(grade);
            }
            if (!hwGrades.empty()) {
                exam = hwGrades.back();
                hwGrades.pop_back(); // Remove exam score from the homework list
                students.push_back(Person(firstName, surname, hwGrades, exam));
            }
        }
        inFile.close();
    }

    // Sort data alphabetically by first name
    std::sort(students.begin(), students.end(), compareByFirstName);

    // Display formatted output table
    std::cout << "\n" << std::left << std::setw(12) << "Name" 
              << std::setw(15) << "Surname" 
              << std::setw(15) << "Final (Avg.)" << " | " << std::setw(15) << "Final (Med.)" << "\n";
    std::cout << std::string(60, '-') << "\n";
    
    for (const auto& student : students) {
        std::cout << student << "\n";
    }

    return 0;
}
