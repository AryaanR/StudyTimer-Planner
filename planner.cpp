# include<iostream>
# include<chrono>

using namespace std;

class Task{
    string taskName;
    string date;
    bool isComplete;

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