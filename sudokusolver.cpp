#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;
class sudokusolver
{
    int sgrid[9][9];
    bitset<9> elementstopleft;
    bitset<9> elementstopcenter;
    bitset<9> elementstopright;
    bitset<9> elementsmidleft;
    bitset<9> elementsmidcenter;
    bitset<9> elementsmidright;
    bitset<9> elementslowleft;
    bitset<9> elementslowcenter;
    bitset<9> elementslowright;
    vector<bitset<9>> rows;
    vector<bitset<9>> columns;
};