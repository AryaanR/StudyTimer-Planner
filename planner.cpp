# include<iostream>
# include<chrono>
# include<fstream>
//"thread" allows you to pass off certain parts of this program to different threads in the CPU, or just stop the thread/ process entirely
# include <thread>
# include <vector>
# include <conio.h>
# include <iomanip>
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
        tasksFile.close();
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
        //load tasks again to update any new tasks
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
        tasksFile.close();
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

    void deleteTask(int taskNumber)
    {
        cout <<"DELETING... " << taskNumber <<endl;
        //erases that task (goes into file, finds that line, and erases it)
        
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
    bool isPaused;

    //TODO: Implement a reset function to allow the same timer to be reused

    void start()
    {
        int timeInSeconds = hoursTime * 3600 + minutesTime * 60 + secondsTime;
        cout << endl <<  "Starting Timer... (Press SPACE to pause/resume)" <<endl;
        etc();
        isPaused = false;
        //split while statement into a while (for when timer is done or not)
        //and and "paused, not paused if tree" inside this while loop, so program doesn't break out when paused
        while(timeInSeconds > 0)
        {
            if (!isPaused)
            {
                this_thread::sleep_for(seconds(1));
                timeInSeconds--;
                //to display minute and hourly time, take modulus of seconds by 3600 -> remainder seconds
                int remainderSeconds = timeInSeconds % 3600;
                int hoursLeft = (timeInSeconds - remainderSeconds) / 3600;
                int secondsLeft = remainderSeconds % 60;
                int minutesLeft = (remainderSeconds - secondsLeft) / 60;
                //subtract from total to get hours in seconds, and divide by 3600 to get hours
                // take remainder seconds and mod 60 to get number of seconds
                //subtract remainder by seconds to get minutes
                //clears previous line
                cout << "\r"<<hoursLeft << " hours, " 
                     << minutesLeft << " minutes, " 
                     << secondsLeft <<" seconds left." << flush;
                     //what does flush do?

                //change the actual value of the hours, minutes, and seconds time to adjust the etc when paused
                hoursTime = hoursLeft;
                minutesTime = minutesLeft;
                secondsTime = secondsLeft;
            }
            //checks if its paused or if want to unpause
            pauseAndCancel(timeInSeconds);
        }
       if (timeInSeconds > -1)
       {
        cout<< "Timer Complete!" << endl;
        //should store this into today's work time (in the pomodoro method, not this)
       }
       else
       {
        cout<<"Cancelled Timer" << endl;
        //should not store this time as "work time"
       }

    }
    //passes by reference to directly change the actual value in the original start function
    void pauseAndCancel(int &timeInSeconds)
    {
        //should have an option to cancel the timer and clear it!

        //should pause the time, and update the etc
        //how to "pause?"
        // if pause, it should break from the while loop, or at least stay in a state that it prints a prompt once and wait until the user presses another button?
        //better to use a boolean state as a toggle instead of asking for a keystroke twice
        if (_kbhit())
        {
            char ch = _getch();
            //if space is pressed
            if (ch == ' ')
            {
                //this converts a boolean value to its opposite (your toggle)
                isPaused = !isPaused;
                // stays in this loop until it gets an input
                if (isPaused)
                {
                   cout << "\nTimer paused... Press SPACE to resume, press ESCAPE to Ddlete" << endl;
                }
                else 
                {
                    cout << "\nTimer resumed!" << endl;
                    etc();
                }  
            }
            else if (ch == 27)
            {
                cout<< "cancelling timer..." <<endl;
                //not good to delete within itself, so just delete the instance where it is
                timeInSeconds = -1;
                return;
                //escape the function and change the time value to -1 so the timer cancels instead of "finishes"
            }
            

        }
    }

    void etc()
    {
        //displays estimated time of completion to the user relative to the system time
        auto endTimePoint = chrono::system_clock::now() + hours(hoursTime) + minutes(minutesTime) + seconds(secondsTime);
        auto endTime = system_clock::to_time_t(endTimePoint);
        //convert to regular day month hour format from epoch time
        tm* timeInfo = localtime(&endTime);
        
        // Format time without the date and seconds
        cout << "ETC: " << setfill('0') 
             << setw(2) << timeInfo->tm_hour << ":"
             << setw(2) << timeInfo->tm_min <<
             endl;
    }


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

class PomodoroTimer{
    //shouldn't prompt timer duration for this constructor!
    Timer* workTimer;
    Timer* breakTimer;
    int totalWorkMinutes;
    int workMinutes;
    int breakMinutes;
    int timerRepeat;
    int leftoverWork;
    //duration is an "interval of time" type and "time point" is a point in time, two different things
    //default constructor that does all the prompting
    public: 

    //bc derived, calling original blank constructor and then this constructor, Therefore don't make this a derived class of timer, as it behaves differently
    //why does this all happen in the constructor??
    PomodoroTimer()
    {
        //smth happens before constructor (constructor conflict between normal and overloaded one?)
        //should ask for total work time (minutes), and desired break time (ideally, store this as a preference in a .txt file later)
        cout << "What's your total work time?: ";
        cin >> totalWorkMinutes;
        cout << "Work time (1 sitting in minutes): ";
        cin >> workMinutes;
        workTimer = new Timer(0, workMinutes, 0);
        cout << "How long is your break time (minutes)?: ";
        cin >> breakMinutes;
        breakTimer = new Timer(0, breakMinutes, 0);
        //calculate repetitions of work, break cycle
        timerRepeat = totalWorkMinutes / (workMinutes + breakMinutes);
        //does this give the minutes or the seconds as well?
        leftoverWork = totalWorkMinutes - ((workMinutes + breakMinutes) * timerRepeat);
        cout <<"Total Work: " << totalWorkMinutes << ", Working " << workMinutes << " in one sitting, with " << breakMinutes << " minute breaks, repeated " << timerRepeat <<" times, with leftover time: " << leftoverWork <<endl;
        //cout<<"Total work time: " << ((workMinutes + breakMinutes) * timerRepeat + leftoverWork);
        //print the etc based on your total work minutes?, but you want this to update if paused, so take etcs from each timer, multiply by repetitions? or pause, when resume, take new time point and add time remaining from totalWorkMinutes??

        //create a work and a break timer of that length and time, and then delete and create new timers of the new lengths
        workTimer = new Timer(0, workMinutes, 0);
        breakTimer = new Timer(0, breakMinutes, 0);

    }

    void start()
    {
        for (int i = 0; i < timerRepeat; i++)
        {
            //loop for how many work and break times there are
            cout << endl << endl << "Work session " << i << "/" << timerRepeat <<endl; 
            workTimer->start();
            //should be able to press escape to cancel timer

            //this should stop entire thread, so 2nd break timer can't start until this finishes
            //let work timer start and go on, should be able to control, right?
            //workTimer should be done by now, so run break timer
            cout << endl << endl << "Break " << i << "/" << timerRepeat << endl;
            breakTimer->start();
        }
        //timer made for extra time
        delete workTimer;
        workTimer = new Timer(0, leftoverWork, 0);
        workTimer->start();
        cout << endl << endl << "Work Done!";
        this_thread::sleep_for(seconds(5));
    }

    //should also store the work data into a .txt file, as well as the day, so it can be displayed on a heat map
};

class SubTimer : Timer{
    string timerName;

    SubTimer (string initTimerName, int initHours, int initMinutes, int initSeconds)
    : Timer(initHours, initMinutes, initSeconds)
    {

    }
};

int main() {
    //create save file for tasks
    //does this create a file in the directory
    ofstream tasksOut;
    ifstream tasksIn;
    TaskList mainTaskList;
    mainTaskList.loadAllTasks(tasksIn);
bool exitProgram = false;
while(!exitProgram) {
    cout<< "+==================================================================+"<< endl;
    cout<< "                     T A S K  M A S T E R  VER. 0.1                "<<endl;
    cout<< "+==================================================================+"<< endl;
    //UI
    cout << "Choose an option: " <<endl;
    cout << "1. Tasks" << endl 
    << "2. Timers" << endl 
    << "3. Quit" << endl;
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
    switch (mainInput) {
        case 1:{
            bool backtoMain = false;
            cout << string(100, '\n');
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
                        mainTaskList.loadAllTasks(tasksIn);
                        mainTaskList.printAllTasks();
                        //FOR YOUR CHANGES TO BE UPDATED AND REREAD IN REAL TIME, MAKE SURE TO PROPERLY CLOSE THE FILE AFTER EDITING AND OPENING IT!
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
                    case 4:{
                    //delete a task or delete all completed tasks (move into a new menu?)
                    cout << endl << endl <<"1. Delete 1 Task" <<endl 
                         <<"2. Delete all completed tasks" << endl;
                         int case5Input;
                         cin >> case5Input;
                         switch(case5Input){

                            case 1:{
                                int taskNumber;
                                cout << "Choose a task to delete: ";
                                cin >> taskNumber;
                                mainTaskList.deleteTask(taskNumber);
                            }
                            case 2:{
                                for (int i = 1; i <= mainTaskList.taskListVector.size(); i++)
                                {
                                    if (mainTaskList.taskListVector[i]->isComplete == true)
                                    {
                                        mainTaskList.deleteTask(i);
                                    }
                                }
                            }

                         }
                    }
                    case 5:
                    backtoMain = true;
                    //break gets out of the entire switch statement
                    break;
            }
            //if you don't do this, it automatically goes to the next case
        }
       //TIMERS MENU
        case 2:{
                bool backtoMain = false;
                cout << string(100, '\n');
                while (!backtoMain){
                cout << string(100, '\n');
                cout << "+=========================+" << endl;
                cout << "     T I M E R  M E N U    " << endl;
                cout << "+=========================+" << endl;
                cout << "1. Work Timer (Pomodoro)" << endl;
                string input3;
                cin >> input3; 
                int timerInput = stoi(input3);
                
                //want UI that allows you to access both
                switch(timerInput){
                    case 1:{
                        //creating a pomodoro timer

                        PomodoroTimer* currentTimer = new PomodoroTimer();

                    }
                }
            }
        }

        case 3: {
        //quit
        exitProgram = true;
        break;
        }   
        
    cout<<"Quitting...";
    return 0;
}
}
}
