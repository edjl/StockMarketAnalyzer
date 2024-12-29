#include "StockDataPoint.h"
#include "StockSimulator.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

void setStartEndDates(ifstream&file, string& startDate, string& endDate) {
    string line;
    getline(file, line);
    getline(file, line);
    stringstream ss(line);
    getline(ss, startDate, ',');

    while(getline(file, line)) {
        stringstream ss(line);
        getline(ss, endDate, ',');
    }
}

bool readCSVLine(ifstream& file, StockDataPoint& stock) {
    string line;

    if (getline(file, line)) {
        stringstream ss(line);
        string token;

        getline(ss, stock.date, ',');
        getline(ss, token, ',');
        stock.open = stod(token);
        getline(ss, token, ',');
        stock.high = stod(token);
        getline(ss, token, ',');
        stock.low = stod(token);
        getline(ss, token, ',');
        stock.close = stod(token);
        getline(ss, token, ',');
        stock.volume = stoi(token);

        return true;
    }

    return false;
}

