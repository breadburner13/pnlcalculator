#pragma once

#include <vector>
#include <string>
#include "trade.h"

class CSVParser {
public:
    static std::vector<Trade> parseFile(const std::string& filename);
    static Trade parseLine(const std::string& line);
};