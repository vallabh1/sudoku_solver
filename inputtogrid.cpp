#include <vector>
#include <iostream>
#include <fstream>
#include <string>

int main()
{
    int sgrid[9][9];
    std::string row;
    std::ifstream ingrid("unsolved.txt");
    int j = 0;
    while (getline(ingrid, row))
    {

        for (int i = 0; i < 9; i++)
        {
            sgrid[j][i] = (int)(row[i]) - 48;
        }
        j++;
    }
}
