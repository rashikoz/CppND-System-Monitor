#include <string>
#include "format.h"

using namespace std;

// Done: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
    string elapsedTimeStr, tempString;
    int hours, mins, secs, reminder;
    hours = int(seconds/3600);
    reminder = seconds%3600;
    mins = int(reminder/60);
    secs = int(reminder%60);
    tempString = to_string(hours);
    if (tempString.size() == 1){
        elapsedTimeStr += ("0" + tempString + ":");
    }
    else{
        elapsedTimeStr +=  (tempString + ":");
    }
    tempString = to_string(mins);
    if (tempString.size() == 1){
        elapsedTimeStr += ("0" + tempString + ":");
    }
    else{
        elapsedTimeStr +=  (tempString + ":");
    }
    tempString = to_string(secs);
    if (tempString.size() == 1){
        elapsedTimeStr += ("0" + tempString);
    }
    else{
        elapsedTimeStr +=  tempString;
    } 
    return elapsedTimeStr;
}