#include "QuizSystem.h"

// Demo program to show CSV integration
int main()
{
    cout << "=== CSV INTEGRATION DEMO ===" << endl;
    
    CSVManager csvManager;
    
    // Load CSV data
    cout << "\n1. Loading CSV data..." << endl;
    if (csvManager.loadCSVData("Course Registration Data - Sheet1.csv"))
    {
        cout << "✓ CSV data loaded successfully!" << endl;
    }
    else
    {
        cout << "✗ Failed to load CSV data!" << endl;
        return 1;
    }
    
    // Display all courses
    cout << "\n2. Available courses:" << endl;
    csvManager.displayAllCourses();
    
    // Show enrollment for a specific course
    cout << "\n3. Students enrolled in CS201 (Object Oriented Programming):" << endl;
    csvManager.displayCourseEnrollment("CS201");
    
    // Check specific student enrollment
    cout << "\n4. Checking if student 20I-0622 is enrolled in CS201:" << endl;
    if (csvManager.isStudentEnrolled("20I-0622", "CS201"))
    {
        cout << "✓ Student 20I-0622 is enrolled in CS201" << endl;
    }
    else
    {
        cout << "✗ Student 20I-0622 is NOT enrolled in CS201" << endl;
    }
    
    // Show courses for a specific student
    cout << "\n5. Courses for student 20I-0622:" << endl;
    vector<string> courses = csvManager.getCoursesByStudent("20I-0622");
    if (!courses.empty())
    {
        for (const auto& course : courses)
        {
            cout << "- " << course << endl;
        }
    }
    else
    {
        cout << "No courses found for this student." << endl;
    }
    
    cout << "\n=== DEMO COMPLETED ===" << endl;
    return 0;
}
