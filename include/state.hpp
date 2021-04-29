#ifndef FIFTEEN_GAME_SOLVER_STATE_HPP
#define FIFTEEN_GAME_SOLVER_STATE_HPP

#include <vector>
#include <memory>
#include <cstdint>
#include "type_defs.hpp"

namespace fifteen {
    enum class Operation : char;

    class State {
    using FifteenTable = std::vector<std::vector<uint8_t>>;

    public:
    using ZeroPosition = std::pair<uint8_t, uint8_t>;

    public:
        State(const FifteenTable& fifteenTable, const ZeroPosition& zeroPosition);

        State(const std::vector<std::vector<u_int8_t>>& gameBoard);

        const FifteenTable& fifteenTable() const;

        const ZeroPosition& zeroPosition() const;

        bool operator==(const State& otherState) const;

        bool operator!=(const State& otherState) const;

    private:
        FifteenTable mFifteenTable;
        ZeroPosition mZeroPosition;
    };
}

#endif //FIFTEEN_GAME_SOLVER_STATE_HPP
