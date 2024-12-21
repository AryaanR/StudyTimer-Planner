# include<iostream>
# include<chrono>
# include<fstream>

using namespace std;

class Task{
    string taskName;
    string date;
    bool isComplete;
    void saveTask(ofstream tasksFile)
    {
        tasksFile.open("allTasks.txt");
        //iterate to end of list and store?
    }
    static void loadAllTasks(ifstream tasksFile)
    {
        tasksFile.open("allTasks.txt");
    }


};

//how to use date and time in c++
class Timer{
    string timerName;
    int timeMinutes;
    float ETC;
};

int main()
{
    auto timePoint = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(timePoint);

    cout<< time;
}