#include "StockSimulator.h"
#include <fstream>
#include <queue>
#include <string>
#include <iostream>

using namespace std;

/*
 * Calculates the short term and long term EMA
 * Buys if short term EMA is above long term EMA by threshold
 * Sells if short term EMA is below long term EMA by threshold
 */
void calcEMA(const string filename, vector<double>& stats, double threshold, int period) {

    StockDataPoint data;
    ifstream file(filename);
    string line;
    getline(file, line);

    // Calculate initial metrics
    double shortMultiplier = 2.0 / (period + 1);
    double longMultiplier = 2.0 / (2 * period + 1);
    readCSVLine(file, data);
    double shortEMA = data.close;
    double longEMA = data.close;

    for (int i = 1; i < 2 * period - 1; i++) {
        readCSVLine(file, data);
        shortEMA = (data.close * shortMultiplier) + (shortEMA * (1 - shortMultiplier));
        longEMA = (data.close * longMultiplier) + (longEMA * (1 - longMultiplier));
    }

    queue<double> holdings;

    // Start of simulation
    while (readCSVLine(file, data)) {
        shortEMA = (data.close * shortMultiplier) + (shortEMA * (1 - shortMultiplier));
        longEMA = (data.close * longMultiplier) + (longEMA * (1 - longMultiplier));

        if ((1 + threshold) * longEMA <= shortEMA) {
            holdings.push(data.close);
            stats[0] += data.close;
            stats[2]++;
        }
        else if (!holdings.empty() && shortEMA <= (1 - threshold) * longEMA) {
            double buyPrice = holdings.front();
            holdings.pop();
            stats[1] += data.close - buyPrice;
            stats[3]++;
        }
    }

    while(!holdings.empty()) {
        double buyPrice = holdings.front();
        holdings.pop();
        stats[1] += data.close - buyPrice;
        stats[3]++;
    }

}
