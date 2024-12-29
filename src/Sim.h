#ifndef SIM_H
#define SIM_H

#include <string>
#include <vector>

extern std::vector<double> initialStats;

void simulateBuyHold(const std::string filename);

void simulateBuyDip(const std::string filename);

void simulateROC(const std::string filename, int period);

void simulateEMA(const std::string filename, int period);

void simulateMeanReversion(const std::string filename, int period);


#endif // SIM_H
