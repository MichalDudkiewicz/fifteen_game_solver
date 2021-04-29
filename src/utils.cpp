#include "utils.hpp"
#include <ostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>

namespace fifteen
{
    std::ostream &operator<<(std::ostream &os, const std::vector<Operation>& operations)
    {
        std::ostringstream buffer;
        for (const auto& operation : operations)
        {
            buffer << operation;
        }
        std::string operationsString = buffer.str();
        std::transform(operationsString.begin(), operationsString.end(), operationsString.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        os << operationsString;
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const std::list<Operation>& operations)
    {
        for (const auto& operation : operations)
        {
            os << operation;
        }
        return os;
    }
}