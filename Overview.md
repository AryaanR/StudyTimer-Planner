# Task Master -- Study timer/To do List

Core Features
------Done-----
- Tasks (Name, due date, is complete)
- Main Timer with custom pomodoro (where user can adjust break and work time) 
- ETC for your timer
- organize tasks by due date
- Safety settings to stop user from entering invalid dates, or from invalid dates causing a segfault when printing

---NOT DONE----
- Work timer settings that are saved to a file (different)


Nice to Have:
- Task descriptions
- Reminder notifications
- "Forget me not" Tasks (daily stuff you keep on forgetting, like exercising or brushing)
- AI-connected habit help (how do i make this habit stick?)
- //feature to give total time you have, and then creates a schedule based on that and your saved preferences, or you give it a schedule and it makes it for you


UI (Command Line MVP)
    /*
    1. Tasks
    2. Timers
    3. Quit
    
    if Tasks
    1. Load All Tasks
    2. Create a new task
    3. Save Task

    if Timers
    1. Work Timer
    2. Work Timer Settings

    in work Timer mode...
    1. Pause (update ETC every minute)
    2. Create Sub Timer

    */

Good things done:
- scope control (by this overview doc to show essentials and extras, as well as ui menu)
- class-based program
- saving and serializing into a file

Things to improve next time:
- better scope of project (didn't know how to actually turn into UI until too late and already made)
- system design plan (what each class is, what it should have, how one should inherit from the other and when one can be polymorphic)
- LOG HOW MUCH TIME YOU SPENT ON YOUR PROJECTS (to gauge time needed for a project)
