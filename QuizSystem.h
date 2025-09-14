#ifndef QUIZSYSTEM_H
#define QUIZSYSTEM_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// Forward declarations
class Menu;
class CourseOffering;
class User;
class QuestionBank;
class Teacher;
class Student;
class TimeSetter;
class QuizSetter;
class CSVManager;

// Menu Class
class Menu
{
public:
    char showMenu();
};

// CourseOffering Class
class CourseOffering
{
public:
    void display_courses();
};

// User Class
class User
{
protected:
    string name;
    int ID;
    string email;
    string password;
    Menu usertype;
    CourseOffering coursesOffered;
    bool teacher_login;
    bool student_login;

public:
    User();
    User(string n, int id, string e, string p);
    
    void setName(string n);
    string getName();
    void setID(int id);
    int getID();
    void setEmail(string e);
    string getEmail();
    
    void login();
};

// QuestionBank Class
class QuestionBank
{
protected:
    string question_topics;
    string mcqs_questions;
    string mcqs_correct_options;
    string true_false_questions;
    string descriptive_questions;

public:
    QuestionBank();
    
    string get_Mcqs();
    void import_questions();
    void display_questions();
};

// Teacher Class
class Teacher : public User
{
private:
    QuestionBank questionBank;

public:
    Teacher();
    
    void menu();
    void teacherLogin();
    void setQuiz();
    void setTime();
    void evaluateQuiz();
    void viewStudentResult();
    void viewAttendanceSheet();
    void markAttendance();
    void generateAttendanceReport();
    void csvDataManagement();
    void logout();
};

// Student Class
class Student : public User
{
private:
    bool login_verify;

public:
    void startMenu();
    void studentLogin();
    void signup();
    string generate_password();
    void student_menu();
    void registerCourses();
    void viewRegisteredCourses();
    void conductQuiz();
    void viewQuizResults();
    void viewAttendance();
    void markAttendance();
    void logout();
};

// TimeSetter Class
class TimeSetter
{
private:
    int hours;
    int minutes;
    int seconds;

public:
    void setTime(int h, int m, int s);
    void getTime();
    void addTime(int h, int m, int s);
    void subtractTime(int h, int m, int s);
    tm CurrentTime();
    void setDuration(int h, int m, int s);
    void remainingTime();
};

// QuizSetter Class
class QuizSetter
{
private:
    string question_type;
    string question;
    string option1;
    string option2;
    string option3;
    string option4;
    string correct_option;
    QuestionBank questionBank;
    int duration;

public:
    QuizSetter();
    
    void Menu();
    void createQuizFromBank();
    void addCustomQuestions();
    void setQuizDuration();
};

// CSV Manager Class
class CSVManager
{
private:
    struct StudentRecord {
        int serialNumber;
        string rollNumber;
        string studentName;
        vector<string> enrolledCourses;
    };
    
    vector<StudentRecord> students;
    vector<string> courseCodes;
    vector<string> courseNames;

public:
    CSVManager();
    
    // CSV parsing functions
    bool loadCSVData(const string& filename);
    vector<string> parseCSVLine(const string& line);
    
    // Student management functions
    void importAllStudents();
    void importStudentsByCourse(const string& courseCode);
    bool isStudentEnrolled(const string& rollNumber, const string& courseCode);
    vector<string> getStudentsByCourse(const string& courseCode);
    vector<string> getCoursesByStudent(const string& rollNumber);
    
    // Course management functions
    void displayAllCourses();
    void displayCourseEnrollment(const string& courseCode);
    
    // Utility functions
    void generateStudentAccounts();
    void updateCourseOffering();
};

#endif
