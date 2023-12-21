#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <map>

using namespace std;
class sudokusolver
{
public:
    int sgrid[9][9];
    bitset<10> elementstopleft;
    bitset<10> elementstopcenter;
    bitset<10> elementstopright;
    bitset<10> elementsmidleft;
    bitset<10> elementsmidcenter;
    bitset<10> elementsmidright;
    bitset<10> elementslowleft;
    bitset<10> elementslowcenter;
    bitset<10> elementslowright;
    vector<bitset<10>> rows;
    vector<bitset<10>> columns;
    map<pair<int, int>, bitset<10>> setmap;

    sudokusolver()
    {
        elementstopleft.reset();
        elementstopcenter.reset();
        elementstopright.reset();
        elementsmidleft.reset();
        elementsmidcenter.reset();
        elementsmidright.reset();
        elementslowleft.reset();
        elementslowcenter.reset();
        elementslowright.reset();

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
        for (int a = 0; a < 3; a++)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int k = 0; k < 3; k++)
                {
                    for (int l = 0; l < 3; l++)
                    {
                        int var = sgrid[3 * a + k][3 * i + l];
                        if (a == 0 && i == 0)
                        {
                            elementstopleft[var] = 1;
                            setmap[make_pair(a * 3, i * 3)] = elementstopleft;
                        }
                        if (a == 0 && i == 1)
                        {
                            elementstopcenter[var] = 1;
                            setmap[make_pair(a * 3, i * 3)] = elementstopcenter;
                        }
                        if (a == 0 && i == 2)
                        {
                            elementstopright[var] = 1;
                            setmap[make_pair(a * 3, i * 3)] = elementstopright;
                        }
                        if (a == 1 && i == 0)
                        {
                            elementsmidleft[var] = 1;
                            setmap[make_pair(a * 3, i * 3)] = elementsmidleft;
                        }
                        if (a == 1 && i == 1)
                        {
                            elementsmidcenter[var] = 1;
                            setmap[make_pair(a * 3, i * 3)] = elementsmidcenter;
                        }
                        if (a == 1 && i == 2)
                        {
                            elementsmidright[var] = 1;
                            setmap[make_pair(a * 3, i * 3)] = elementsmidright;
                        }
                        if (a == 2 && i == 0)
                        {
                            elementslowleft[var] = 1;
                            setmap[make_pair(a * 3, i * 3)] = elementslowleft;
                        }
                        if (a == 2 && i == 1)
                        {
                            elementslowcenter[var] = 1;
                            setmap[make_pair(a * 3, i * 3)] = elementslowcenter;
                        }
                        if (a == 2 && i == 2)
                        {
                            elementslowright[var] = 1;
                            setmap[make_pair(a * 3, i * 3)] = elementslowright;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < 9; i++)
        {
            bitset<10> tempr;
            tempr.reset();
            bitset<10> tempc;
            tempc.reset();
            for (int l = 0; l < 9; l++)
            {
                int varc = sgrid[l][i];
                int varr = sgrid[i][l];
                tempr[varr] = 1;
                tempc[varc] = 1;
            }
            rows.push_back(tempr);
            columns.push_back(tempc);
        }
    }

    bool solved()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (sgrid[i][j] == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }

    void solvesudoku()
    {
        while (!solved())
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    checksquare(i * 3, 3 * j);
                }
            }
        }
    }

    void checksquare(int r, int c)
    {
        for (int i = 1; i < 10; i++)
        {
            bitset<10> temp = (setmap[make_pair(3 * r, 3 * c)]);
            if (temp[i] == 1)
            {
                continue;
            }
            vector<pair<int, int>> possible;
            for (int j = r; j < r + 3; j++)
            {
                for (int k = c; k < c + 3; k++)
                {
                    if (sgrid[j][k] == 0 && rows[j][i] == 0 && columns[k][i] == 0)
                    {
                        possible.push_back(make_pair(j, k));
                        searchrow(j);
                        searchcolumn(k);
                    }
                }
            }

            if ((int)(possible.size()) == 1)
            {
                if (sgrid[possible[0].first][possible[0].second] == 0)
                {
                    sgrid[possible[0].first][possible[0].second] = i;
                    cout << "done!";
                    setmap[make_pair(3 * r, 3 * c)][i] = 1;
                    rows[possible[0].first][i] = 1;
                    columns[possible[0].second][i] = 1;
                }
            }
        }
    }

    void searchrow(int r)
    {
        for (int i = 1; i < 10; i++)
        {
            bitset<10> t = rows[r];
            if (t[i] == 1)
            {
                continue;
            }
            vector<pair<int, int>> possible;
            for (int j = 0; j < 9; j++)
            {
                if (sgrid[r][j] == 0 && columns[j][i] == 0 && setmap[make_pair(r / 3, j / 3)][i] == 0)
                {
                    possible.push_back(make_pair(r, j));
                }
            }
            if ((int)possible.size() == 1)
            {
                sgrid[possible[0].first][possible[0].second] = i;
                rows[r][i] = 1;
                cout << "done!";
                columns[possible[0].second][i] = 1;
                setmap[make_pair((possible[0].first) / 3, (possible[0].second) / 3)][i] = 1;
            }
        }
    }

    void searchcolumn(int c)
    {
        for (int i = 1; i < 10; i++)
        {
            bitset<10> t = columns[c];
            if (columns[c][i] == 1)
            {
                continue;
            }
            vector<pair<int, int>> possible;
            for (int j = 0; j < 9; j++)
            {
                if (sgrid[j][c] == 0 && rows[j][i] == 0 && setmap[make_pair(j / 3, c / 3)][i] == 0)
                {
                    possible.push_back(make_pair(j, c));
                }
            }
            if ((int)possible.size() == 1)
            {
                sgrid[possible[0].first][possible[0].second] = i;
                columns[c][i] = 1;
                cout << "done!";
                rows[possible[0].first][i] = 1;
                setmap[make_pair((possible[0].first) / 3, (possible[0].second) / 3)][i] = 1;
            }
        }
    }
    void printsudoku()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                cout << sgrid[i][j];
            }
            cout << endl;
        }
    }
};