#include "Printer.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void printHeader() {
    cout << left << setw(40) << "" 
         << fixed << setprecision(2)
         << setw(16) << "Invested" 
         << setw(16) << "Profit"
         << setw(10) << "Gain"
         << setw(15) << "Trade Count"
         << endl << endl;
}

void printFooter(string startDate, string endDate, bool dateExpired) {
    cout << "** " << startDate << " - " << endDate << " **" << endl;
    if (dateExpired) {
        cout << "** " << "Note: your local .csv file of stock prices is outdated by more than 2 weeks." << " **" 
            << endl << "Please run the script: src/webscraper.py" << endl << endl;
    }
}

void printStats(const vector<double>& stats, string name) {
    stringstream stream;
    stream << fixed << setprecision(2) << 100 * stats[1] / stats[0];
    string gain = stream.str();
    
    cout << left << setw(40) << name 
         << fixed << setprecision(2)
         << "$" << setw(15) << stats[0] 
         << "$" << setw(15) << stats[1] 
         << setw(gain.length()) << gain
         << setw(10 - gain.length()) << (gain == "nan" ? "" : "%") 
         << setprecision(0) <<setw(15) << stats[2] + stats[3] 
         << endl;
}

void printBuyHoldStats(const vector<double>& stats, int days) {
    string name = "Buy Hold (" + to_string(days) + (days == 1 ? " day" : " days") + "):";
    printStats(stats, name);
}

void printBuyDipStats(const vector<double>& stats, double dipPercentage) {
    stringstream ss;
    ss << fixed << setprecision(0) << 100 * dipPercentage;
    string name = "Buy Dip (" + ss.str() + "%):";
    printStats(stats, name);
}

void printROCStats(const vector<double>& stats, double threshold, int days) {
    stringstream ss;
    ss << fixed << setprecision(1) << threshold * 100;
    string name = "ROC Momentum (" + to_string(days) + (days == 1 ? " day" : " days") + ", " + ss.str() + "%):";
    printStats(stats, name);
}

void printEMAStats(const vector<double>& stats, double threshold, int days) {
    stringstream ss;
    ss << fixed << setprecision(1) << threshold * 100;
    string name = "EMA Momentum (" + to_string(days) + (days == 1 ? " day" : " days") + ", " + ss.str() + "%):";
    printStats(stats, name);
}

void printMeanReversionStats(const vector<double>& stats, double threshold, int days) {
    stringstream ss;
    ss << fixed << setprecision(0) << threshold * 100;
    string name = "EMA MR (" + to_string(days) + (days == 1 ? " day" : " days") + ", " + ss.str() + "%):";
    printStats(stats, name);
}
