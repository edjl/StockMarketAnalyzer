
#include "WebscraperRunner.h"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string getLatestMarketDate_Minus2Weeks() {
    time_t t = time(nullptr);
    tm* currentTime = localtime(&t);
    int hour = currentTime->tm_hour;
    tm previousDay = *currentTime;

    if (hour >= 9) {
        previousDay.tm_mday -= 1;
    }
    else {
        previousDay.tm_mday -= 2;
    }

    mktime(&previousDay);
    if (previousDay.tm_wday == 0) { // Sunday
        previousDay.tm_mday -= 2; // Move to Friday
    } else if (previousDay.tm_wday == 6) { // Saturday
        previousDay.tm_mday -= 1; // Move to Friday
    }
    previousDay.tm_mday -= 14;

    mktime(&previousDay);
    stringstream prevDateStream;
    prevDateStream << previousDay.tm_year + 1900 << "-"
                   << setfill('0') << setw(2) << previousDay.tm_mon + 1 << "-"
                    << setw(2) << previousDay.tm_mday;
    return prevDateStream.str();
}

void runWebscraperScript() {
    string scriptName = "webscraper.py";
    string command = "python3 " + scriptName;
    int result = system(command.c_str());
    if (result != 0) {
        cerr << "Error running the script: " << scriptName << endl;
    }
}
