CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -pthread
TARGET = StockSimulator
SRC = src/StockSimulator.cc src/SimBuyHold.cc src/SimBuyDip.cc \
      src/SimROC.cc src/SimEMA.cc src/SimMeanReversion.cc \
      src/Printer.cc src/Sim.cc src/WebscraperRunner.cc \
      src/main.cc

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

.PHONY: all clean
