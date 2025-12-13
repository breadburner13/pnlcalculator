#include "position.h"
#include <stdexcept>

Position::Position(const std::string& symbol) : symbol_(symbol) {}

double Position::processTrade(const Trade& trade, bool useFIFO) {
    if (trade.symbol != symbol_) {
        throw std::runtime_error("Trade symbol doesn't match position");
    }
    
    return useFIFO ? processFIFO(trade) : processLIFO(trade);
}

double Position::processFIFO(const Trade& trade) {
    double pnl = 0.0;
    int remaining = trade.quantity;
    
    if (trade.action == TradeAction::BUY) {
        fifoQueue_.push({trade.quantity, trade.price});
        netPosition_ += trade.quantity;
        return 0.0;
    }
    
    // SELL logic
    while (remaining > 0 && !fifoQueue_.empty()) {
        PositionLot& front = fifoQueue_.front();
        int matched = std::min(remaining, front.quantity);
        
        pnl += matched * (trade.price - front.price);
        remaining -= matched;
        front.quantity -= matched;
        
        if (front.quantity == 0) {
            fifoQueue_.pop();
        }
    }
    
    netPosition_ -= trade.quantity;
    return pnl;
}

double Position::processLIFO(const Trade& trade) {
    double pnl = 0.0;
    int remaining = trade.quantity;
    
    if (trade.action == TradeAction::BUY) {
        lifoStack_.push({trade.quantity, trade.price});
        netPosition_ += trade.quantity;
        return 0.0;
    }
    
    // SELL logic
    while (remaining > 0 && !lifoStack_.empty()) {
        PositionLot& top = lifoStack_.top();
        int matched = std::min(remaining, top.quantity);
        
        pnl += matched * (trade.price - top.price);
        remaining -= matched;
        top.quantity -= matched;
        
        if (top.quantity == 0) {
            lifoStack_.pop();
        }
    }
    
    netPosition_ -= trade.quantity;
    return pnl;
}

bool Position::isFlat() const {
    return netPosition_ == 0;
}