#pragma once 

#include <string> 

enum class TradeAction {BUY, SELL};

struct Trade {
    int timestamp;
    std::string symbol;
    TradeAction action;
    double price;
    int quantity;

    static TradeAction actionFromString(const std::string& actionStr);
    static char actionToChar(TradeAction action);
};