#include "fileReader.h"
#include <iostream>
#include <fstream>

using namespace std;

fileReader::fileReader() //default constructor
{
    students = 0;
    windows = 0;
    time = 0;
}

fileReader::~fileReader() //default destructor
{}

void fileReader::readFile(string file)
{
    Student *s;

    ifstream inf;
    inf.open(file);

    getline(inf,line); //line 1
    windows=stoi(line); //stores windows open
    while(inf.peek() != EOF)//while the file is not over
    {
        getline(inf,line); //time
        time=stoi(line); //stores time students arrive
        getline(inf,line); //line 2
        students=stoi(line); //stores number of students at that time
        for(int i = 0; i<students; i++)
        {
            s = new Student();
            s->timeArrived=time;
            getline(inf,line); //time required for student
            s->timeReq = stoi(line);
            waitLine->insert(*s); //inserts student into line
        }

    }

}

int fileReader::getWindows()
{
    return windows;
}
