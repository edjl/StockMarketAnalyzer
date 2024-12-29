#ifndef STOCK_DATA_POINT_H
#define STOCK_DATA_POINT_H

#include <string>

struct StockDataPoint {
    std::string date;
    double open;
    double high;
    double low;
    double close;
    double volume;
};

#endif // STOCK_DATA_POINT_H
