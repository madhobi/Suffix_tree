#include "Node.h"

Node::Node(int NodeID, bool isLeaf, int depth, string alp, int edgeLabelStart, int edgeLabelEnd)
{
    alphabet = alp;
    children.resize(alphabet.length());    
    this->NodeID = NodeID;//node ID, increasing every time a node is created
    this->isLeaf = isLeaf;//if the internal node is a leaf or not
    this->depth = depth;//depth of the node from root(number of characters from root to the node)
    suffixLink = NULL;
    this->edgeLabelStart = edgeLabelStart;
    this->edgeLabelEnd = edgeLabelEnd;
}
