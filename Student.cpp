#include "QuizSystem.h"
#include <ctime>

// Student Class Implementation
void Student::startMenu()
{
    int choice;
    do
    {
        cout << "\n=== STUDENT LOGIN/SIGNUP ===" << endl;
        cout << "Choose One" << endl;
        cout << "1. Login" << endl;
        cout << "2. Sign Up" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        switch(choice)
        {
            case 1:
                studentLogin();

                if (student_login)
                {
                    student_menu();
                }
                else 
                {
                    cout << "Login Failed" << endl;
                    cout << "Press Enter to continue...";
                    cin.ignore();
                    cin.get();
                }
                break;
            case 2:
                signup();
                cout << "Signup successful! You can now login." << endl;
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            case 3:
                cout << "Returning to main menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 3);
}

void Student::studentLogin()
{
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter your email: ";
    getline(cin, email);

    cout << "Enter your password: ";
    getline(cin, password);

    ifstream studentFile;
    studentFile.open("students/studentLogin.txt");

    if (studentFile.is_open())
    {
        string line;
        string currentName, currentEmail, currentPassword;
        int lineCount = 0;
        
        while (getline(studentFile, line))
        {
            lineCount++;
            
            if (lineCount % 3 == 1) // Name line
            {
                currentName = line;
            }
            else if (lineCount % 3 == 2) // Email line
            {
                currentEmail = line;
            }
            else if (lineCount % 3 == 0) // Password line
            {
                currentPassword = line;
                
                // Check if this is a complete record (not empty)
                if (!currentName.empty() && !currentEmail.empty() && !currentPassword.empty())
                {
                    if (currentName == name && currentEmail == email && currentPassword == password)
                    {
                        student_login = true;
                        break;
                    }
                }
            }
        }
    }

    if (student_login == true)
    {
        cout << "Login successful" << endl;
        
        // Automatically mark attendance on successful login
        markAttendance();
    }
    else
    {
        cout << "Login unsuccessful" << endl;
    }

    studentFile.close();
}

void Student::signup()
{
    cout << "Enter username: ";
    cin.ignore();
    getline(cin, name);
    
    cout << "Enter email: ";
    getline(cin, email);
    
    cout << "Do you want to enter your own password or generate one? (1/2)" << endl;
    int choice_password;
    cin >> choice_password;

    if (choice_password == 1)
    {
        cout << "Enter password: ";
        cin >> password;

        if (password.length() < 6)
        {
            cout << "Password must be at least 6 characters long" << endl;
        }

        else
        {
            bool has_uppercase = false;
            bool has_lowercase = false;
            bool has_number = false;
            bool has_special_character = false;

            do
            {
                for (int i = 0; i < password.length(); i++)
                {
                    if (isupper(password[i]))
                    {
                        has_uppercase = true;
                    }

                    else if (islower(password[i]))
                    {
                        has_lowercase = true;
                    }

                    else if (isdigit(password[i]))
                    {
                        has_number = true;
                    }

                    else if (ispunct(password[i]))
                    {
                        has_special_character = true;
                    }
                }

                if (!has_uppercase)
                {
                    cout << "Password must contain at least one uppercase letter" << endl;
                    cout << "Enter password: ";
                    cin >> password;
                }

                else if (!has_lowercase)
                {
                    cout << "Password must contain at least one lowercase letter" << endl;
                    cout << "Enter password: ";
                    cin >> password;
                }

                else if (!has_number)
                {
                    cout << "Password must contain at least one number" << endl;
                    cout << "Enter password: ";
                    cin >> password;
                }

                else if (!has_special_character)
                {
                    cout << "Password must contain at least one special character" << endl;
                    cout << "Enter password: ";
                    cin >> password;
                }
            }while (!has_uppercase || !has_lowercase || !has_number || !has_special_character);
        }
    }

    else if (choice_password == 2)
    {
        password = generate_password();
    }

    else
    {
        cout << "Invalid choice" << endl;
    }

    ofstream userFile;
    userFile.open("students/studentLogin.txt", ios::app);

    if (userFile.is_open())
    {
        // Add a newline before appending new data to ensure proper separation
        userFile << endl;
        userFile << name << endl;
        userFile << email << endl;
        userFile << password << endl;
    }

    userFile.close();
}

string Student::generate_password()
{
    srand(time(0));

    string password;
    int length = rand() % 10 + 6;
    bool has_uppercase = false;
    bool has_lowercase = false;
    bool has_number = false;
    bool has_special_character = false;

    for (int i = 0; i < length; i++)
    {
        int choice = rand() % 4 + 1;

        if (choice == 1)
        {
            password += rand() % 26 + 65;
            has_uppercase = true;
        }

        else if (choice == 2)
        {
            password += rand() % 26 + 97;
            has_lowercase = true;
        }

        else if (choice == 3)
        {
            password += rand() % 10 + 48;
            has_number = true;
        }

        else if (choice == 4)
        {
            password += rand() % 15 + 33;
            has_special_character = true;
        }
    }

    if (!has_uppercase)
    {
        password += rand() % 26 + 65;
    }

    if (!has_lowercase)
    {
        password += rand() % 26 + 97;
    }

    if (!has_number)
    {
        password += rand() % 10 + 48;
    }

    if (!has_special_character)
    {
        password += rand() % 15 + 33;
    }

    cout << "Your password is: " << password << endl;
    return password;
}

void Student::student_menu()
{
    if (student_login)
    {
        int choice;
        do
        {
            cout << "\n=== STUDENT DASHBOARD ===" << endl;
            cout << "Welcome, " << name << "!" << endl;
            cout << "Choose One" << endl;
            cout << "1. Register Courses" << endl;
            cout << "2. View Registered Courses" << endl;
            cout << "3. Conduct Quiz" << endl;
            cout << "4. View Quiz Results" << endl;
            cout << "5. View Attendance" << endl;
            cout << "6. Mark Attendance" << endl;
            cout << "7. Logout" << endl;
            cout << "Enter your choice: ";

            cin >> choice;

            switch(choice)
            {
                case 1:
                    registerCourses();
                    break;
                case 2:
                    viewRegisteredCourses();
                    break;
                case 3:
                    conductQuiz();
                    break;
                case 4:
                    viewQuizResults();
                    break;
                case 5:
                    viewAttendance();
                    break;
                case 6:
                    markAttendance();
                    break;
                case 7:
                    logout();
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
            
            if (choice != 7)
            {
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
            }
            
        } while (choice != 7);
    }
}

void Student::registerCourses()
{
    cout << "Course Registration" << endl;
    cout << "Available courses:" << endl;
    
    ifstream courseFile;
    courseFile.open("data/CourseOffering.txt");
    if (courseFile.is_open())
    {
        string line;
        int courseNum = 1;
        while (getline(courseFile, line))
        {
            cout << courseNum << ". " << line << endl;
            courseNum++;
        }
        courseFile.close();
    }
    
    cout << "Enter course numbers to register (separated by spaces, 0 to finish): ";
    string input;
    cin.ignore();
    getline(cin, input);
    
    ofstream regFile;
    regFile.open("students/student_courses_" + name + ".txt", ios::app);
    if (regFile.is_open())
    {
        // Add a newline before appending new data to ensure proper separation
        regFile << endl;
        regFile << "Student: " << name << endl;
        regFile << "Registration Date: " << __DATE__ << " " << __TIME__ << endl;
        regFile << "Courses: " << input << endl;
        regFile << "---" << endl;
        regFile.close();
        cout << "Courses registered successfully!" << endl;
    }
}

void Student::viewRegisteredCourses()
{
    cout << "Your Registered Courses:" << endl;
    ifstream regFile;
    regFile.open("students/student_courses_" + name + ".txt");
    
    if (regFile.is_open())
    {
        string line;
        while (getline(regFile, line))
        {
            cout << line << endl;
        }
        regFile.close();
    }
    else
    {
        cout << "No courses registered yet." << endl;
    }
}

void Student::conductQuiz()
{
    cout << "Available Quizzes:" << endl;
    cout << "Enter quiz name: ";
    string quizName;
    cin.ignore();
    getline(cin, quizName);
    
    ifstream quizFile;
    quizFile.open("quizzes/quiz_" + quizName + ".txt");
    
    if (quizFile.is_open())
    {
        cout << "Starting Quiz: " << quizName << endl;
        cout << "Time limit: ";
        
        // Read time from quiz_time.txt
        ifstream timeFile;
        timeFile.open("data/quiz_time.txt");
        if (timeFile.is_open())
        {
            string timeStr;
            getline(timeFile, timeStr);
            cout << timeStr << endl;
            timeFile.close();
        }
        
        cout << "Press Enter to start...";
        cin.get();
        
        // Read and display questions
        string line;
        ofstream answerFile;
        answerFile.open("results/answers_" + name + "_" + quizName + ".txt");
        
        if (answerFile.is_open())
        {
            answerFile << "Student: " << name << endl;
            answerFile << "Quiz: " << quizName << endl;
            answerFile << "---" << endl;
            
            int questionNum = 1;
            while (getline(quizFile, line))
            {
                if (line.find("Q" + to_string(questionNum) + ":") != string::npos)
                {
                    cout << line << endl;
                    
                    // Read options
                    for (int i = 0; i < 4; i++)
                    {
                        getline(quizFile, line);
                        if (line.find("A)") != string::npos || 
                            line.find("B)") != string::npos || 
                            line.find("C)") != string::npos || 
                            line.find("D)") != string::npos)
                        {
                            cout << line << endl;
                        }
                    }
                    
                    cout << "Your answer: ";
                    string answer;
                    getline(cin, answer);
                    answerFile << "Q" << questionNum << ": " << answer << endl;
                    questionNum++;
                }
            }
            
            answerFile.close();
            cout << "Quiz completed! Answers saved." << endl;
        }
        
        quizFile.close();
    }
    else
    {
        cout << "Quiz not found!" << endl;
    }
}

void Student::viewQuizResults()
{
    cout << "Your Quiz Results:" << endl;
    ifstream resultFile;
    resultFile.open("results/results_" + name + ".txt");
    
    if (resultFile.is_open())
    {
        string line;
        while (getline(resultFile, line))
        {
            cout << line << endl;
        }
        resultFile.close();
    }
    else
    {
        cout << "No results available yet." << endl;
    }
}

void Student::viewAttendance()
{
    cout << "Your Attendance:" << endl;
    ifstream attendanceFile;
    attendanceFile.open("attendance/attendance.txt");
    
    if (attendanceFile.is_open())
    {
        string line;
        bool found = false;
        while (getline(attendanceFile, line))
        {
            if (line.find(name) != string::npos)
            {
                cout << line << endl;
                found = true;
            }
        }
        if (!found)
        {
            cout << "No attendance records found for you." << endl;
        }
        attendanceFile.close();
    }
    else
    {
        cout << "No attendance records available." << endl;
    }
}

void Student::markAttendance()
{
    // Get current date and time
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    string date = to_string(1900 + ltm->tm_year) + "-" + 
                  to_string(1 + ltm->tm_mon) + "-" + 
                  to_string(ltm->tm_mday);
    
    string time_str = to_string(ltm->tm_hour) + ":" + 
                      to_string(ltm->tm_min) + ":" + 
                      to_string(ltm->tm_sec);
    
    // Check if already marked present today
    ifstream checkFile;
    checkFile.open("attendance/attendance.txt");
    bool alreadyMarked = false;
    
    if (checkFile.is_open())
    {
        string line;
        while (getline(checkFile, line))
        {
            if (line.find(name) != string::npos && line.find(date) != string::npos)
            {
                alreadyMarked = true;
                break;
            }
        }
        checkFile.close();
    }
    
    if (alreadyMarked)
    {
        cout << "Attendance already marked for today!" << endl;
        return;
    }
    
    // Mark attendance
    ofstream attendanceFile;
    attendanceFile.open("attendance/attendance.txt", ios::app);
    
    if (attendanceFile.is_open())
    {
        attendanceFile << endl << name << " - Present on " << date << " at " << time_str << endl;
        attendanceFile.close();
        cout << "Attendance marked successfully for " << date << " at " << time_str << endl;
    }
    else
    {
        cout << "Error: Could not mark attendance." << endl;
    }
}

void Student::logout()
{
    student_login = false;
    cout << "Logged out successfully!" << endl;
}
