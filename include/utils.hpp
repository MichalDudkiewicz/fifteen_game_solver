#ifndef FIFTEEN_GAME_SOLVER_UTILS_HPP
#define FIFTEEN_GAME_SOLVER_UTILS_HPP

#include <ostream>
#include <vector>
#include <list>
#include "operation.hpp"

namespace fifteen
{
    std::ostream &operator<<(std::ostream &os, const std::vector<Operation>& operations);

    std::ostream &operator<<(std::ostream &os, const std::list<Operation>& operations);
}

#endif //FIFTEEN_GAME_SOLVER_UTILS_HPP
