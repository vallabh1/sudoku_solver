#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "sudokusolver.cpp"

int main()
{
    sudokusolver S;
    S.solveSudoku();
    S.printsudoku();
}
