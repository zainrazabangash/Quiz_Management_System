#include "QuizSystem.h"
#include <ctime>
#include <map>
#include <iomanip>

// Teacher Class Implementation
Teacher::Teacher()
{
    questionBank.import_questions();
}

void Teacher::menu()
{
    teacherLogin();

    if (teacher_login)
    {
        int choice;
        do
        {
            cout << "\n=== TEACHER DASHBOARD ===" << endl;
            cout << "Welcome, " << name << "!" << endl;
            cout << "What would you like to do?" << endl;
            cout << "1. See Questions" << endl;
            cout << "2. Set Quiz" << endl;
            cout << "3. Set Time" << endl;
            cout << "4. Evaluate Quiz" << endl;
            cout << "5. View Result of a student" << endl;
            cout << "6. View Attendance Sheet" << endl;
            cout << "7. Mark Attendance" << endl;
            cout << "8. Generate Attendance Report" << endl;
            cout << "9. CSV Data Management" << endl;
            cout << "10. Log Out" << endl;
            cout << "Enter your choice: ";

            cin >> choice;
        
            switch (choice)
            {
                case 1:
                    questionBank.display_questions();
                    break;
                case 2:
                    setQuiz();
                    break;
                case 3:
                    setTime();
                    break;
                case 4:
                    evaluateQuiz();
                    break;
                case 5:
                    viewStudentResult();
                    break;
                case 6:
                    viewAttendanceSheet();
                    break;
                case 7:
                    markAttendance();
                    break;
                case 8:
                    generateAttendanceReport();
                    break;
                case 9:
                    csvDataManagement();
                    break;
                case 10:
                    logout();
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
            
            if (choice != 10)
            {
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
            }
            
        } while (choice != 10);
    }
    else 
    {
        cout << "Login Failed" << endl;
    }
}

void Teacher::teacherLogin()
{
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter your email: ";
    getline(cin, email);

    cout << "Enter your password: ";
    getline(cin, password);

    ifstream teacherFile;
    teacherFile.open("teachers/teacherLogin.txt");

    if (teacherFile.is_open())
    {
        string line;
        string currentName, currentEmail, currentPassword;
        int lineCount = 0;
        
        while (getline(teacherFile, line))
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
                        teacher_login = true;
                        break;
                    }
                }
            }
        }
    }

    if (teacher_login == true)
    {
        cout << "Login successful" << endl;
    }
    else
    {
        cout << "Login unsuccessful" << endl;
    }

    teacherFile.close();
}

void Teacher::setQuiz()
{
    cout << "Setting up a new quiz..." << endl;
    cout << "Enter quiz name: ";
    string quizName;
    cin.ignore();
    getline(cin, quizName);
    
    cout << "Enter number of questions: ";
    int numQuestions;
    cin >> numQuestions;
    
    ofstream quizFile;
    quizFile.open("quizzes/quiz_" + quizName + ".txt", ios::out);
    
    if (quizFile.is_open())
    {
        quizFile << "Quiz: " << quizName << endl;
        quizFile << "Number of Questions: " << numQuestions << endl;
        quizFile << "Created by: " << name << endl;
        quizFile << "Date: " << __DATE__ << " " << __TIME__ << endl;
        quizFile << "---" << endl;
        
        for (int i = 1; i <= numQuestions; i++)
        {
            cout << "Question " << i << ":" << endl;
            cout << "1. MCQ" << endl;
            cout << "2. True/False" << endl;
            cout << "3. Descriptive" << endl;
            cout << "Choose question type: ";
            
            int qType;
            cin >> qType;
            cin.ignore();
            
            string question, option1, option2, option3, option4, correctAnswer;
            
            cout << "Enter question: ";
            getline(cin, question);
            quizFile << "Q" << i << ": " << question << endl;
            
            if (qType == 1) // MCQ
            {
                cout << "Enter option 1: ";
                getline(cin, option1);
                cout << "Enter option 2: ";
                getline(cin, option2);
                cout << "Enter option 3: ";
                getline(cin, option3);
                cout << "Enter option 4: ";
                getline(cin, option4);
                cout << "Enter correct answer (1-4): ";
                getline(cin, correctAnswer);
                
                quizFile << "A) " << option1 << endl;
                quizFile << "B) " << option2 << endl;
                quizFile << "C) " << option3 << endl;
                quizFile << "D) " << option4 << endl;
                quizFile << "Correct: " << correctAnswer << endl;
            }
            else if (qType == 2) // True/False
            {
                cout << "Enter correct answer (True/False): ";
                getline(cin, correctAnswer);
                quizFile << "True/False" << endl;
                quizFile << "Correct: " << correctAnswer << endl;
            }
            else if (qType == 3) // Descriptive
            {
                cout << "Enter sample answer: ";
                getline(cin, correctAnswer);
                quizFile << "Descriptive" << endl;
                quizFile << "Sample Answer: " << correctAnswer << endl;
            }
            
            quizFile << "---" << endl;
        }
        
        quizFile.close();
        cout << "Quiz '" << quizName << "' created successfully!" << endl;
    }
    else
    {
        cout << "Error creating quiz file!" << endl;
    }
}

void Teacher::setTime()
{
    cout << "Setting quiz time..." << endl;
    cout << "Enter hours: ";
    int hours;
    cin >> hours;
    cout << "Enter minutes: ";
    int minutes;
    cin >> minutes;
    cout << "Enter seconds: ";
    int seconds;
    cin >> seconds;
    
    ofstream timeFile;
    timeFile.open("data/quiz_time.txt", ios::out);
    if (timeFile.is_open())
    {
        timeFile << hours << ":" << minutes << ":" << seconds << endl;
        timeFile.close();
        cout << "Quiz time set to " << hours << ":" << minutes << ":" << seconds << endl;
    }
}

void Teacher::evaluateQuiz()
{
    cout << "Quiz Evaluation" << endl;
    cout << "Enter student name: ";
    string studentName;
    cin.ignore();
    getline(cin, studentName);
    
    cout << "Enter quiz name: ";
    string quizName;
    getline(cin, quizName);
    
    ifstream answerFile;
    answerFile.open("results/answers_" + studentName + "_" + quizName + ".txt");
    
    if (answerFile.is_open())
    {
        cout << "Student: " << studentName << endl;
        cout << "Quiz: " << quizName << endl;
        cout << "Answers submitted successfully!" << endl;
        answerFile.close();
    }
    else
    {
        cout << "No answers found for this student and quiz." << endl;
    }
}

void Teacher::viewStudentResult()
{
    cout << "View Student Result" << endl;
    cout << "Enter student name: ";
    string studentName;
    cin.ignore();
    getline(cin, studentName);
    
    ifstream resultFile;
    resultFile.open("results/results_" + studentName + ".txt");
    
    if (resultFile.is_open())
    {
        string line;
        cout << "Results for " << studentName << ":" << endl;
        while (getline(resultFile, line))
        {
            cout << line << endl;
        }
        resultFile.close();
    }
    else
    {
        cout << "No results found for this student." << endl;
    }
}

void Teacher::viewAttendanceSheet()
{
    cout << "Attendance Sheet" << endl;
    ifstream attendanceFile;
    attendanceFile.open("attendance/attendance.txt");
    
    if (attendanceFile.is_open())
    {
        string line;
        cout << "Student Attendance:" << endl;
        while (getline(attendanceFile, line))
        {
            cout << line << endl;
        }
        attendanceFile.close();
    }
    else
    {
        cout << "No attendance records found." << endl;
    }
}

void Teacher::csvDataManagement()
{
    CSVManager csvManager;
    int choice;
    
    do
    {
        cout << "\n=== CSV DATA MANAGEMENT ===" << endl;
        cout << "1. Load CSV Data" << endl;
        cout << "2. Import All Students" << endl;
        cout << "3. View Course Enrollments" << endl;
        cout << "4. Check Student Enrollment" << endl;
        cout << "5. Display All Courses" << endl;
        cout << "6. Generate Student Accounts" << endl;
        cout << "7. Back to Teacher Menu" << endl;
        cout << "Enter your choice: ";
        
        cin >> choice;
        
        switch(choice)
        {
            case 1:
                {
                    cout << "Loading CSV data..." << endl;
                    if (csvManager.loadCSVData("data/Course Registration Data - Sheet1.csv"))
                    {
                        cout << "CSV data loaded successfully!" << endl;
                    }
                    break;
                }
            case 2:
                csvManager.importAllStudents();
                break;
            case 3:
                {
                    cout << "Enter course code (e.g., CS101, CS201): ";
                    string courseCode;
                    cin >> courseCode;
                    csvManager.displayCourseEnrollment(courseCode);
                    break;
                }
            case 4:
                {
                    cout << "Enter student roll number: ";
                    string rollNumber;
                    cin >> rollNumber;
                    cout << "Enter course code: ";
                    string courseCode;
                    cin >> courseCode;
                    
                    if (csvManager.isStudentEnrolled(rollNumber, courseCode))
                    {
                        cout << "Student " << rollNumber << " is enrolled in " << courseCode << endl;
                    }
                    else
                    {
                        cout << "Student " << rollNumber << " is NOT enrolled in " << courseCode << endl;
                    }
                    break;
                }
            case 5:
                csvManager.displayAllCourses();
                break;
            case 6:
                csvManager.generateStudentAccounts();
                break;
            case 7:
                cout << "Returning to teacher menu..." << endl;
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

void Teacher::markAttendance()
{
    cout << "\n=== MARK ATTENDANCE ===" << endl;
    
    // Get current date
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string date = to_string(1900 + ltm->tm_year) + "-" + 
                  to_string(1 + ltm->tm_mon) + "-" + 
                  to_string(ltm->tm_mday);
    
    cout << "Marking attendance for date: " << date << endl;
    
    // Read student list from studentLogin.txt
    ifstream studentFile;
    studentFile.open("students/studentLogin.txt");
    
    if (!studentFile.is_open())
    {
        cout << "Error: Could not open student file." << endl;
        return;
    }
    
    vector<string> students;
    string line;
    int lineCount = 0;
    string currentName;
    
    while (getline(studentFile, line))
    {
        lineCount++;
        if (lineCount % 3 == 1) // Name line
        {
            currentName = line;
        }
        else if (lineCount % 3 == 0 && !currentName.empty()) // Password line (end of record)
        {
            students.push_back(currentName);
            currentName = "";
        }
    }
    studentFile.close();
    
    if (students.empty())
    {
        cout << "No students found." << endl;
        return;
    }
    
    // Mark attendance for each student
    ofstream attendanceFile;
    attendanceFile.open("attendance/attendance.txt", ios::app);
    
    if (!attendanceFile.is_open())
    {
        cout << "Error: Could not open attendance file." << endl;
        return;
    }
    
    cout << "\nMarking attendance for " << students.size() << " students:" << endl;
    
    for (const string& studentName : students)
    {
        cout << "Is " << studentName << " present? (y/n): ";
        char present;
        cin >> present;
        
        if (present == 'y' || present == 'Y')
        {
            attendanceFile << endl << studentName << " - Present on " << date << " (Marked by Teacher)" << endl;
            cout << "Marked present." << endl;
        }
        else
        {
            attendanceFile << endl << studentName << " - Absent on " << date << " (Marked by Teacher)" << endl;
            cout << "Marked absent." << endl;
        }
    }
    
    attendanceFile.close();
    cout << "\nAttendance marking completed for " << date << endl;
}

void Teacher::generateAttendanceReport()
{
    cout << "\n=== ATTENDANCE REPORT ===" << endl;
    
    ifstream attendanceFile;
    attendanceFile.open("attendance/attendance.txt");
    
    if (!attendanceFile.is_open())
    {
        cout << "No attendance records found." << endl;
        return;
    }
    
    map<string, int> presentCount;
    map<string, int> absentCount;
    map<string, vector<string>> studentRecords;
    
    string line;
    while (getline(attendanceFile, line))
    {
        if (line.find("Present") != string::npos)
        {
            // Extract student name (everything before " - Present")
            size_t pos = line.find(" - Present");
            if (pos != string::npos)
            {
                string studentName = line.substr(0, pos);
                presentCount[studentName]++;
                studentRecords[studentName].push_back(line);
            }
        }
        else if (line.find("Absent") != string::npos)
        {
            // Extract student name (everything before " - Absent")
            size_t pos = line.find(" - Absent");
            if (pos != string::npos)
            {
                string studentName = line.substr(0, pos);
                absentCount[studentName]++;
                studentRecords[studentName].push_back(line);
            }
        }
    }
    attendanceFile.close();
    
    if (studentRecords.empty())
    {
        cout << "No attendance records found." << endl;
        return;
    }
    
    // Generate filename with current date
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string date = to_string(1900 + ltm->tm_year) + "-" + 
                  to_string(1 + ltm->tm_mon) + "-" + 
                  to_string(ltm->tm_mday);
    string filename = "results/attendance_report_" + date + ".txt";
    
    // Create report file
    ofstream reportFile;
    reportFile.open(filename);
    
    if (!reportFile.is_open())
    {
        cout << "Error: Could not create report file." << endl;
        return;
    }
    
    // Write to both console and file
    reportFile << "ATTENDANCE REPORT" << endl;
    reportFile << "Generated on: " << date << endl;
    reportFile << "=========================================" << endl;
    
    cout << "\n=== ATTENDANCE SUMMARY ===" << endl;
    reportFile << "\nATTENDANCE SUMMARY" << endl;
    cout << "Student Name\t\tPresent\tAbsent\tTotal\tPercentage" << endl;
    reportFile << "Student Name\t\tPresent\tAbsent\tTotal\tPercentage" << endl;
    cout << "--------------------------------------------------------" << endl;
    reportFile << "--------------------------------------------------------" << endl;
    
    for (const auto& record : studentRecords)
    {
        string studentName = record.first;
        int present = presentCount[studentName];
        int absent = absentCount[studentName];
        int total = present + absent;
        double percentage = total > 0 ? (double)present / total * 100 : 0;
        
        cout << studentName << "\t\t" << present << "\t" << absent << "\t" << total << "\t" << fixed << setprecision(1) << percentage << "%" << endl;
        reportFile << studentName << "\t\t" << present << "\t" << absent << "\t" << total << "\t" << fixed << setprecision(1) << percentage << "%" << endl;
    }
    
    cout << "\n=== DETAILED RECORDS ===" << endl;
    reportFile << "\nDETAILED RECORDS" << endl;
    for (const auto& record : studentRecords)
    {
        cout << "\n" << record.first << ":" << endl;
        reportFile << "\n" << record.first << ":" << endl;
        for (const string& detail : record.second)
        {
            cout << "  " << detail << endl;
            reportFile << "  " << detail << endl;
        }
    }
    
    reportFile.close();
    cout << "\nReport saved to: " << filename << endl;
}

void Teacher::logout()
{
    teacher_login = false;
    cout << "Logged out successfully!" << endl;
}
