#include "QuizSystem.h"

// TimeSetter Class Implementation
void TimeSetter::setTime(int h, int m, int s)
{
    hours = h;
    minutes = m;
    seconds = s;
}

void TimeSetter::getTime()
{
    cout << hours << ":" << minutes << ":" << seconds << endl;
}

void TimeSetter::addTime(int h, int m, int s)
{
    hours += h;
    minutes += m;
    seconds += s;

    if (seconds >= 60)
    {
        minutes += seconds / 60;
        seconds = seconds % 60;
    }

    if (minutes >= 60)
    {
        hours += minutes / 60;
        minutes = minutes % 60;
    }

    if (hours >= 24)
    {
        hours = hours % 24;
    }
}

void TimeSetter::subtractTime(int h, int m, int s)
{
    hours -= h;
    minutes -= m;
    seconds -= s;

    if (seconds < 0)
    {
        minutes -= seconds / 60;
        seconds = seconds % 60;
    }

    if (minutes < 0)
    {
        hours -= minutes / 60;
        minutes = minutes % 60;
    }

    if (hours < 0)
    {
        hours = hours % 24;
    }
}

tm TimeSetter::CurrentTime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return *ltm;
}

void TimeSetter::setDuration(int h, int m, int s)
{
    hours = h;
    minutes = m;
    seconds = s;
}

void TimeSetter::remainingTime()
{
    tm ltm = CurrentTime();

    int h = ltm.tm_hour;
    int m = ltm.tm_min;
    int s = ltm.tm_sec;

    int remaining_hours = hours - h;
    int remaining_minutes = minutes - m;
    int remaining_seconds = seconds - s;

    if (remaining_seconds < 0)
    {
        remaining_minutes -= remaining_seconds / 60;
        remaining_seconds = remaining_seconds % 60;
    }

    if (remaining_minutes < 0)
    {
        remaining_hours -= remaining_minutes / 60;
        remaining_minutes = remaining_minutes % 60;
    }

    if (remaining_hours < 0)
    {
        remaining_hours = remaining_hours % 24;
    }

    cout << "Remaining time: " << remaining_hours << ":" << remaining_minutes << ":" << remaining_seconds << endl;
}

// QuizSetter Class Implementation
QuizSetter::QuizSetter()
{
    questionBank.import_questions();
}

void QuizSetter::Menu()
{
    cout << "Quiz Management System" << endl;
    cout << "1. Create Quiz from Question Bank" << endl;
    cout << "2. Add Custom Questions" << endl;
    cout << "3. Set Quiz Duration" << endl;
    cout << "4. View Available Questions" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    switch(choice)
    {
        case 1:
            createQuizFromBank();
            break;
        case 2:
            addCustomQuestions();
            break;
        case 3:
            setQuizDuration();
            break;
        case 4:
            questionBank.display_questions();
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
    }
}

void QuizSetter::createQuizFromBank()
{
    cout << "Creating quiz from question bank..." << endl;
    cout << "Enter quiz name: ";
    string quizName;
    cin.ignore();
    getline(cin, quizName);
    
    ofstream quizFile;
    quizFile.open("quizzes/quiz_" + quizName + ".txt", ios::out);
    
    if (quizFile.is_open())
    {
        quizFile << "Quiz: " << quizName << endl;
        quizFile << "Created from Question Bank" << endl;
        quizFile << "Date: " << __DATE__ << " " << __TIME__ << endl;
        quizFile << "---" << endl;
        
        // Import questions from the existing question bank
        questionBank.import_questions();
        
        // Display available questions and let user select
        cout << "Available questions from question bank:" << endl;
        questionBank.display_questions();
        
        cout << "Quiz created successfully!" << endl;
        quizFile.close();
    }
}

void QuizSetter::addCustomQuestions()
{
    cout << "Adding custom questions..." << endl;
    cout << "Enter question: ";
    cin.ignore();
    getline(cin, question);
    
    cout << "Question type:" << endl;
    cout << "1. MCQ" << endl;
    cout << "2. True/False" << endl;
    cout << "3. Descriptive" << endl;
    cout << "Choose: ";
    
    int type;
    cin >> type;
    
    ofstream customFile;
    customFile.open("data/custom_questions.txt", ios::app);
    
    if (customFile.is_open())
    {
        // Add a newline before appending new data to ensure proper separation
        customFile << endl;
        customFile << "Custom Question: " << question << endl;
        customFile << "Type: " << type << endl;
        customFile << "---" << endl;
        customFile.close();
        cout << "Custom question added!" << endl;
    }
}

void QuizSetter::setQuizDuration()
{
    cout << "Setting quiz duration..." << endl;
    cout << "Enter duration in minutes: ";
    cin >> duration;
    
    ofstream durationFile;
    durationFile.open("data/quiz_duration.txt", ios::out);
    if (durationFile.is_open())
    {
        durationFile << duration << " minutes" << endl;
        durationFile.close();
        cout << "Quiz duration set to " << duration << " minutes" << endl;
    }
}
