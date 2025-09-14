# Quiz Management System

A comprehensive C++ application for managing quizzes, student registrations, and course offerings in an educational institution. Built with Object-Oriented Programming principles and featuring a clean, modular architecture.

## Features

### Teacher Features
- **Authentication System** - Secure login/signup with credential validation
- **Question Bank Management** - Import and manage questions from text files
- **Quiz Creation** - Create custom quizzes with multiple question types
- **Time Management** - Set time limits for quizzes
- **Grading System** - Automated quiz evaluation and scoring
- **Student Analytics** - View individual student results and performance
- **Attendance Tracking** - Manage and view student attendance records
- **CSV Integration** - Import student data from Excel/CSV files
- **Course Management** - View and manage course enrollments

### Student Features
- **User Registration** - Easy signup with email validation
- **Course Registration** - Browse and register for available courses
- **Quiz Participation** - Take timed quizzes with real-time feedback
- **Performance Tracking** - View quiz results and grades
- **Attendance Monitoring** - Check personal attendance records
- **Profile Management** - Update personal information

### System Features
- **Modular Architecture** - Clean separation of concerns with multiple files
- **Data Persistence** - File-based storage for all data
- **Error Handling** - Robust error handling and validation
- **Organized Structure** - Logical folder organization for different data types
- **CSV Support** - Import student enrollment data from external sources

## Project Structure

```
Quiz Management System/
├── main.cpp                    # Program entry point
├── QuizSystem.h               # Main header file with all declarations
├── Makefile                   # Build configuration
├── .gitignore                 # Git ignore rules
├── README.md                  # Project documentation
├── data/                      # Core data files
│   ├── Questions.txt
│   ├── Answers.txt
│   ├── CourseOffering.txt
│   └── Course Registration Data - Sheet1.csv
├── students/                  # Student-related files
│   └── .gitkeep
├── teachers/                  # Teacher-related files
│   └── .gitkeep
├── quizzes/                   # Generated quiz files
│   └── .gitkeep
├── results/                   # Quiz results and answers
│   └── .gitkeep
├── attendance/                # Attendance records
│   └── .gitkeep
└── Implementation Files/
    ├── BasicClasses.cpp          # Core classes implementation
    ├── Teacher.cpp              # Teacher functionality
    ├── Student.cpp              # Student functionality
    ├── TimeQuizClasses.cpp      # Time and quiz management
    └── CSVManager.cpp           # CSV data handling
```

## Quick Start

### Prerequisites
- C++ compiler (GCC, Clang, or MSVC)
- Make utility (optional, for using Makefile)

### Installation & Compilation

#### Method 1: Using Makefile (Recommended)
```bash
# Clone the repository
git clone <repository-url>
cd Quiz-Management-System

# Compile the project
make

# Run the application
./QuizSystem
```

#### Method 2: Manual Compilation
```bash
# Compile all source files
g++ -o QuizSystem main.cpp BasicClasses.cpp Teacher.cpp Student.cpp TimeQuizClasses.cpp CSVManager.cpp

# Run the application
./QuizSystem
```

### First Time Setup
1. **Data Files**: Ensure `data/` folder contains required files:
   - `Questions.txt` - Question bank
   - `Answers.txt` - Answer key
   - `CourseOffering.txt` - Available courses
   - `Course Registration Data - Sheet1.csv` - Student data

2. **Run Application**: Execute the compiled binary
3. **Create Accounts**: Set up teacher and student accounts through the interface

## Data Management

### Input Data Format

#### Questions.txt Format
```
Topic: Mathematics
MCQ: What is 2+2?
A) 3
B) 4
C) 5
D) 6
Correct: B

True/False: The sun rises in the east.
Correct: True

Descriptive: Explain photosynthesis.
```

#### CSV Data Format
The system supports importing student enrollment data from CSV files with the following structure:
- Serial Number
- Roll Number  
- Student Name
- Course Enrollments (1 for enrolled, 0 for not enrolled)

### Generated Files
- **Student Data**: `students/studentLogin.txt` - Student credentials
- **Teacher Data**: `teachers/teacherLogin.txt` - Teacher credentials  
- **Quiz Files**: `quizzes/quiz_*.txt` - Generated quiz files
- **Results**: `results/results_*.txt` - Student quiz results
- **Attendance**: `attendance/attendance.txt` - Attendance records

## Usage Guide

### For Teachers
1. **Login** with your credentials
2. **Import Questions** from the question bank
3. **Create Quizzes** by selecting questions and setting parameters
4. **Set Time Limits** for quizzes
5. **Evaluate Submissions** and assign grades
6. **View Analytics** for individual students
7. **Manage Attendance** and track student participation
8. **Import Student Data** from CSV files

### For Students
1. **Register** for a new account or login
2. **Browse Courses** and register for available ones
3. **Take Quizzes** within the specified time limits
4. **View Results** and track your performance
5. **Check Attendance** for your enrolled courses

## Technical Details

- **Language**: C++ (C++11 or later)
- **Paradigm**: Object-Oriented Programming
- **Key Concepts**: Classes, Inheritance, Polymorphism, File I/O, Data Structures
- **Dependencies**: Standard C++ libraries only
- **Architecture**: Multi-file modular design
- **Data Storage**: Text file-based persistence
- **Error Handling**: Comprehensive input validation and error management

## Development

### Code Organization
- **Header File**: `QuizSystem.h` contains all class declarations
- **Implementation**: Each class has its own implementation file
- **Main**: `main.cpp` handles program flow and user interface
- **Modularity**: Easy to extend and maintain

## Developer

**Muhammad Zain Raza**  
BS AI Student in FAST NUCES Islamabad

## License

This project is developed as a final project for Object-Oriented Programming course, demonstrating practical application of OOP concepts in educational software.

## Contributing

This is an academic project. For educational purposes, feel free to:
- Study the code structure
- Suggest improvements
- Use as a reference for OOP concepts

## Support

For questions or issues related to this project, please refer to the code documentation or contact the development team.
