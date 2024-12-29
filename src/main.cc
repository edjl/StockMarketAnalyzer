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


    cout << endl;
    printHeader();

    simulateBuyHold(filename);
    cout << endl;

    simulateBuyDip(filename);
    cout << endl;

    vector<int> rocPeriods = {1, 5, 10, 20};
    for (int period : rocPeriods) {
        simulateROC(filename, period);
        cout << endl;
    }

    vector<int> emaPeriodsMomentum = {5, 10, 20};
    for (int period : emaPeriodsMomentum) {
        simulateEMA(filename, period);
        cout << endl;
    }
    vector<int> emaPeriodsMR = {5, 10, 20, 60, 120, 240};
    for (int period : emaPeriodsMR) {
        simulateMeanReversion(filename, period);
        cout << endl;
    }


    printFooter(startDate, endDate, endDate < getLatestMarketDate_Minus2Weeks());

    return 0;
}
