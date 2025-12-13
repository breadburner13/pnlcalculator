#include "pnl_calculator.h"

std::vector<PnLEvent> PnLCalculator::calculate(const std::vector<Trade>& trades, bool useFIFO) {
    std::vector<PnLEvent> events;
    
    for (const auto& trade : trades) {
        auto it = positions_.find(trade.symbol);
        if (it == positions_.end()) {
            it = positions_.emplace(trade.symbol, Position(trade.symbol)).first;
        }
        
        double pnl = it->second.processTrade(trade, useFIFO);
        
        if (pnl != 0.0) {
            events.push_back({trade.timestamp, trade.symbol, pnl});
        }
    }
    
    return events;
}