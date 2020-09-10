#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <sys/time.h>
#include <ctime>
#include "io_manager.h"
#include "Node.h"
#include "Tree.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
      cout << "Usage: <executable name>  <input file containing sequence s> <input alphabet file> \n";
      return (1);
    }
    io_manager im;
    im.readSrting(argv[1]);
    string sequence = im.seq+'$';

    im.readAlphabet(argv[2]);
    string alphabet = im.alphabet;

    double startTime, endTime;
    Tree *tree = new Tree(sequence, alphabet);
    startTime =clock();
    tree->createST();//create the suffix tree for the string and alphabet in the files which are passed in constructor
    endTime =clock();
    cout << "time for Construct suffix Tree: " << double(endTime-startTime)/double(CLOCKS_PER_SEC) << endl;
    tree->longestExactMatch();
    tree->getBWTIndex();

    return 0;
}
