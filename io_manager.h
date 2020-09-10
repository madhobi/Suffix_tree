#ifndef IO_MANAGER_H
#define IO_MANAGER_H

#include <vector>
using namespace std;

class io_manager
{
public:

    string alphabet;
    string seq;
    string seqName;
    string seqLength;
    
    io_manager();    
    vector <string> sequnece_name;
    vector <string> sequences;

    void readSrting(string fileName);
    void readAlphabet(string fileName);
};


#endif // IO_MANAGER_H
