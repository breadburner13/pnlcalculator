#pragma once

#include "trade.h"
#include <string>
#include <queue>
#include <stack>
#include <vector>

struct PositionLot {
    int quantity;
    double price;
};

class Position {
public:
    Position(const std::string& symbol);
    
    double processTrade(const Trade& trade, bool useFIFO);
    
    bool isFlat() const;
    
private:
    std::string symbol_;
    std::queue<PositionLot> fifoQueue_;
    std::stack<PositionLot> lifoStack_;
    int netPosition_ = 0;
    
    double processFIFO(const Trade& trade);
    double processLIFO(const Trade& trade);
};