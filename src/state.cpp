#include "state.hpp"
#include "operation.hpp"

namespace fifteen
{
    State::ZeroPosition findZero(const std::vector<std::vector<u_int8_t>>& gameBoard)
    {
        for (int i = 0; i<gameBoard.size(); i++)
        {
            for (int j = 0; j<gameBoard[i].size(); j++)
            {
                if (gameBoard[i][j] == 0)
                {
                    return {i, j};
                }
            }
        }
        throw std::runtime_error("no zero on the board!");
    }

    State::State(const FifteenTable& fifteenTable, const ZeroPosition& zeroPosition) : mFifteenTable(fifteenTable), mZeroPosition(zeroPosition) {
    }

    const State::FifteenTable &State::fifteenTable() const {
        return mFifteenTable;
    }

    const State::ZeroPosition &State::zeroPosition() const {
        return mZeroPosition;
    }

    bool State::operator==(const State &otherState) const {
        unsigned int rowIndex = 0;
        const auto& otherTable = otherState.fifteenTable();
        for (const auto& row : mFifteenTable)
        {
            const auto& otherRow = otherTable[rowIndex];
            if(!std::equal(row.begin(), row.end(), otherRow.begin()))
            {
                return false;
            }
            rowIndex++;
        }
        return true;
    }

    bool State::operator!=(const State &otherState) const {
        return !operator==(otherState);
    }

    State::State(const std::vector<std::vector<u_int8_t>>& gameBoard) {
        mZeroPosition = findZero(gameBoard);
        mFifteenTable = gameBoard;
    }
}

