#include "Window.h"
#include <iostream>
#include <algorithm>

using namespace std;

GenQueue<Student> *waitLine = new GenQueue<Student>();
GenQueue<Student> *helpedLine = new GenQueue<Student>();

int main (int argc, char** argv)
{
    bool loop = true;
    bool windowsEmpty = true;
    bool isFull = false;

    int clock = 0; //tracks total minutes
    int workingWindows = 0;
    int www; //int for tracking which window is open

    Student *stud; //pointer to student object that allows use of ->
    Student tempStudent;
    Student checkStudent; //checks if next student arrived at same time
    Student *checkPointer; //pointer for checkStudent
    Window tempWindow;
    Window *wind; //pointer for tempWindow

    string file_arg = argv[1]; //stores comman line arg for in file

    fileReader fr;
    fr.readFile(file_arg); //reads file and fills queue with students
    int numWindows = fr.getWindows(); //stores number of windows


    Window* openWindows[numWindows]; //creates array of window pointers for open windows
    for(int i = 0; i<numWindows; i++)
    {
        openWindows[i] = new Window(); //fills array with empty windows
    }


    while(loop==true) //while simulation is still runnin
        {
            for(int q = 0; q<numWindows ; q++) //loops through windows
            {
                if(openWindows[q]->occupied)//checks if any windows are occupied
                {
                    windowsEmpty = false;// if any are occupied, it sets boolean to false and breaks
                    break;
                }
                else
                    windowsEmpty = true; // if all are unoccupied, sets boolean to true
            }
            if(windowsEmpty && waitLine->isEmpty()) //checks if all windows are empty and waitline is empty
            {
                loop = false; //exits loop
            }



            if(!waitLine->isEmpty()) //as long as there are more students in line
            {
                tempStudent = waitLine->peek(); //looks at next student in line
                stud = &tempStudent; //stores address of tempStudent


                if(stud->timeArrived == clock)//student has arrived at the current hour
                {
                    helpedLine->insert(waitLine->remove()); //removes student from waiting line and adds to second queue
                    for(int a = 0; a < numWindows ; ++a)//finds an open window
                    {
                        if(openWindows[a]->occupied == false)//if the windows indexed at a is not occupied
                        {
                            www = a;//www is the index of an open window
                            break;
                        }
                    }

                    wind = openWindows[www]; //unoccupied window
                    wind->helped = stud; //assigning student pointer to window
                    wind->timeLeft = stud->timeReq; //assigns time remaining to window
                    wind->occupied = true;

                    ++workingWindows;

                }

            }



            for(int i = 0; i<numWindows; i++)//checks if all windows are full
            {
                if(openWindows[i]->occupied==false)//looks at all windows in the array
                {
                    isFull=false;//if any windows are not occupied, isFull=false and the loop is broken
                    break;
                }else{
                    isFull=true; //if all windows are occupied, isFull=true
                }
            }
            //increment wait time
            if(isFull && !waitLine->isEmpty())//if all the windows are occupied and there are still people in line
            {
                unsigned int size = waitLine->myQueue->size; //records size of the line
                for(int s = 0; s<size ; s++)//loops through line
                {
                    Student sss = waitLine->remove();//removes the front students
                    Student *sssp = &sss;
                    double tempWait = sssp->wait; //stores the student's current wait time
                    tempWait++; //increments wait
                    sssp->wait = tempWait; //stores incremented wait time
                    waitLine->insert(sss); //reinserts student to the queue
                }

            }





            if(!waitLine->isEmpty()) //if there are more students in line
            {
                checkStudent = waitLine->peek();//checks the next student in the queue
                checkPointer = &checkStudent;
                if(checkPointer->timeArrived != clock) //only increments time if the next student has not arrived at the current time
                    {
                        ++clock;//increments time
                        for(int y = 0 ; y<numWindows ; y++)
                        {
                            if (openWindows[y]->occupied && (openWindows[y]->timeLeft!=0)) //if a window is occupied and still has time remaining to help student
                            {
                                openWindows[y]->timeLeft--; //decrements time left
                            }
                            else if (openWindows[y]->occupied && (openWindows[y]->timeLeft==0)) //if a window is occupied but has no time remaining in helping the student, we open the window up
                            {
                                openWindows[y]->occupied = false;
                                --workingWindows;
                            }
                            else if (openWindows[y]->occupied == false) //if a window is not being used, we increment idleTime
                            {
                                openWindows[y]->idleTime++;
                            }
                        }
                    }
            } else { //if no more students are in line
                ++clock;
                for(int y = 0 ; y<numWindows ; y++)
                {
                    if (openWindows[y]->occupied && (openWindows[y]->timeLeft!=0)) //if a window is occupied and still has time remaining to help student
                    {
                        openWindows[y]->timeLeft--; //decrements time left
                    }
                    else if (openWindows[y]->occupied && (openWindows[y]->timeLeft==0)) //if a window is occupied but has no time remaining in helping the student, we open the window up
                    {
                        openWindows[y]->occupied = false;
                        --workingWindows;
                    }
                    else if (openWindows[y]->occupied == false) //if a window is not being used, we increment idleTime
                    {
                        openWindows[y]->idleTime++;
                    }
                }
            }


            cout<<"\n\nTime: "<<clock<<endl<<endl<<endl;
            for(int i = 0; i<numWindows ; i++)
            {
                wind = openWindows[i];
                cout<<"Window: "<<i+1<<endl;
                cout<<"Occupied: "<<wind->occupied<<endl;
                cout<<"Idle time: "<<wind->idleTime<<endl;
                if(wind->occupied)
                    cout<<"Time left: "<<wind->timeLeft<<endl;
                cout<<endl;
            }


    }
    double sumWait = 0;
    int numStudents = helpedLine->myQueue->size; //stores length of line
    double waitArray[numStudents]; //array to be filled with wait times of each students
    double medianArray[numStudents]; //array filled with wait times to calculate median
    double median;
    int x = 0; //counting variable used for assigning values to arrays
    while(!helpedLine->isEmpty())
    {
        Student s1 = helpedLine->remove();//removes and stores student info
        Student *s1p = &s1;
        double tempWait = s1p->wait; //stores wait time
        waitArray[x] = tempWait; //fills both arrays
        medianArray[x] = tempWait;
        ++x; //increments x
        sumWait+=tempWait; //calculates total wait time
    }






    double meanWait = sumWait/numStudents; //calculates the mean

    double greatestWait =0; //sets greatestWait to zero so it can be compared
    for(int i=0; i<numStudents ; i++)
    {
        if(waitArray[i] > greatestWait) //if any value is larger
            greatestWait = waitArray[i]; //stores the largest value
    }

    double numWaitOverTen = 0;
    for(int i=0; i<numStudents ; i++)
    {
        if(waitArray[i] >= 10)
            ++numWaitOverTen; //increments only if wait time value is over 10
    }

    int numWaited = 0; //tracks how many students had a value other than 0 for wait time
    for(int i = 0; i<numStudents ; i++)
    {
        if(medianArray[i] > 0)
            ++numWaited;
    }
    double finalMedianArray[numWaited]; //a final array that ignores all 0 values
    int count = 0;
    for(int k =0; k<numStudents ; k++)
    {
        if(medianArray[k] > 0)
        {
            finalMedianArray[count] = medianArray[k]; //assigns value to final array only if not 0
            count++;
        }
    }



    sort(finalMedianArray, finalMedianArray + numWaited); //sorts the array in ascending order

    if(numWaited%2 == 0) //if total number of values in array is even
    {
        median = (finalMedianArray[(numWaited/2) - 1] + finalMedianArray[numWaited/2]) / 2 ; //averages the two middle elements
    } else { //if total number of values is odd
        median = finalMedianArray[(numWaited/2)]; //accesses the middle element
    }


    cout<<"MEAN STUDENT WAIT TIME: "<<meanWait<<endl;
    cout<<"MEDIAN STUDENT WAIT TIME: "<<median<<endl;
    cout<<"GREATEST STUDENT WAIT TIME: "<<greatestWait<<endl;
    cout<<"STUDENTS WAITING OVER 10 MINUTES: "<<numWaitOverTen<<endl;


    double sumIdle = 0;
    double meanIdle = 0;
    double longIdle = 0;
    int numOverFive = 0;

    for(int w = 0; w<numWindows ; w++) //loops through openWindows
    {
        double tempIdle = openWindows[w]->idleTime;
        sumIdle += tempIdle;//sums up idle times
        if(tempIdle > longIdle)//if value is greater than currently stored
            longIdle = tempIdle; //overwrite value
        if(tempIdle >= 5)//if value greater than 5
            ++numOverFive; //increment count

    }
    meanIdle = sumIdle/numWindows;//calculate mean

    cout<<"MEAN WINDOW IDLE TIME: "<<meanIdle<<endl;
    cout<<"LONGEST WINDOW IDLE TIME: "<<longIdle<<endl;
    cout<<"WINDOWS IDLING OVER 5 MINUTES: "<<numOverFive<<endl;












}
