#include "position.h"

Position::Position(const std::string& symbol) :symbol_(symbol) {}

void Position::addTrade(const Trade& trade) {
    if (trade.symbol != symbol_) {
        throw std::runtime_error("Trade symbol doesn't match position symbol");
    }

    trades_.push_back(trade);
    if (trade.action == TradeAction::BUY) {
        netPosition_ += trade.quantity;
    } else {
        netPosition_ -= trade.quantity;
    }
}

int Position::getNetPos() const {
    return netPosition_;
}

std::string Position::getSymbol() const {
    return symbol_;
}

const std::vector<Trade>& Position::getTrades() const {
    return trades_;
}