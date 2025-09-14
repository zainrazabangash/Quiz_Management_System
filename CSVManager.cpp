#include "QuizSystem.h"

// CSV Manager Implementation
CSVManager::CSVManager()
{
    // Initialize course codes and names based on the CSV structure
    courseCodes = {"CS101", "CS201", "CS102", "CS301", "CS302", "SE301", "CS501", "CS407", "CS307", "CS601", "CS409"};
    courseNames = {"Programming Fundamentals", "Object Oriented Programming", "Introduction To Computing", 
                   "Data Structures", "Analysis of Algorithms", "Software Requirements Engineering", 
                   "Research Methodology", "Big Data Analytics", "Artificial Intelligence", 
                   "Deep Learning", "Digital Image Processing"};
}

bool CSVManager::loadCSVData(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Could not open CSV file: " << filename << endl;
        return false;
    }
    
    string line;
    int lineNumber = 0;
    
    while (getline(file, line))
    {
        lineNumber++;
        
        // Skip header lines (lines 1 and 2)
        if (lineNumber <= 2)
        {
            cout << "Skipping header line " << lineNumber << ": " << line.substr(0, 50) << "..." << endl;
            continue;
        }
        
        // Skip empty lines
        if (line.empty() || line.find_first_not_of(" \t,") == string::npos)
        {
            continue;
        }
            
        vector<string> fields = parseCSVLine(line);
        
        // Debug output for first few lines
        if (lineNumber <= 5) {
            cout << "Line " << lineNumber << ": " << line << endl;
            cout << "Fields count: " << fields.size() << endl;
            if (!fields.empty()) {
                cout << "First field: '" << fields[0] << "'" << endl;
            }
        }
        
        if (fields.size() >= 3 && !fields[0].empty() && !fields[1].empty() && !fields[2].empty()) // At least S#, Roll No., Student Name
        {
            // Check if first field is numeric (serial number)
            bool isNumeric = true;
            for (char c : fields[0]) {
                if (!isdigit(c)) {
                    isNumeric = false;
                    break;
                }
            }
            
            if (isNumeric) {
                try {
                    StudentRecord student;
                    student.serialNumber = stoi(fields[0]);
                    student.rollNumber = fields[1];
                    student.studentName = fields[2];
            
                    // Parse course enrollments (starting from index 3)
                    for (int i = 3; i < fields.size() && i < 3 + courseCodes.size(); i++)
                    {
                        if (fields[i] == "1")
                        {
                            student.enrolledCourses.push_back(courseCodes[i - 3]);
                        }
                    }
                    
                    students.push_back(student);
                }
                catch (const std::invalid_argument& e) {
                    cout << "Error parsing line " << lineNumber << ": " << e.what() << endl;
                    cout << "Problematic line: " << line << endl;
                }
            }
        }
    }
    
    file.close();
    cout << "Successfully loaded " << students.size() << " student records from CSV." << endl;
    return true;
}

vector<string> CSVManager::parseCSVLine(const string& line)
{
    vector<string> fields;
    stringstream ss(line);
    string field;
    
    while (getline(ss, field, ','))
    {
        // Remove leading/trailing whitespace
        field.erase(0, field.find_first_not_of(" \t"));
        field.erase(field.find_last_not_of(" \t") + 1);
        
        // Handle empty fields - convert to empty string
        if (field.empty())
        {
            fields.push_back("");
        }
        else
        {
            fields.push_back(field);
        }
    }
    
    return fields;
}

void CSVManager::importAllStudents()
{
    if (students.empty())
    {
        cout << "No student data loaded. Please load CSV data first." << endl;
        return;
    }
    
    ofstream studentFile;
    studentFile.open("students/studentLogin.txt", ios::app);
    
    if (studentFile.is_open())
    {
        for (const auto& student : students)
        {
            // Generate a default email and password
            string email = student.rollNumber + "@nu.edu.pk";
            string password = "Student" + to_string(student.serialNumber) + "!";
            
            studentFile << endl;
            studentFile << student.studentName << endl;
            studentFile << email << endl;
            studentFile << password << endl;
        }
        
        studentFile.close();
        cout << "Successfully imported " << students.size() << " students to login system." << endl;
        cout << "Default passwords are: Student[SerialNumber]!" << endl;
    }
    else
    {
        cout << "Error: Could not open studentLogin.txt for writing." << endl;
    }
}

void CSVManager::importStudentsByCourse(const string& courseCode)
{
    if (students.empty())
    {
        cout << "No student data loaded. Please load CSV data first." << endl;
        return;
    }
    
    vector<string> enrolledStudents = getStudentsByCourse(courseCode);
    
    if (enrolledStudents.empty())
    {
        cout << "No students found enrolled in course: " << courseCode << endl;
        return;
    }
    
    cout << "Students enrolled in " << courseCode << ":" << endl;
    for (const auto& student : enrolledStudents)
    {
        cout << "- " << student << endl;
    }
}

bool CSVManager::isStudentEnrolled(const string& rollNumber, const string& courseCode)
{
    for (const auto& student : students)
    {
        if (student.rollNumber == rollNumber)
        {
            for (const auto& course : student.enrolledCourses)
            {
                if (course == courseCode)
                    return true;
            }
        }
    }
    return false;
}

vector<string> CSVManager::getStudentsByCourse(const string& courseCode)
{
    vector<string> enrolledStudents;
    
    for (const auto& student : students)
    {
        for (const auto& course : student.enrolledCourses)
        {
            if (course == courseCode)
            {
                enrolledStudents.push_back(student.studentName + " (" + student.rollNumber + ")");
                break;
            }
        }
    }
    
    return enrolledStudents;
}

vector<string> CSVManager::getCoursesByStudent(const string& rollNumber)
{
    vector<string> enrolledCourses;
    
    for (const auto& student : students)
    {
        if (student.rollNumber == rollNumber)
        {
            return student.enrolledCourses;
        }
    }
    
    return enrolledCourses;
}

void CSVManager::displayAllCourses()
{
    cout << "\n=== AVAILABLE COURSES ===" << endl;
    for (int i = 0; i < courseCodes.size(); i++)
    {
        cout << (i + 1) << ". " << courseCodes[i] << " - " << courseNames[i] << endl;
    }
}

void CSVManager::displayCourseEnrollment(const string& courseCode)
{
    vector<string> enrolledStudents = getStudentsByCourse(courseCode);
    
    cout << "\n=== ENROLLMENT FOR " << courseCode << " ===" << endl;
    cout << "Total enrolled students: " << enrolledStudents.size() << endl;
    
    for (const auto& student : enrolledStudents)
    {
        cout << "- " << student << endl;
    }
}

void CSVManager::generateStudentAccounts()
{
    if (students.empty())
    {
        cout << "No student data loaded. Please load CSV data first." << endl;
        return;
    }
    
    cout << "Generating student accounts..." << endl;
    importAllStudents();
    
    // Also update course offering file
    updateCourseOffering();
}

void CSVManager::updateCourseOffering()
{
    ofstream courseFile;
    courseFile.open("data/CourseOffering.txt", ios::out);
    
    if (courseFile.is_open())
    {
        for (int i = 0; i < courseCodes.size(); i++)
        {
            courseFile << (i + 1) << ". " << courseCodes[i] << " - " << courseNames[i] << endl;
        }
        courseFile.close();
        cout << "Course offering file updated successfully." << endl;
    }
    else
    {
        cout << "Error: Could not update course offering file." << endl;
    }
}
