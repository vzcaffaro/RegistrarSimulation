#include <iostream>
#include "fileReader.h"

class Window
{
public:
    double idleTime; //tracks time the window is idle
    int timeLeft; //tracks how much time is left in helping a student
    Student *helped; //stores which student is being helped
    bool occupied; //whether or not a window is occupied

    Window();
    ~Window();
};
