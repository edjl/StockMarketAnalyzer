#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void printStats(const vector<double>& stats, string name) {
    cout << name << fixed << setprecision(2)
        << "\t$" << stats[0] << (stats[0] < 1000 ? "\t" : "")
        << "\t$" << stats[1] << (stats[1] < 1000 ? "\t" : "")
        << "\t" << 100 * stats[1] / stats[0] << "%"
        << setprecision(0)
        << "\t\t" << stats[2] + stats[3] 
        << endl;
}

void printBuyHoldStats(const vector<double>& stats, int days) {
    string name = "Buy Hold Strategy (" + to_string(days) + (days == 1 ? " day" : " days") + "):";
    printStats(stats, name);
}

void printBuyDipStats(const vector<double>& stats, double dipPercentage) {
    stringstream ss;
    ss << fixed << setprecision(0) << 100 * dipPercentage;
    string name = "Buy Dip Strategy (" + ss.str() + "%):\t";
    printStats(stats, name);
}

void printROCStats(const vector<double>& stats, double threshold, int days) {
    stringstream ss;
    ss << fixed << setprecision(1) << threshold * 100;
    string name = "ROC Strategy (" + to_string(days) + (days == 1 ? " day" : " days") + ", " + ss.str() + "%):";
    printStats(stats, name);
}

void printEMAStats(const vector<double>& stats, double threshold, int days) {
    stringstream ss;
    ss << fixed << setprecision(1) << threshold * 100;
    string name = "EMA Strategy (" + to_string(days) + (days == 1 ? " day" : " days") + ", " + ss.str() + "%):";
    printStats(stats, name);
}

void printMeanReversionStats(const vector<double>& stats, double threshold, int days) {
    stringstream ss;
    ss << fixed << setprecision(0) << threshold * 100;
    string name = "Mean Reversion (" + to_string(days) + (days == 1 ? " day" : " days") + ", " + ss.str() + "%):";
    printStats(stats, name);
}
