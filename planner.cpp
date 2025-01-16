# include<iostream>
# include<chrono>
# include<fstream>
# include <thread>
# include <vector>
# include <conio.h>
# include <iomanip>

using namespace std;
using namespace std::chrono;

class Task{
    private:
    string taskName;
    int dueDate[3];
    //[0] is day, [1] is month [2] is year
    const string MONTHS[13] = {"ERROR", "January", "Feburary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    
    void printDueDate()
    {
        cout<<dueDate[0]<<" "<< MONTHS[dueDate[1]]<< " " << dueDate[2];
    }

    bool verifyDate(int day, int month, int year)
    {
        bool isLeapYear = false;
        //first check year
        if (year > 2000)
        {
            //valid year
        }
        else 
        {
            //cout << "ERROR: Enter a valid year" << endl;
            return false;
        }

        //check if a leap year
        if (year % 4 == 0 && year % 100 != 0)
        {
            isLeapYear = true;
        }
        else if (year % 100 == 0)
        {
            if (year % 400 == 0)
            {
                isLeapYear = true;
            }
        }
        else
        {
            //stays false
            isLeapYear = false;
        }

            //if year % 4 == 0 && year % 100 != 0
            //leap
            //else if year % 100 == 0
                //if year %400 == 0
                //leap
            //else
            //not leap


        //then check month
        if (month < 13 && month > 0)
        {
            //USED TO ASSIGN DIRECTLY
            //does nothing, passes
        }
        else 
        {
            //cout << "ERROR: Enter a valid month" << endl;
            return false;
        }


        //then check day
        int maxDay = 0;
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        {
            maxDay = 31;
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11 ) 
        {
            maxDay = 30;
        }
        else if (month == 2)
        {
            if (isLeapYear)
            {
                maxDay = 29;
            }
            else
            {
                maxDay = 28;
            }
        }
        else
        {
            cout <<"ERROR: Enter a valid month" << endl;
            return false;
        }

        //check the day
        if (day <= maxDay && day > 0)
        {
            //passes
        }
        else
        {
            return false;
        }
        

        //passes all conditions, so returns true;
        return true;
    }
    public:
    bool isComplete;
    void saveTask()
    {
        ofstream tasksFile;
        tasksFile.open("saved_tasks.txt", ios::app);
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

        int day, month, year = 0;
        cout << "Enter Day (DD MM YYYY): ";
        cin >> day >> month >> year;
        
        bool correctDate = verifyDate(day, month, year);
        while (!correctDate)
        {
            cout << "ERROR: Invalid Date" << endl; 
            cout <<"Enter a new VALID date (DD MM YYYY): ";
            cin >> day >> month >> year;
            correctDate = verifyDate(day, month, year);
        } 
        if (correctDate)
        {
            dueDate[0] = day;
            dueDate[1] = month;
            dueDate[2] = year;
        }
    }
        
    Task(string initTaskName, int day, int month, int year, bool complete)
    {

        taskName = initTaskName;
        bool correctDate = verifyDate(day, month, year);
        if (correctDate)
        {
            dueDate[0] = day;
            dueDate[1] = month;
            dueDate[2] = year;
        }
        else
        {
            dueDate[0] = -1;
            dueDate[1] = -1;
            dueDate[2] = -1;
        }
        isComplete = complete;
        taskName = initTaskName;
    }

    string getTaskName()
    {
        return taskName;
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

    int getDay()
    {
        return dueDate[0];
    }

    int getMonth()
    {
        return dueDate[1];
    }

    int getYear()
    {
        return dueDate[2];
    }

    int getDateSum()
    {
        //values are multiplied to avoid a datesum conflict (ex sum of 1 10 2024 is greader than 2 1 2025)
        return dueDate[0] + (dueDate[1] * 10) + (dueDate[2] * 100);
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

    void loadAllTasks()
    {
        //clear vector to remove any extra garbage tasks
        taskListVector.clear();
        ifstream tasksFile;
        tasksFile.open("saved_tasks.txt");
        //store all tasks
        string name;
        int day, month,year = 0;
        bool complete;

        int i = 0;
        while(tasksFile >> name >> day >> month >> year >> complete)
        {
            taskListVector.push_back(new Task(name, day, month, year, complete));
            i++;
        }
        tasksFile.close();
    }

    void toggleCompleteTask(int taskNumber)
    {
        
        taskNumber -= 1;

        if (taskListVector.empty())
        {
            cout << "Empty Task List" <<endl;
            return;
        }
        if (taskNumber >= 0 && taskNumber < taskListVector.size())
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

        //writes this to file
        //rewrites entire list again, using save task just duplicates the task
        updateTaskFile();
    }

    void deleteTask(int index)
    {

        taskListVector.erase(taskListVector.begin() + index);
        //removes from vector, now reprint
        updateTaskFile();
    }

    void updateTaskFile()
    {
        ofstream taskWrite;
        taskWrite.open("saved_tasks.txt");
        for (int i = 0; i < taskListVector.size(); i++)
        {
            if (!taskWrite.fail())
            {  
                string taskName = taskListVector[i]->getTaskName();
                int dueDay = taskListVector[i]->getDay();
                int dueMonth = taskListVector[i]->getMonth();
                int dueYear = taskListVector[i]->getYear();
                //writes to task
                taskWrite << taskName << " " << dueDay << " " << dueMonth << " " << dueYear << " " << taskListVector[i]->isComplete << endl;
            }
        }
        taskWrite.close();
    }

    void sortByDueDate()
    {
        //just sorts the vector by due date, which allows you to change how the txt file is organized dynamically by calling this before saving in the save function
        //organize by date sum
        //need to only access datesums 
        quicksort(taskListVector, 0, taskListVector.size() - 1);
        updateTaskFile();
    }

    private:
    //PASS YOUR ARRAYS BY REFERENCE IF YOURE SORTING AN ARRAY
    int partition(vector<Task*>& arr, int low, int high)
    {
        int pivot = arr[low]->getDateSum();
        //left and right pointers
        int i = low;
        int j = high;
        //as long as pointers don't cross
        while (i < j)
        {
            while (arr[i]->getDateSum() <= pivot && i <= high - 1)
            {
                i++;
            }

            while (arr[j]->getDateSum() > pivot && j >= low + 1)
            {
                //goes right to left, so reduce!
                j--;
            }

            //if pointers haven't crossed, swap
            if (i < j)
            {
                Task* temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }

        Task* temp2 = arr[j];
        arr[j] = arr[low];
        arr[low] = temp2;
        return j;
    }
    //adapted for type of task* and accessing the dateSums
    void quicksort(vector<Task*>& array, int start, int end)
    {
            //base case
            if (start >= end)
            {
                //smallest possible
                return;
            }

            //create a helper function that finds your "partition"
            int pivot = partition(array, start, end);
            //your recursive case (pivot part is already sorted so ignor)
            quicksort(array, start, pivot - 1);
            quicksort(array, pivot + 1, end);
    }
};

class Clock{
    public: 

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
       }
       else
       {
        cout<<"Cancelled Timer" << endl;
       }

    }

    void pauseAndCancel(int &timeInSeconds)
    {
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
                   cout << "\nTimer paused... Press SPACE to resume, press ESCAPE to Delete Timer" << endl;
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
    Timer* workTimer;
    Timer* breakTimer;
    int totalWorkMinutes;
    int workMinutes;
    int breakMinutes;
    int timerRepeat;
    int leftoverWork;
    public: 

    PomodoroTimer()
    {

        cout << "What's your total work time?: ";
        cin >> totalWorkMinutes;
        cout << "Work time (1 sitting in minutes): ";
        cin >> workMinutes;
        workTimer = new Timer(0, workMinutes, 0);
        cout << "How long is your break time (minutes)?: ";
        cin >> breakMinutes;
        breakTimer = new Timer(0, breakMinutes, 0);

        timerRepeat = totalWorkMinutes / (workMinutes + breakMinutes);

        leftoverWork = totalWorkMinutes - ((workMinutes + breakMinutes) * timerRepeat);
        
        workTimer = new Timer(0, workMinutes, 0);
        breakTimer = new Timer(0, breakMinutes, 0);

    }

    void saveSettings(int workMins, int breakMins)
    {
        ofstream settings;
        settings.open("pomodoro_settings.txt");
        settings << workMins << breakMins;

    }

    void loadSettings()
    {
        ifstream settings;
        settings.open("pomodoro_settings.txt");
        settings >> workMinutes >> breakMinutes;

    }
    
    void start()
    {
        int workSessions = timerRepeat;
        if (leftoverWork > 0)
        {
            workSessions++;
            //if no leftover work, no need for last break, so removed
        }
        for (int i = 0; i < timerRepeat; i++)
        {
            //loop for how many work and break times there are
            cout << endl << endl << "Work session " << i + 1 << "/" << workSessions <<endl; 
            workTimer->start();
            //should be able to press escape to cancel timer

            //this should stop entire thread, so 2nd break timer can't start until this finishes
            //let work timer start and go on, should be able to control, right?
            //workTimer should be done by now, so run break timer
            cout << endl << endl << "Break " << i + 1 << "/" << timerRepeat << endl;
            breakTimer->start();
        }
        //timer made for extra time
        delete workTimer;

        cout << endl << endl << "Work session " << workSessions << "/" << workSessions <<endl;
        workTimer = new Timer(0, leftoverWork, 0);
        workTimer->start();
        cout << endl << endl << "Work Done!";
        this_thread::sleep_for(seconds(5));
    }

};


class SubTimer : public Timer{
    string timerName;
    public:
    SubTimer (string initTimerName, int initHours, int initMinutes, int initSeconds)
    : Timer(initHours, initMinutes, initSeconds)
    {
        timerName = initTimerName;
    }
    string getName()
    {
        return timerName;
    }
};

int main() {
    //create save file for tasks
    TaskList mainTaskList;
    mainTaskList.loadAllTasks();
    mainTaskList.sortByDueDate();
bool exitProgram = false;
while(!exitProgram) {
    cout<< "+==================================================================+"<< endl;
    cout<< "                     T A S K  M A S T E R  VER. 0.1                "<<endl;
    cout<< "                            Copyright A. Ray                       "<<endl;
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
        //TASK MENU
        case 1:{
            bool backtoMain = false;
            cout << string(100, '\n');
            while (!backtoMain)
            {
            //Tasks Menu
                cout << "+=========================+" << endl;
                cout << "      T A S K  M E N U     " << endl;
                cout << "+=========================+" << endl;
                cout << "1. Create New Task" << endl;
                cout << "2. View All Tasks" << endl;
                cout << "3. Complete/Uncomplete Task" << endl;
                cout << "4. Delete Tasks" << endl;
                cout << "5. Back To Main Menu" << endl;
                string input2;
                cin >> input2; 
                int taskInput = stoi(input2);
                //switch statements are good for menu options
                switch (taskInput){
                    case 1:{
                        Task* newTask = new Task();
                        newTask->saveTask(); 
                        break;
                    }
                    case 2:{
                        mainTaskList.loadAllTasks();
                        mainTaskList.printAllTasks();
                        break;
                    }
                    
                    case 3:{
                        mainTaskList.loadAllTasks();
                        mainTaskList.printAllTasks();
                        cout << endl << "Enter the number of the task you want to change: ";
                        string completeInput;
                        cin >> completeInput;
                        while (stoi(completeInput) > mainTaskList.taskListVector.size() || stoi(completeInput) <= 0)
                        {
                            cout << endl 
                                 << "INVALID INPUT: Enter valid task number between 1 and " 
                                 << mainTaskList.taskListVector.size() << ": ";
                            cin >> completeInput;
                        }
                            mainTaskList.toggleCompleteTask(stoi(completeInput));
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
                                string taskNumber;
                                cout << "Choose a task to delete: ";
                                cin >> taskNumber;
                                while (stoi(taskNumber) > mainTaskList.taskListVector.size() || stoi(taskNumber) < 1)
                                {
                                    cout << "Please enter a valid task number between 1 and " 
                                         << mainTaskList.taskListVector.size() 
                                         << ": ";
                                    cin >> taskNumber;  
                                }
                                mainTaskList.deleteTask(stoi(taskNumber) - 1);
                                break;
                            }
                            case 2:{
                                for (int i = 0; i < mainTaskList.taskListVector.size(); i++)
                                {
                                    //to make sure list is as updated as possible
                                   // mainTaskList.loadAllTasks();
                                    if (mainTaskList.taskListVector[i]->isComplete == true)
                                    {
                                        mainTaskList.deleteTask(i);
                                        //to prevent skipping over new values as list shrinks in size
                                        i--;
                                    }
                                }
                                break;
                            }
                         }
                         break;
                    }
                    case 5:{
                    backtoMain = true;
                    break;
                    }
                    
            }
        }
        break;
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
                cout << "2. Sub Timer" << endl;
                cout << "3. Main Menu" << endl;
                string input3;
                cin >> input3; 
                int timerInput = stoi(input3);
                
                //want UI that allows you to access both
                switch(timerInput){
                    case 1:{
                        PomodoroTimer* currentTimer = new PomodoroTimer();
                        currentTimer->start();
                        break;
                    }

                    case 2:{
                        
                        int initHours, initMinutes, initSeconds = 0;
                        string timerName;
                        // prompt user
                        cout << "Enter time name (in one string): ";
                        cin >> timerName;
                        cout << "Enter hours, minutes, and seconds of timer (ex 1 1 1 for 1 hour, 1 min, 1 sec): ";
                        cin >> initHours >> initMinutes >> initSeconds;
                        SubTimer* subTimer = new SubTimer(timerName, initHours, initMinutes, initSeconds); 
                        cout <<"+======" << timerName << "======+" << endl;
                        subTimer->start();
                        break;
                    }

                    case 3:{
                        backtoMain = true;
                        break;
                    }
                }
            }
            break;
        }
        //QUIT 
        case 3: {
        //quit
        exitProgram = true;
        break;
        }   
        
    return 0;
}
}
}
