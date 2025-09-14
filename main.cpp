#include "QuizSystem.h"

int main()
{
    Menu menu;
    char choice;
    
    do
    {
        cout << "\n=== WELCOME TO QUIZ MANAGEMENT SYSTEM ===" << endl;
        choice = menu.showMenu();

        if ((choice == 't') || (choice == 'T'))
        {
            Teacher teacher;
            teacher.menu();
        }
        else if ((choice == 's') || (choice == 'S'))
        {
            Student student;
            student.startMenu();
        }
        else if ((choice == 'c') || (choice == 'C'))
        {
            CourseOffering course;
            course.display_courses();
            cout << "\nPress Enter to return to main menu...";
            cin.ignore();
            cin.get();
        }
        else if ((choice == 'e') || (choice == 'E'))
        {
            cout << "Exiting the program..." << endl;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
        
    } while (choice != 'e' && choice != 'E');
    
    cout << "Thank you for using Quiz Management System. Goodbye!" << endl;
    return 0;
}
