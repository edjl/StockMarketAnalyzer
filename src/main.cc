#include "Printer.h"
#include "Sim.h"
#include "StockSimulator.h"
#include "WebscraperRunner.h"
#include <iostream>
#include <locale>
#include <sstream>
#include <thread>
#include <vector>

using namespace std;

int main() {
    string filename = "prices/spy_daily.csv";
    cout.imbue(locale("en_US.UTF-8"));

    string startDate = "", endDate = "";
    ifstream file(filename);
    setStartEndDates(file, startDate, endDate);


    cout << endl << "\t\t\t\tInvested\tProfit\t\tGain\t\tTradeCount" << endl;
    cout << endl;

    simulateBuyHold(filename);
    cout << endl;

    simulateBuyDip(filename);
    cout << endl;

    vector<int> rocPeriods = {1, 5, 10, 20};
    for (int period : rocPeriods) {
        simulateROC(filename, period);
        cout << endl;
    }

    vector<int> emaPeriods = {5, 10, 20, 60, 120, 240};
    for (int period : emaPeriods) {
        simulateEMA(filename, period);
        cout << endl;
    }
    for (int period : emaPeriods) {
        simulateMeanReversion(filename, period);
        cout << endl;
    }


    cout << "** " << startDate << " - " << endDate << " **" << endl;
    if (endDate < getLatestMarketDate_Minus2Weeks()) {
        cout << "** " << "Note: your local .csv file of stock prices is outdated by more than 2 weeks." << " **" 
            << endl << "Please run the script: src/webscraper.py" << endl << endl;
    }

    return 0;
}
