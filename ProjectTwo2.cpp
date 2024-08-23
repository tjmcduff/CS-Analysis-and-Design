#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits> // for numeric_limits

using namespace std;

// Course structure to hold course details
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Function to load course data from file into the hash table
void loadCourseData(unordered_map<string, Course>& courses, const string& fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, courseTitle, prereq;
        vector<string> prerequisites;

        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');

        while (getline(ss, prereq, ',')) {
            prerequisites.push_back(prereq);
        }

        Course course = { courseNumber, courseTitle, prerequisites };
        courses[courseNumber] = course;
    }

    file.close();
    cout << "Course data loaded successfully." << endl;
}

// Function to print an alphanumeric list of all courses
void printSortedCourseList(const unordered_map<string, Course>& courses) {
    if (courses.empty()) {
        cout << "Error: No course data loaded." << endl;
        return;
    }

    vector<string> sortedCourses;
    for (const auto& pair : courses) {
        sortedCourses.push_back(pair.first);
    }

    sort(sortedCourses.begin(), sortedCourses.end());

    cout << "Here is a sample schedule:" << endl;
    for (const string& courseNumber : sortedCourses) {
        cout << courseNumber << ", " << courses.at(courseNumber).courseTitle << endl;
    }
}

// Function to print course information
void printCourseInfo(const unordered_map<string, Course>& courses, const string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        const Course& course = it->second;
        cout << course.courseNumber << ", " << course.courseTitle << endl;
        cout << "Prerequisites: ";
        if (course.prerequisites.empty()) {
            cout << "None" << endl;
        }
        else {
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                cout << course.prerequisites[i];
                if (i < course.prerequisites.size() - 1) cout << ", ";
            }
            cout << endl;
        }
    }
    else {
        cout << "Error: Course not found." << endl;
    }
}

// Main function with menu implementation
int main() {
    unordered_map<string, Course> courses;
    int option = 0;

    cout << "Welcome to the course planner." << endl;

    while (option != 9) {
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit." << endl;
        cout << "\nWhat would you like to do? ";
        cin >> option;

        // Check for invalid input type (e.g., entering a non-integer)
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid option." << endl;
            continue; // Return to the start of the loop to ask for input again
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any leftover newline characters

        switch (option) {
        case 1: {
            string fileName;
            cout << "Enter the course data file name: ";
            getline(cin, fileName); // Use getline to ensure entire filename is captured
            loadCourseData(courses, fileName);
            break;
        }
        case 2:
            printSortedCourseList(courses);
            break;
        case 3: {
            string courseNumber;
            cout << "What course do you want to know about? ";
            getline(cin, courseNumber);
            transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
            printCourseInfo(courses, courseNumber);
            break;
        }
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << option << " is not a valid option." << endl;
            break;
        }
    }

    return 0;
}
