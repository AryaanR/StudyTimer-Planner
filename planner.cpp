# include<iostream>
# include<chrono>
# include<fstream>
//"thread" allows you to pass off certain parts of this program to different threads in the CPU, or just stop the thread/ process entirely
# include <thread>

using namespace std;
using namespace std::chrono;
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
    public:
    string timerName;
    int timeMinutes;
    float ETC;
    //duration is an "interval of time" type and "time point" is a point in time, two different things
    void setTimer(int mins, system_clock::time_point timePoint)
    {
        //works now!
        auto newTime = system_clock::to_time_t(timePoint + minutes(mins));
        cout<<"ETC: " << ctime(&newTime);
    }
};

int main()
{
    Timer timer;
    //system clock is a static member class of chrono that has all the stuff like "now()" and time conversion from epoch time to human readable time
    auto timePoint = chrono::system_clock::now();
    auto time = system_clock::to_time_t(timePoint);

    timer.setTimer(10, timePoint);
    
    cout<< ctime(&time);
    //"stops" the thread for 1 second, converted to one second via the chrono library, which knows what 1 second is in computer clock speed
    this_thread::sleep_for(chrono::seconds(1));
}