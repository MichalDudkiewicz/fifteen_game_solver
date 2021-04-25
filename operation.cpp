#include <stdexcept>
#include <optional>
#include "operation.hpp"
#include "state.hpp"
#include <ostream>

namespace fifteen
{
    std::vector<std::vector<uint8_t>> updateFifteenTable(const std::vector<std::vector<uint8_t>>& parentFifteenTable, std::pair<uint8_t, uint8_t> parentZeroPosition, std::pair<uint8_t, uint8_t> newZeroPosition)
    {
        const uint8_t valueToSwapWithBuffer = parentFifteenTable[newZeroPosition.first][newZeroPosition.second];
        std::vector<std::vector<uint8_t>> fifteenTable = parentFifteenTable;
        fifteenTable[parentZeroPosition.first][parentZeroPosition.second] = valueToSwapWithBuffer;
        fifteenTable[newZeroPosition.first][newZeroPosition.second] = 0;
        return fifteenTable;
    }

    std::optional<State> updateState(const std::shared_ptr<fifteen::State> &parentState, fifteen::Operation operationOnParent)
    {
        const auto parentZeroPosition = parentState->zeroPosition();
        const auto parentFifteenTable = parentState->fifteenTable();
        const unsigned int maxRowIndex = parentFifteenTable.size() - 1;
        const unsigned int maxColumnIndex = parentFifteenTable.front().size() - 1;

        std::pair<uint8_t, uint8_t> newZeroPosition;
        std::vector<std::vector<uint8_t>> fifteenTable;
        switch(operationOnParent) {
            case Operation::UP:
                if (parentZeroPosition.first > 0)
                {
                    newZeroPosition = {parentZeroPosition.first - 1, parentZeroPosition.second };
                    fifteenTable = updateFifteenTable(parentFifteenTable, parentZeroPosition, newZeroPosition);
                    const State updatedState = {fifteenTable, newZeroPosition};
                    return updatedState;
                }
                break;
            case Operation::RIGHT:
                if (parentZeroPosition.second < maxColumnIndex)
                {
                    newZeroPosition = {parentZeroPosition.first, parentZeroPosition.second + 1 };
                    fifteenTable = updateFifteenTable(parentFifteenTable, parentZeroPosition, newZeroPosition);
                    const State updatedState = {fifteenTable, newZeroPosition};
                    return updatedState;
                }
                break;
            case Operation::DOWN:
                if (parentZeroPosition.first < maxRowIndex)
                {
                    newZeroPosition = {parentZeroPosition.first + 1, parentZeroPosition.second};
                    fifteenTable = updateFifteenTable(parentFifteenTable, parentZeroPosition, newZeroPosition);
                    const State updatedState = {fifteenTable, newZeroPosition};
                    return updatedState;
                }
                break;
            case Operation::LEFT:
                if (parentZeroPosition.second > 0)
                {
                    newZeroPosition = {parentZeroPosition.first, parentZeroPosition.second - 1 };
                    fifteenTable = updateFifteenTable(parentFifteenTable, parentZeroPosition, newZeroPosition);
                    const State updatedState = {fifteenTable, newZeroPosition};
                    return updatedState;
                }
                break;
            default:
                return {};
        };
        return {};
    }

    std::ostream& operator<<(std::ostream& os, fifteen::Operation operation)
    {
        switch(operation) {
            case Operation::UP:
                os << 'U';
                break;
            case Operation::RIGHT:
                os << 'R';
                break;
            case Operation::DOWN:
                os << 'D';
                break;
            case Operation::LEFT:
                os << 'L';
                break;
        }
        return os;
    }
}

