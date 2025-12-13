#include "trade.h"
#include <stdexcept>

TradeAction Trade::actionFromString(const std::string& actionStr) {
    if (actionStr == "B") {
        return TradeAction::BUY;
    } else if (actionStr == "S") {
        return TradeAction::SELL;
    }
    throw std::invalid_argument("Invalid trade action: " + actionStr);
}

char Trade::actionToChar(TradeAction action) {
    return (action == TradeAction::BUY) ? 'B' : 'S';
}