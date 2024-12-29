#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <sstream>
#include <vector>

void printHeader();
void printFooter(std::string startDate, std::string endDate, bool dateExpired);

void printStats(const std::vector<double>& stats, std::string name);

void printBuyHoldStats(const std::vector<double>& stats, int days);

void printBuyDipStats(const std::vector<double>& stats, double dipPercentage);

void printROCStats(const std::vector<double>& stats, double threshold, int days);

void printEMAStats(const std::vector<double>& stats, double threshold, int days);

void printMeanReversionStats(const std::vector<double>& stats, double threshold, int days);

#endif // PRINTER_H
