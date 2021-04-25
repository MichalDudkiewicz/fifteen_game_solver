#ifndef FIFTEEN_GAME_SOLVER_OPERATION_HPP
#define FIFTEEN_GAME_SOLVER_OPERATION_HPP

#include <vector>
#include <memory>
#include <optional>

namespace fifteen {
    class State;

    enum class Operation : char {
        UP, RIGHT, DOWN, LEFT
    };

    std::ostream &operator<<(std::ostream &os, Operation operation);

    std::optional<State> updateState(const std::shared_ptr<fifteen::State> &parentState, fifteen::Operation operationOnParent);
}

#endif //FIFTEEN_GAME_SOLVER_OPERATION_HPP
