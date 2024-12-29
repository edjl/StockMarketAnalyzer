#include "StockSimulator.h"
#include <fstream>
#include <queue>
#include <string>
#include <iostream>

using namespace std;

/*
 * Calculates a rolling average with the last 50 prices (closing)
 * Buys if lower than the average by [percentage]
 * Sells if higher than the average by [percentage]
 */
void calcBuyDip(const string filename, vector<double>& stats, double percentage) {

    double average = 0;
    int initialAverageCount = 50;
    queue<double>prices;
    ifstream file(filename);
    string line;
    getline(file, line);
    StockDataPoint data;

    // Calculate initial metrics
    for (int i = 0; i < initialAverageCount; i++) {
        readCSVLine(file, data);
        average += data.close;
        prices.push(data.low + data.high);
    }
    average /= initialAverageCount;

    double buyPoint = (1 - percentage) * average;
    double sellPoint = (1 + percentage) * average;
    queue<double> holdings;

    // Start of simulation
    while (readCSVLine(file, data)) {
        double currPrice = data.close;
        if (currPrice <= buyPoint) {
            holdings.push(currPrice);
            stats[0] += currPrice;
            stats[2]++;
        }
        else if (!holdings.empty() && sellPoint <= currPrice) {
            double buyPrice = holdings.front();
            holdings.pop();
            stats[1] += currPrice - buyPrice;
            stats[3]++;
        }
        average -= prices.front() / initialAverageCount;
        average += currPrice / initialAverageCount;
        prices.pop();
        prices.push(currPrice);
    }

    while(!holdings.empty()) {
        double buyPrice = holdings.front();
        stats[1] += data.close - buyPrice;
        stats[3]++;
    }
}
