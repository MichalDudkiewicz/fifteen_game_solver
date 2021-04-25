#include "node.hpp"
#include "state.hpp"
#include <memory>
#include <utility>
#include "operation.hpp"

namespace fifteen
{
    Node::Node(const std::shared_ptr<Node> &parentNode, Operation operationOnParent)
    : mParentNode(parentNode),
    mOperationOnParent(operationOnParent)
    {
        mState = std::make_shared<State>(updateState(parentNode->state(), operationOnParent).value());
        mPathCost = parentNode->pathCost() + 1;
    }

    const std::shared_ptr<State>& Node::state() const {
        return mState;
    }

    unsigned int Node::pathCost() const {
        return mPathCost;
    }

    Node::Node(std::shared_ptr<State> initialState)
    : mParentNode(nullptr),
    mOperationOnParent(std::nullopt),
    mState(std::move(initialState)),
    mPathCost(0)
    {
    }

    std::list<std::shared_ptr<Node>> Node::neighbours(const std::vector<Operation> &operationOrder) {
        std::list<std::shared_ptr<Node>> listOfOrderedNeigbours;
        for (const auto& operation : operationOrder)
        {
            const auto newState = updateState(mState, operation);
            if (newState)
            {
                const auto newNode = std::make_shared<Node>(shared_from_this(), operation);
                listOfOrderedNeigbours.push_back(newNode);
            }
        }
        return listOfOrderedNeigbours;
    }

    bool Node::operator==(const Node &otherNode) const {
        return mState==otherNode.mState;
    }

    const std::shared_ptr<Node>& Node::parent() const {
        return mParentNode;
    }

    std::optional<Operation> Node::operationOnParent() const {
        return mOperationOnParent;
    }
}