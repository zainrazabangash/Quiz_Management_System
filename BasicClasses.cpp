#include "QuizSystem.h"

// Menu Class Implementation
char Menu::showMenu()
{
    char choice;

    cout << "Are you a teacher or a student or just want to check the courses offered?" << endl;
    cout << "Press 't' for teacher, 's' for student, 'c' for courses offered, or 'e' to exit" << endl;
    cin >> choice;

    while((choice != 't') && (choice != 's') && (choice != 'c') && (choice != 'e') && 
          (choice != 'T') && (choice != 'S') && (choice != 'C') && (choice != 'E'))
    {
        cout << "Invalid choice, please enter again" << endl;
        cin >> choice;
    }

    return choice;
}

// CourseOffering Class Implementation
void CourseOffering::display_courses()
{
    ifstream courseFile;
    string* courses = new string[100];
    courseFile.open("data/CourseOffering.txt", ios::in);

    if (courseFile.is_open())
    {
        cout << "Courses offered are: " << endl;

        while (!courseFile.eof())
        {
            for (int i = 0; i < 100; i++)
            {
                getline(courseFile, courses[i]);
            }

            for (int i = 0; courses[i] != "\0"; i++)
            {
                cout << courses[i] << endl;
            }
        }
    }

    courseFile.close();
    delete[] courses;
}

// User Class Implementation
User::User()
{
    name = "";
    ID = 0;
    email = "";
    password = "";
    teacher_login = false;
    student_login = false;
}

User::User(string n, int id, string e, string p)
{
    name = n;
    ID = id;
    email = e;
    password = p;
    teacher_login = false;
    student_login = false;
}

void User::setName(string n)
{
    name = n;
}

string User::getName()
{
    return name;
}

void User::setID(int id)
{
    ID = id;
}

int User::getID()
{
    return ID;
}

void User::setEmail(string e)
{
    email = e;
}

string User::getEmail()
{
    return email;
}

void User::login()
{
    char choice = usertype.showMenu();

    if (choice == 't' || choice == 'T')
    {
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter your email: ";
        getline(cin, email);

        cout << "Enter your password: ";
        getline(cin, password);

        ifstream teacherFile;

        string* name_read_teach = new string[100];
        string* email_read_teach = new string[100];
        string* password_read_teach = new string[100];

        teacherFile.open("teachers/teacherLogin.txt");

        while (!teacherFile.eof())
        {
            for (int i = 0; i < 100; i++)
            {
                getline(teacherFile, name_read_teach[i]);
                getline(teacherFile, email_read_teach[i]);
                getline(teacherFile, password_read_teach[i]);
            }

            for (int i = 0; name_read_teach[i] != "\0"; i++)
            {
                if (name_read_teach[i] == name)
                {
                    if (email_read_teach[i] == email)
                    {
                        if (password_read_teach[i] == password)
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
        
        delete[] name_read_teach;
        delete[] email_read_teach;
        delete[] password_read_teach;
    }

    else if (choice == 's' || choice == 'S')
    {
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter your email: ";
        getline(cin, email);

        cout << "Enter your password: ";
        getline(cin, password);

        ifstream studentFile;

        string* name_read_stu = new string[100];
        string* email_read_stu = new string[100];
        string* password_read_stu = new string[100];

        studentFile.open("students/studentLogin.txt");

        if (studentFile.is_open())
        {
            int i = 0;
            while (!studentFile.eof() && i < 100)
            {
                getline(studentFile, name_read_stu[i]);
                getline(studentFile, email_read_stu[i]);
                getline(studentFile, password_read_stu[i]);
                i++;
            }

            for (int j = 0; j < i && name_read_stu[j] != ""; j++)
            {
                if (name_read_stu[j] == name)
                {
                    if (email_read_stu[j] == email)
                    {
                        if (password_read_stu[j] == password)
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
        }
        else
        {
            cout << "Login unsuccessful" << endl;
        }

        studentFile.close();
        
        delete[] name_read_stu;
        delete[] email_read_stu;
        delete[] password_read_stu;
    }

    else if (choice == 'c' || choice == 'C')
    {
        coursesOffered.display_courses();
    }
}

// QuestionBank Class Implementation
QuestionBank::QuestionBank()
{
    question_topics = "";
    mcqs_questions = "";
    mcqs_correct_options = "";
    true_false_questions = "";
    descriptive_questions = "";
}

string QuestionBank::get_Mcqs()
{
    return mcqs_questions;
}

void QuestionBank::import_questions()
{
    ifstream questionFile;
    string check_marker; 
    int topics_index = 0, mcqs_index = 0, mcqs_correct = 0, true_false_index = 0, descriptive_index = 0;
    questionFile.open("data/Questions.txt", ios::in);

    if (questionFile.is_open()) 
    {
        while (!questionFile.eof()) 
        {
            getline(questionFile, check_marker);

            if (check_marker.compare("a5380ee") == 0)
            {
                string temp = "";
                do
                {
                    getline(questionFile, temp);
                    question_topics += temp;
                    question_topics += "\n";

                }while ((temp != "" ) && !questionFile.eof());
            }

            else if (check_marker.compare("2efcde9") == 0)
            {
                string temp = "";
                do 
                {
                    getline(questionFile, temp);
                    mcqs_questions += temp;
                    mcqs_questions += "\n";
                
                }while ((temp != "") && !questionFile.eof());
            }

            else if (check_marker.compare("dabfac4") == 0)
            {
                string temp = "";
                do
                {
                    getline(questionFile, temp);
                    mcqs_correct_options += temp;
                    mcqs_correct_options += "\n";

                }while ((temp != "") && !questionFile.eof());
            }

            else if (check_marker.compare("b94d27b") == 0)
            {
                string temp = "";
                do
                {
                    getline(questionFile, temp);
                    true_false_questions += temp;
                    true_false_questions += "\n";

                }while ((temp != "") && !questionFile.eof());
            }

            else if (check_marker.compare("88f7ace") == 0)
            {
                string temp = "";
                do
                {
                    getline(questionFile, temp);
                    descriptive_questions += temp;
                    descriptive_questions += "\n";

                }while ((temp != "") && !questionFile.eof());
            }
        }
    }

    questionFile.close();
}

void QuestionBank::display_questions()
{
    cout << "Which type of questions would you like to see?" << endl;
    cout << "1. MCQs" << endl;
    cout << "2. True/False" << endl;
    cout << "3. Descriptive" << endl;
    cout << "Enter your choice: " << endl;

    int choice;
    cin >> choice;

    switch (choice)
    {
        case 1:
            cout << "MCQs Questions:" << endl;
            cout << mcqs_questions << endl;
            break;

        case 2:
            cout << "True/False Questions:" << endl;
            cout << true_false_questions << endl;
            break;

        case 3:
            cout << "Descriptive Questions:" << endl;
            cout << descriptive_questions << endl;
            break;

        default:
            cout << "Invalid choice" << endl;
            break;
    }
}
