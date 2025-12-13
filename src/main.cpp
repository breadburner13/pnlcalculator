#include <iostream>
#include <iomanip>
#include "csv_parser.h"
#include "pnl_calculator.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <trades.csv> <fifo|lifo>" << std::endl;
        return 1;
    }
    
    std::string filename = argv[1];
    std::string method = argv[2];
    
    bool useFIFO;
    if (method == "fifo") {
        useFIFO = true;
    } else if (method == "lifo") {
        useFIFO = false;
    } else {
        std::cerr << "Error: Accounting method must be 'fifo' or 'lifo'" << std::endl;
        return 1;
    }
    
    try {
        // Parse trades
        auto trades = CSVParser::parseFile(filename);
        
        // Calculate PnL
        PnLCalculator calculator;
        auto events = calculator.calculate(trades, useFIFO);
        
        // Output header
        std::cout << "TIMESTAMP,SYMBOL,PNL" << std::endl;
        
        // Output PnL events
        for (const auto& event : events) {
            std::cout << event.timestamp << ","
                      << event.symbol << ","
                      << std::fixed << std::setprecision(2) << event.pnl << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}