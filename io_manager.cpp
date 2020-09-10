#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "io_manager.h"
using namespace std;

io_manager::io_manager(){}

void io_manager::readSrting(string fileName)
{
    seq = "";
    string line;
    ifstream infile(fileName.c_str());
    int split;
    getline(infile, line);
    if (line[0] == '>') {
      split = line.find_first_of(",");
      seqName = line.substr(0, split);
    }
    while (getline(infile, line) && line.length()>0)
    {
      seq += line;
    }

    seqLength = seq.length();
    infile.close();
}

void io_manager::readAlphabet(string fileName)
{
    string line;
    alphabet= "";
    ifstream infile(fileName.c_str());
    if (!infile.is_open())
    {
        cout << "it cannot open the file " << fileName;
        exit(1);
    }

    while (getline(infile, line))
    {
        alphabet += line;
    }

    alphabet.erase(remove(alphabet.begin(), alphabet.end(), ' '), alphabet.end());
    alphabet = '$' + alphabet;
    infile.close();


}

