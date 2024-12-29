#include "StockSimulator.h"
#include <fstream>
#include <queue>
#include <string>
#include <iostream>

using namespace std;

/*
 * Calculates the rate of change using the open and close prices (for a given period)
 * Buys if increase is above threshold
 * Sells if decrease is above threshold
 */
void calcROC(const string filename, vector<double>& stats, double threshold, int period){

    queue<StockDataPoint> lastData;
    StockDataPoint data;
    ifstream file(filename);
    string line;
    getline(file, line);

    // Calculate initial metrics
    for (int i = 0; i < period - 1; i++) {
        readCSVLine(file, data);
        lastData.push(data);
    }

    queue<double> holdings;

    // Start of simulation
    while (readCSVLine(file, data)) {
        lastData.push(data);

        double roc =  (data.close - lastData.front().open) / lastData.front().open / period;
        if (roc >= threshold) {
            holdings.push(data.close);
            stats[0] += data.close;
            stats[2]++;
        }
        else if (!holdings.empty() && -1 * roc >= threshold) {
            double buyPrice = holdings.front();
            holdings.pop();
            stats[1] += data.close - buyPrice;
            stats[3]++;
        }

        lastData.pop();
    }

    while(!holdings.empty()) {
        double buyPrice = holdings.front();
        holdings.pop();
        stats[1] += data.close - buyPrice;
        stats[3]++;
    }

}
