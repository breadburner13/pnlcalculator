#include "csv_parser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

Trade CSVParser::parseLine(const std::string& line) {
    std::stringstream ss(line);
    Trade trade;
    std::string field;

    // Parse comma-separated values
    std::getline(ss, field, ',');
    trade.timestamp = std::stoi(field);

    std::getline(ss, trade.symbol, ',');
    
    std::getline(ss, field, ',');
    trade.action = Trade::actionFromString(field);

    std::getline(ss, field, ',');
    trade.price = std::stoi(field);

    std::getline(ss, field, ',');
    trade.quantity = std::stoi(field);

    return trade;
}

std::vector<Trade> CSVParser::parseFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Cannot open file: " + filename);

    std::vector<Trade> trades;
    std::string line;

    std::getline(file, line);

    while (std::getline(file, line)) {
        if (!line.empty()) {
            trades.push_back(parseLine(line));
        }
    }
    return trades;
}