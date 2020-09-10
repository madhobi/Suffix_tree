#ifndef NODE_H
#define NODE_H

#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

class Node
{
    public:
    int NodeID, depth;    
    int edgeLabelStart, edgeLabelEnd;
    vector <Node*> children;
    bool isLeaf;
    Node* parent;
    Node* suffixLink;
    string alphabet;

    Node(int NodeID, bool isLeaf, int depth, string alp, int edgeLabelStart, int edgeLabelEnd);
};


#endif // NODE_H
