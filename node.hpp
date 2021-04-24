#ifndef FIFTEEN_GAME_SOLVER_NODE_HPP
#define FIFTEEN_GAME_SOLVER_NODE_HPP

#include <memory>
#include <optional>
#include "operation.hpp"
#include "state.hpp"
#include <list>
#include <functional>
#include <boost/functional/hash/hash.hpp>

namespace fifteen
{
class Node : public std::enable_shared_from_this<Node> {
    public:
        Node(const std::shared_ptr<Node>& parentNode, Operation operationOnParent);

        Node(std::shared_ptr<State> initialState);

        const std::shared_ptr<State>& state() const;

        unsigned int pathCost() const;

        std::list<std::shared_ptr<Node>> neighbours(const std::vector<Operation>& operationOrder);

        bool operator==(const Node& otherNode) const;

    private:
        std::shared_ptr<Node> mParentNode;
        std::optional<Operation> mOperationOnParent;
        std::shared_ptr<State> mState;
        unsigned int mPathCost;
    };

    struct NodeHash {
        size_t operator()(const Node& node) const
        {
            const auto& gameBoard = node.state()->fifteenTable();
            std::size_t seed = 0;
            for (const auto& row : gameBoard)
            {
                boost::hash_combine(seed, row);
            }
            return seed;
        }
    };
}

#endif //FIFTEEN_GAME_SOLVER_NODE_HPP
