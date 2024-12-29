#include "StockSimulator.h"
#include <fstream>
#include <queue>
#include <string>
#include <iostream>

using namespace std;

/*
 * Calculates a buy and hold strategy (closing)
 * Buys always
 * Sells all at the end
 */
void calcBuyHold(const string filename, vector<double>& stats, int days){

    ifstream file(filename);
    string line;
    getline(file, line);
    StockDataPoint data;
    int day = 1;
    double currPrice = 0.0;

    // Start of simulation
    while (readCSVLine(file, data)) {
        if (day % days == 0) {
            currPrice = data.close;
            stats[0] += currPrice;
            stats[2]++;
        }
        day++;
    }

    //cout << days << "    " << stats[0]  << endl;

    stats[1] = stats[2] * currPrice - stats[0];
    stats[3] = stats[2];
}
