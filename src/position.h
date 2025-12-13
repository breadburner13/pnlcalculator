#pragma once

#include "trade.h"
#include <string>
#include <vector>

class Position {
public:
    Position(const std::string& symbol);
    void addTrade(const Trade& trade);
    int getNetPos() const;
    std::string getSymbol() const;
    const std::vector<Trade>& getTrades() const;

private:
    std::string symbol_;
    std::vector<Trade> trades_;
    int netPosition_ = 0;
}