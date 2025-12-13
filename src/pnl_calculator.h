#pragma once

#include "trade.h"
#include "position.h"
#include <vector>
#include <unordered_map>

struct PnLEvent {
    int timestamp;
    std::string symbol;
    double pnl;
};

class PnLCalculator {
public:
    std::vector<PnLEvent> calculate(const std::vector<Trade>& trades, bool useFIFO);
    
private:
    std::unordered_map<std::string, Position> positions_;
};