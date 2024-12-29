#include "Printer.h"
#include "Sim.h"
#include "StockSimulator.h"
#include <future>
#include <thread>
#include <vector>

using namespace std;

vector<double> initialStats(4, 0.0);

void simulateBuyHold(const string filename) {
    int buyHoldCount = 5;
    vector<int> buyDays = {1, 5, 10, 20, 60};
    vector<vector<double>> buyHoldStats(buyHoldCount, initialStats);
    vector<future<void>> buyHoldFutures;

    for (int i = 0; i < buyHoldCount; i++) {
        buyHoldFutures.push_back(async(launch::async, calcBuyHold, filename, ref(buyHoldStats[i]), buyDays[i]));
    }
    for (int i = 0; i < buyHoldCount; i++) {
        buyHoldFutures[i].get();
        printBuyHoldStats(buyHoldStats[i], buyDays[i]);
    }
}

void simulateBuyDip(const string filename) {
    int buyDipCount = 5;
    vector<double> dipPercentages = {0.0, 0.02, 0.05, 0.1, 0.2};
    vector<vector<double>> buyDipStats(buyDipCount, initialStats);
    vector<future<void>> buyDipFutures;

    for (int i = 0; i < buyDipCount; i++) {
        buyDipFutures.push_back(async(launch::async, calcBuyDip, filename, ref(buyDipStats[i]), dipPercentages[i]));
    }
    for (int i = 0; i < buyDipCount; i++) {
        buyDipFutures[i].get();
        printBuyDipStats(buyDipStats[i], dipPercentages[i]);
    }
}

void simulateROC(const string filename, int period) {
    int rocCount = 5;
    vector<double> rocThresholds = {0.0, 0.005, 0.01, 0.015, 0.02};
    vector<vector<double>> rocStats(rocCount, initialStats);
    vector<future<void>> rocFutures;

    for (int i = 0; i < rocCount; i++) {
        rocFutures.push_back(async(launch::async, calcROC, filename, ref(rocStats[i]), rocThresholds[i], period));
    }
    for (int i = 0; i < rocCount; i++) {
        rocFutures[i].get();
        printROCStats(rocStats[i], rocThresholds[i], period);
    }
}

void simulateEMA(const string filename, int period) {
    int emaCount = 5;
    vector<double> emaThresholds = {0.0, 0.005, 0.01, 0.015, 0.02};
    vector<vector<double>> emaStats(emaCount, initialStats);
    vector<future<void>> emaFutures;

    for (int i = 0; i < emaCount; i++) {
        emaFutures.push_back(async(launch::async, calcROC, filename, ref(emaStats[i]), emaThresholds[i], period));
    }
    for (int i = 0; i < emaCount; i++) {
        emaFutures[i].get();
        printEMAStats(emaStats[i], emaThresholds[i], period);
    }
}

void simulateMeanReversion(const string filename, int period) {
    int emaCount = 5;
    vector<double> emaThresholds = {0.0, 0.01, 0.02, 0.05, 0.1};
    vector<vector<double>> emaStats(emaCount, initialStats);
    vector<future<void>> emaFutures;

    for (int i = 0; i < emaCount; i++) {
        emaFutures.push_back(async(launch::async, calcMeanReversion, filename, ref(emaStats[i]), emaThresholds[i], period));
    }
    for (int i = 0; i < emaCount; i++) {
        emaFutures[i].get();
        printMeanReversionStats(emaStats[i], emaThresholds[i], period);
    }
}