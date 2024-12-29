#ifndef STOCK_SIMULATOR_H
#define STOCK_SIMULATOR_H

#include "StockDataPoint.h"
#include <fstream> 
#include <string>
#include <vector>

void setStartEndDates(std::ifstream&file, std::string& startDate, std::string& endDate);
bool readCSVLine(std::ifstream& file, StockDataPoint& stock);

void calcBuyHold(const std::string filename, std::vector<double>& stats, int days);

void calcBuyDip(const std::string filename, std::vector<double>& stats, double percentage);

void calcROC(const std::string filename, std::vector<double>& stats, double threshold, int period);

void calcEMA(const std::string filename, std::vector<double>& stats, double threshold, int period);

void calcMeanReversion(const std::string filename, std::vector<double>& stats, double threshold, int period);
    
#endif