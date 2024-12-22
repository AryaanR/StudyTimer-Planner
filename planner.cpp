# include<iostream>
# include<chrono>
# include<fstream>
//"thread" allows you to pass off certain parts of this program to different threads in the CPU, or just stop the thread/ process entirely
# include <thread>

using namespace std;
using namespace std::chrono;
class Task{
    private:
    string taskName;
    int dueDate[3];
    //[0] is day, [1] is month [2] is year
    bool isComplete;
    const string MONTHS[13] = {"", "January", "Feburary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    void saveTask(ofstream tasksFile)
    {
        tasksFile.open("allTasks.txt");
        //iterate to end of list and store?
    }
    void printDueDate()
    {
        cout<<dueDate[0]<<" "<< MONTHS[dueDate[1]]<< " " << dueDate[2];
    }

    public:
    static void loadAllTasks(ifstream tasksFile)
    {
        tasksFile.open("allTasks.txt");
    }

    static void printAllTasks(ofstream tasksFile)
    {
       tasksFile.open("allTasks.txt");
        
    }

    Task(string newTaskName)
    {
        isComplete = false;
        taskName = newTaskName;
        while (dueDate[0], dueDate[1], dueDate[2] < 1, dueDate[2] < 2024)
        {
            cout << "Enter Day (DD MM YYYY): ";
            cin >> dueDate[0] >> dueDate[1] >> dueDate[2];
        }
        //checks if dates are correct
    }
    void printTask()
    {
        cout<<"TASK: " << taskName << endl<< "  Due: ";
        printDueDate();
        cout<<endl;
    }
};

class Clock{
    public: 
    //make this a process in another thread to stop it from stopping program
    static void printTime()
    {
        while (true)
        {
            //system clock is a static member class of chrono that has all the stuff like "now()" and time conversion from epoch time to human readable time
            auto timePoint = chrono::system_clock::now();
            auto time = system_clock::to_time_t(timePoint);
            cout<< ctime(&time) << flush;
            //"stops" the thread for 1 second, converted to one second via the chrono library, which knows what 1 second is in computer clock speed
            this_thread::sleep_for(chrono::seconds(5));
        }
    }
};
//how to use date and time in c++
class Timer{
    public:
    int secondsTime;
    int minutesTime;
    int hoursTime;

    Timer()
    {
        cout << "Timer Duration (hours mins seconds): ";
        cin >> hoursTime >> minutesTime >> secondsTime;
    }

    Timer(int initHours, int initMinutes, int initSeconds)
    {
        secondsTime = initSeconds;
        minutesTime = initMinutes;
        hoursTime = initHours;
    }
};

class pomodoroTimer : Timer{

    Timer workTimer;
    Timer breakTimer;
    float ETC;
    //duration is an "interval of time" type and "time point" is a point in time, two different things
    void setTimer(int mins, system_clock::time_point timePoint)
    {
        auto newTime = system_clock::to_time_t(timePoint + hours(hoursTime) 
        + minutes(minutesTime)
        + seconds(secondsTime));
        cout<<"ETC: " << ctime(&newTime);
    }
};


class SubTimer : Timer{
    string timerName;

    SubTimer (string initTimerName, int initHours, int initMinutes, int initSeconds)
    : Timer(initHours, initMinutes, initSeconds)
    {

    }
};

int main()
{
    cout<< "===================================================================="<< endl;
    cout<< "                     T A S K  M A S T E R  VER. 0.1                "<<endl;
    cout<< "===================================================================="<< endl;
    //UI
    cout << "Choose an option: " <<endl;
    cout << "1. Tasks" << endl << "2. Timers" << endl << "3. Quit" << endl;
    string input;
    cin >> input; 
    int intInput = stoi(input);
    while (intInput > 3 || intInput < 1)
    {
        cout << "Please choose a valid option" << endl;
        cin >> input; 
        intInput = stoi(input);
        cout<< intInput;
    }
    if (intInput == 1)
    {
        //Tasks Menu
    }

    if (intInput == 2)
    {
        //Timers Menu
    }

    if (intInput == 3)
    {
        //quit
        cout<<"Quitting...";
        return 0;
    }
}