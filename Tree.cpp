#include "Tree.h"

Tree::Tree(string sequ, string alph)
{
    str = sequ;
    alphabet = alph;
    cout << "str length: " << str.length() << " and alphabet length: " << alphabet.length() << endl;
    no_of_comparison=0;
    currentNodeID = sequ.length()+1;
    root = new Node(currentNodeID++, false, 0, alphabet, 0, 0);
    root->parent = root;
    root->suffixLink = root;
    lastInserted = root;
    deepestInternalDepth = 0;
    deepestInternal = NULL;
    lastSuffixNum = 0;
}

//Create a suffixtree function to insert suffixes
void Tree::createST()
{
    for (size_t i = 0; i <str.length(); i++)
    {
        lastSuffixNum = i;
        insert(i);//inserts ith suffix (index i in the string, starting from 0)

    }

}

//Insert suffixes
void Tree::insert(int suffixNum)
{
    if(lastInserted->parent->suffixLink != NULL)
    {
        caseI(suffixNum);
    }
    else if(lastInserted->parent->parent == root)
    {
        caseIIB(suffixNum);
    }
    else
    {
        caseIIA(suffixNum);
    }
}

//parents suffixLink is known
void Tree::caseI(int suffixNum)
{
    Node* u = lastInserted->parent;
    Node* v = u->suffixLink;
    lastInserted = FindPath(v, suffixNum+v->depth);
}

// grand_parent is not root
void Tree::caseIIA(int suffixNum)
{
    Node* u = lastInserted->parent;
    Node* u_prime = lastInserted->parent->parent;
    Node* v_prime = u_prime->suffixLink;
    int BetaPrime = u->depth - u_prime->depth;
    Node* v = NodeHop(v_prime, v_prime->depth+suffixNum, BetaPrime);
    u->suffixLink = v;
    FindPath(v, suffixNum+v->depth);
}

// grand_parent is root
void Tree::caseIIB(int suffixNum)
{
    Node* u = lastInserted->parent;
    Node* u_prime = lastInserted->parent->parent;  // u_prime is the root
    Node* v_prime = u_prime->suffixLink;           // v_prime is also root 
    int BetaPrime = u->depth - u_prime->depth-1;
    Node* v = NodeHop(v_prime, suffixNum, BetaPrime);
    u->suffixLink = v;
    FindPath(v, suffixNum+v->depth);
}

Node* Tree::NodeHop(Node* v_prime, int startIndex, int BetaPrime)
{
    if(BetaPrime <= 0)
    {
        return v_prime;
    }

    int c = get_alphabet_index(startIndex);
    int childEdgeLabelLength=0;
    if(v_prime->children[c] != NULL)
    {
        childEdgeLabelLength = v_prime->children[c]->edgeLabelEnd - v_prime->children[c]->edgeLabelStart+1;
    }

    if(BetaPrime == childEdgeLabelLength)
    {
        return v_prime->children[c];
    }
    else if(BetaPrime > childEdgeLabelLength) // need to nodehop again
    {
        BetaPrime = BetaPrime - childEdgeLabelLength;
        startIndex = startIndex + childEdgeLabelLength;
        NodeHop(v_prime->children[c], startIndex, BetaPrime);
    }
    else    // when BetaPrime < childEdgeLabelLength then there is to insert an internal nodeDepth
    {
        Node* prevNode = v_prime->children[c];
        Node* internal = new Node(currentNodeID++, false, v_prime->depth+BetaPrime, alphabet, v_prime->children[c]->edgeLabelStart, v_prime->children[c]->edgeLabelStart+BetaPrime-1 );

        v_prime->children[c] = internal;
        internal->parent = v_prime;
        c = get_alphabet_index(internal->edgeLabelStart+BetaPrime);
        internal->children[c] = prevNode;
        prevNode->parent = internal;
        prevNode->edgeLabelStart = internal->edgeLabelStart+BetaPrime;
        return internal;
    }
}

Node* Tree::FindPath(Node *u, int startIndex)
{
    Node* newLeafNode;
    int c = get_alphabet_index(startIndex);
    if(u->children[c] == NULL)
    {
        newLeafNode = createNewLeaf(u, startIndex, c);
        return newLeafNode;
    }
    else
    {
        Node *current = u->children[c];
        int suffixIndex = startIndex;
        int edgeLabelIndex = current->edgeLabelStart;
        int numberOfMatch = 0;

        while(str[suffixIndex] == str[edgeLabelIndex])
        {
            suffixIndex++;
            edgeLabelIndex++;
            numberOfMatch++;
            no_of_comparison++;
            if(edgeLabelIndex > current->edgeLabelEnd) //the edge is exausted, take child branch for further comparison
            {
                break;
            }
        }
        if(edgeLabelIndex > current->edgeLabelEnd) //the edge is exausted, take child branch for further comparison
        {
            u = current;
            FindPath(u, suffixIndex);
        }
        else
        {
            int nodeDepth = u->depth+numberOfMatch;
            Node *internal = new Node(currentNodeID++, false, nodeDepth, alphabet, current->edgeLabelStart, current->edgeLabelStart+numberOfMatch-1);

            internal->parent = u;
            u->children[c] = internal;
            c = get_alphabet_index(edgeLabelIndex);
            internal->children[c] = current;
            current->parent = internal;
            current->edgeLabelStart = edgeLabelIndex;
            //add the mismatched portion as a leafnode of the internal node
            c = get_alphabet_index(suffixIndex);
            newLeafNode = createNewLeaf(internal, suffixIndex, c);

            return newLeafNode;;
        }
    }
}


Node* Tree::createNewLeaf(Node* parent, int suffixNum, int parentIndex)
{
    leafDepth = parent->depth+str.length() - suffixNum;
    Node* newLeaf = new Node(lastSuffixNum, true, leafDepth, alphabet, suffixNum, str.length()-1);
    lastInserted = newLeaf;
    newLeaf->parent = parent;
    //parent->startIndex[parentIndex] = suffixNum + parent->depth;
    parent->children[parentIndex] = newLeaf;
    return newLeaf;
}


//finds the alphabet index for the character
int Tree::get_alphabet_index(int startIndex)
{
    int index = 0;
    for (size_t i = 0; i < alphabet.length(); i++)
    {
      if (alphabet[i] == str[startIndex])
      {
        index = i;
        break;
      }
    }
    return index;
}

void Tree::getBWTIndex()
{

    dfsBWTIndex(root);
    ofstream BWTFileOut;
    BWTFileOut.open("BWT.txt", ios::out);
    for (size_t i = 0; i < BWT.size(); i++)
    {
      BWTFileOut<< BWT[i] << endl;
    }
    BWTFileOut.close();
}

void Tree::dfsBWTIndex(Node* node)
{
    for (int i=0; i< alphabet.length();i++)
    {
        if(node->children[i]!=NULL)
        {
            dfsBWTIndex(node->children[i]);
        }
    }
    if(node->isLeaf)
    {
        if(node->NodeID==0)
        {
            BWT.push_back('$');
        }
        else
        {
            BWT.push_back(str[node->NodeID-1]);
        }
    }
}

void Tree::longestExactMatch()
{
    findingDeepestNode(root); // will save the deepest node in deepestInternal
    cout << "Longest repeating substringlength: " << deepestInternal->depth << endl;
    vector<int> exactMatchStartIndex;
    for(int i=0; i<alphabet.length(); i++)
    {
        if(deepestInternal->children[i]!=NULL)
        {
            int longestRepeatStringIndex = deepestInternal->children[i]->edgeLabelStart-deepestInternal->depth;
            exactMatchStartIndex.push_back(longestRepeatStringIndex);
        }
    }
    cout << "Longest repeat start index:";
    for (int i = 0; i < exactMatchStartIndex.size(); i++)
    {
        cout << " " << exactMatchStartIndex[i];
    }
    cout << endl;
}

void Tree::findingDeepestNode(Node* node)
{
    for (int i=0; i< alphabet.length();i++)
    {
        if(node->children[i]!=NULL && node->children[i]->isLeaf!=true)
        {
            if(node->children[i]->depth > deepestInternalDepth)
            {
                deepestInternalDepth = node->children[i]->depth;
                deepestInternal = node->children[i];
            }
            findingDeepestNode(node->children[i]);
        }
    }
}
