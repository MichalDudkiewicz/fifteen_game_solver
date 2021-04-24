#include "blind_solver.hpp"

#include <utility>

namespace fifteen
{
    BlindSolver::BlindSolver(std::vector<Operation> operationOrder)
    : mOperationOrder(std::move(operationOrder))
    {

    }
}