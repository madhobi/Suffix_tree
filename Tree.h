#ifndef TREE_H
#define TREE_H

#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
#include "Node.h"
#include <cstdlib>
using namespace std;

class Tree
{
    public:
        int leafDepth;
        int currentNodeID;
        string alphabet, str, name;
        vector<string> reads; // storing read sequences
        Node* lastInserted;//stores the last inserted node to know the suffix links and which case to follow
        Node* root;
        int deepestInternalDepth;
        Node* deepestInternal;
        Node* lastLeaf;
        int lastSuffixNum;
        int no_of_comparison;
        vector<char> BWT;//BWT ARRAY
        //vector<int> suffixVector;//array of suffixes of the tree
        //vector<Node*> leafNodesVector;

        Tree(string sequ, string alph);
        void createST(); //Create a suffixtree function to insert suffixes
        Node* FindPath(Node *u, int startIndex);
        void insert(int suffixNum); // insert suffixes
        void caseI(int suffixNum);
        void caseIIA(int suffixNum);
        void caseIIB(int suffixNum);
        Node* createNewLeaf(Node* current, int suffixNum, int parentIndex);
        int get_alphabet_index(int startIndex); //finds the alphabet index for the character
        void findingDeepestNode(Node* node);
        void longestExactMatch();
        void getBWTIndex();
        void dfsBWTIndex(Node* node);
        Node* NodeHop(Node* v_prime, int startIndex, int BetaPrime);

};


#endif // TREE_H
