#ifndef FIFTEEN_GAME_SOLVER_OPERATION_HPP
#define FIFTEEN_GAME_SOLVER_OPERATION_HPP

#include <vector>
#include <memory>
#include <optional>

namespace fifteen {
    class State;

    enum class Operation {
        UP, RIGHT, DOWN, LEFT
    };

    std::optional<State> updateState(const std::shared_ptr<fifteen::State> &parentState, fifteen::Operation operationOnParent);
}

#endif //FIFTEEN_GAME_SOLVER_OPERATION_HPP
