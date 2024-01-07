#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <cstdint>
#include <cstring>

#include <map>

using namespace std;
class sudokusolver
{
public:
    char board[9][9];

public:
    sudokusolver()
    {
        std::string row;
        std::ifstream ingrid("unsolved.txt");
        int j = 0;
        while (getline(ingrid, row))
        {

            for (int i = 0; i < 9; i++)
            {
                board[j][i] = row[i];
            }
            j++;
        }
    }

    void solveSudoku()
    {
        solve(0, 0);
    }

    bool validis(int i, int j, char a)
    {
        for (int x = 0; x < 9; ++x)
        {
            if (board[i][x] == a || board[x][j] == a)
                return false;
        }

        for (int r = (i / 3) * 3; r < (i / 3) * 3 + 3; ++r)
        {
            for (int c = (j / 3) * 3; c < (j / 3) * 3 + 3; ++c)
            {
                if (board[r][c] == a)
                    return false;
            }
        }

        return true;
    }
    bool solve(int x, int y)
    {
        if (x == 9)
            return true;
        if (board[x][y] != '0')
        {
            return solve(x + ((y + 1) / 9), (y + 1) % 9);
        }
        for (int i = 49; i <= 57; i++)
        {
            if (validis(x, y, char(i)))
            {
                board[x][y] = char(i);
                if (solve(x + ((y + 1) / 9), (y + 1) % 9))
                {
                    return true;
                }
            }
        }

        board[x][y] = '0';
        return false;
    }
    void printsudoku()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                cout << board[i][j];
            }
            cout << endl;
        }
    }
};