#include "GenQueue.h"
#include "Student.h"

extern GenQueue<Student> *waitLine; //allows referencing of queues defined in main
extern GenQueue<Student> *helpedLine;

class fileReader
{
public:
    int windows;//stores number of windows open
    std::string line; //stores line from file
    int students; //stores number of students arriving at a time
    int time; //stores time arrived

    fileReader();
    ~fileReader();
    void readFile(std::string file); //method used to read file and fill queue with student objects
    int getWindows();//allows main to access number of windows

};
