#include <cstdlib>
#include <iostream>

#define size_x 6
#define size_y 5

using namespace std;

class disk
{
  private:
    int bead[size_x][size_y + 1] = {}; //sizey + 1 = buffer
    int meetbead[size_x][size_y] = {};
    int i, j, k, x, y; //counter

  public:
    int counter;
    bool meet;
    void Init();
    void Play();
    void Meet();
    void Combo();
    void Drop();
    void Rand();
    void Display();
};
void disk::Init()
{
    for (i = 0; i < size_x; i++)
        for (j = 0; j < size_y; j++)
            bead[i][j] = rand() % 5 + 1;
    //test
    bead[0][0] = 1;
    bead[0][1] = 1;
    bead[0][2] = 1;
    bead[2][0] = 5;
    cout << "\nInit";
    Display();
}
void disk::Meet()
{
    meet = 0;
    for (i = 0; i < size_x; i++)
        for (j = 0; j < size_y; j++)
            if (bead[i][j] > 0)
            {
                if (bead[i][j] == bead[i][j + 1] && bead[i][j] == bead[i][j - 1])
                {
                    meet = 1;
                    for (k = 0; k < size_y; k++)
                        if (bead[i][k] == bead[i][j])
                            meetbead[i][k] = bead[i][j] - 6;
                }
                if (bead[i][j] == bead[i + 1][j] && bead[i][j] == bead[i - 1][j])
                {
                    meet = 1;
                    for (k = 0; k < size_x; k++)
                        if (bead[k][j] == bead[i][j])
                            meetbead[k][j] = bead[i][j] - 6;
                }
            }
    cout << "\nMeet";
    Display();
    if (meet)
        Combo();
}
void disk::Combo()
{
    for (i = 0; i < size_x; i++)
        for (j = 0; j < size_y; j++)
            if (meetbead[i][j] < 0)
            {
                counter++;
                meetbead[i][j] = counter;
                for (x = 0; x < size_x; x++)
                    for (y = 0; y < size_y; y++)
                    {

                        if (bead[x][y] == bead[i][j] && meetbead[x][y] < 0)
                        {
                            if (meetbead[x + 1][y] == counter)
                                meetbead[x][y] = counter;
                            if (meetbead[x - 1][y] == counter)
                                meetbead[x][y] = counter;
                            if (meetbead[x][y + 1] == counter)
                                meetbead[x][y] = counter;
                            if (meetbead[x][y - 1] == counter)
                                meetbead[x][y] = counter;
                        }
                    }
                /*cout << "\nmeetbead";
                for (int x2 = 0; x2 < size_x; x2++) //display meetbead
                {
                    cout << endl;
                    for (int y2 = 0; y2 < size_y; y2++)
                        cout << meetbead[x2][y2];
                }*/
            }
    for (i = 0; i < size_x; i++)
        for (j = 0; j < size_y; j++)
            if (meetbead[i][j] != 0)
            {
                bead[i][j] = -1;
                meetbead[i][j] = 0;
            }
    cout << "\nCombo";
    Display();
}
void disk::Drop() //complete
{
    for (i = 0; i < size_x; i++)
        for (j = 0; j < size_y; j++)
            if (bead[i][j] == -1)
            {
                Rand();
                for (k = j; k < 5; k++)
                    bead[i][k] = bead[i][k + 1];
                j = -1; //因為會j++ 所以要從頭開始需先-1
            }
    cout << "\nDrop";
    Display();
}
void disk::Rand()
{
    bead[i][5] = 0;
    //temporarily unavailable
}
void disk::Display()
{
    cout << "\tCombe:" << counter << endl;
    for (j = size_y - 1; j >= 0; j--)
    {
        for (i = 0; i < size_x; i++)
            switch (bead[i][j])
            {
            case -1:
                cout << "*";
                break;
            case 0:
                cout << " ";
                break;
            default:
                cout << bead[i][j];
                break;
            }
        cout << endl;
    }
}
int main()
{
    int userIn = 1;
    while (userIn)
    {
        disk d;
        d.Init();
        d.counter = 0;
        d.Meet();
        while (d.meet)
        {
            d.Drop();
            d.Meet();
        }
        cout << "\nFinal";
        d.Display();
        userIn = 0;
    }
}