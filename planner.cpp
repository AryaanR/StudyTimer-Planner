# include<iostream>
# include<chrono>
# include<fstream>
//"thread" allows you to pass off certain parts of this program to different threads in the CPU, or just stop the thread/ process entirely
# include <thread>
# include <vector>
//open this in visual studio
//implement timer class feature (Actually counts down, can pause)
//implement pomodoro timner class feature (gives custom work time, custom break time, and ETC)

using namespace std;
using namespace std::chrono;
//maybe make tasks sort by due date when new task is added?
class Task{
    private:
    string taskName;
    int dueDate[3];
    //[0] is day, [1] is month [2] is year
    const string MONTHS[13] = {"", "January", "Feburary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    
    void printDueDate()
    {
        cout<<dueDate[0]<<" "<< MONTHS[dueDate[1]]<< " " << dueDate[2];
    }

    public:
    bool isComplete;
    void saveTask(ofstream& tasksFile)
    {
        tasksFile.open("saved_tasks.txt", ios::app);
        //make sure tasks don't interfere
        if (!tasksFile.fail())
        {
            string temp;
            tasksFile << taskName << " " << dueDate[0] << " " << dueDate[1] << " " << dueDate[2] << " " << isComplete << endl;
        }
    }

    Task()
    {
        isComplete = false;

        string initTaskName;
        cout << "NEW TASK, Enter task name (without spaces): ";
        cin >> initTaskName;
        taskName = initTaskName;
        while (dueDate[0], dueDate[1], dueDate[2] < 1, dueDate[2] < 2024)
        {
            cout << "Enter Day (DD MM YYYY): ";
            cin >> dueDate[0] >> dueDate[1] >> dueDate[2];
        }
        //checks if dates are correct
    }

    Task(string initTaskName, int day, int month, int year, bool complete)
    {
        isComplete = complete;
        taskName = initTaskName;
        dueDate[0] = day;
        dueDate[1] = month;
        dueDate[2] = year;
        cout <<" new task" << endl;
    }

    void printTask()
    {
        if (isComplete)
        {
            cout<< "|x|";
        }
        else if (!isComplete)
        {
            cout<< "| |";
        }
        cout<<"TASK: " << taskName << endl<< "  Due: ";
        printDueDate();
        cout<<endl;
    }
};

class TaskList{
    public:
    vector<Task*> taskListVector;
    void printAllTasks()
    {
        cout << endl << "+===========Main Tasks============+" << endl;
       for (int i = 0; i < taskListVector.size(); i++)
       {
            taskListVector[i]->printTask();
            cout<<endl;
       }
       cout <<endl;
    }

    void loadAllTasks(ifstream& tasksFile)
    {
        tasksFile.open("saved_tasks.txt");
        //store all tasks
        string name;
        int day, month,year = 0;
        bool complete;

        //MAKE SURE TO PASS BY REFERENCE
        while(tasksFile >> name >> day >> month >> year >> complete)
        {
            taskListVector.push_back(new Task(name, day, month, year, complete));
        }
        //load task by getting all its data in vars, passing it into 
        //should be able to load one task, and use this to load all
        //no need to split, if so, refactor
    }

    void toggleCompleteTask(int taskNumber)
    {
        //edit task (from looking at listand then save vector into file?
        taskNumber -= 1;

        if (taskNumber >= 0 || taskNumber < taskListVector.size())
        {
            if (taskListVector[taskNumber]->isComplete == false)
            {
                taskListVector[taskNumber]->isComplete = true;
            }
            else
            {
                taskListVector[taskNumber]->isComplete = false;
            }
        }
        else
        {
            cout << "Task number not found" << endl;;
        }
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
    //create save file for tasks
    //does this create a file in the directory
    ofstream tasksOut;
    ifstream tasksIn;
    TaskList mainTaskList;
    mainTaskList.loadAllTasks(tasksIn);
bool exitProgram = false;
while(!exitProgram)
{
    cout<< "+==================================================================+"<< endl;
    cout<< "                     T A S K  M A S T E R  VER. 0.1                "<<endl;
    cout<< "+==================================================================+"<< endl;
    //UI
    cout << "Choose an option: " <<endl;
    cout << "1. Tasks" << endl << "2. Timers" << endl << "3. Quit" << endl;
    string input;
    cin >> input; 
    int mainInput = stoi(input);
    while (mainInput > 3 || mainInput < 1)
    {
        cout << "Please choose a valid option" << endl;
        cin >> input; 
        mainInput = stoi(input);
        cout<< mainInput;
    }
    //MAIN MENU SELECTION
    switch (mainInput){
        case 1:{
            bool backtoMain = false;
            while (!backtoMain)
            {
                //create a back to main menu variable that stops this from going back to main menu and starting the timer one
            //Tasks Menu
                cout << "+=========================+" << endl;
                cout << "      T A S K  M E N U     " << endl;
                cout << "+=========================+" << endl;
                cout << "1. Create New Task" << endl;
                cout << "2. View All Tasks" << endl;
                cout << "3. Complete Task" << endl;
                cout << "4. Back To Main Menu" << endl;
                string input2;
                cin >> input2; 
                int taskInput = stoi(input2);
                //switch statements are good for menu options
                switch (taskInput){
                    case 1:{
                        Task* newTask = new Task();
                        //need to pass by reference: reference "trustworthy pointer that always points to smth"
                        //This is why passing by reference to an object can be done without the * notation
                        //fstream is an object, so passing by value causes a copy of the object, not what you want
                        //passing into a function is basically like saying "here's the object", by value makes a carbon copy on a printer, by reference (& to actual function) 
                        //connects a string to the object and gives it back!!
                        newTask->saveTask(tasksOut); 
                        //when you make a variable in c++, you can't "jump over" the declaration of a variable 
                        //without creating a new scope
                        break;
                    }
                    case 2:{
                        mainTaskList.printAllTasks();
                        break;
                    }
                    case 3:{
                        //Complete a task
                        //should set isComplete to one
                        //chose a task in the taskList to Complete
                        //Print all tasks
                        mainTaskList.printAllTasks();
                        cout << endl << "Enter the number of the task you want to tick as complete: ";
                        string completeInput;
                        cin >> completeInput;
                        mainTaskList.toggleCompleteTask(stoi(completeInput));
                        cout << "Task completed" <<endl;
                        mainTaskList.printAllTasks();
                        break;
                    }
                    //clear completed tasks
                    case 4:
                    backtoMain = true;
                }
            }
            //break gets out of the entire switch statement
            break;
            //if you don't do this, it automatically goes to the next case
        }
       //TIMERS MENU
        case 2:{
            bool backtoMain = false;
            while (!backtoMain)
            {
                cout << "+=========================+" << endl;
                cout << "     T I M E R  M E N U    " << endl;
                cout << "+=========================+" << endl;
                cout << "1. Work Timer (Pomodoro)" << endl;
                string input3;
                cin >> input3; 
                int timerInput = stoi(input3);
            }
        }
        case 3:
        //quit
        exitProgram = true;
    }
}

    cout<<"Quitting...";
    return 0;
}
