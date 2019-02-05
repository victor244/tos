#include <cstdlib>
#include <iostream>
#define size_x 6
#define size_y 5

using namespace std;

class disk
{
  private:
    //����
    //sizey + 1 = buffer
    int bead[size_y + 1][size_x];

    //�w�]10C����
    int demo[size_y + 1][size_x] = {{1, 4, 4, 3, 5, 5}, {1, 5, 5, 3, 4, 4}, {1, 2, 1, 3, 2, 3}, {4, 2, 1, 5, 2, 3}, {5, 2, 1, 4, 2, 3}, {0, 0, 0, 0, 0, 0}};

    //�ΥH�p�����combo���}�C
    int meetbead[size_y][size_x];

    // display string
    string beadBacisStyle[7] = {" ", "��", "��", "��", "��", "��", "?"};
    string beadBigStyle1[7] = {"      ", "  ����  ", "  ����  ", "����  ����", "  ����  ", "   ���� ", " ��  �� "};
    string beadBigStyle2[7] = {"      ", " �������� ", "�� ���� ��", "  ����  ", "������������", "  ����  ", "������������"};
    string beadBigStyle3[7] = {"      ", "������������", " �������� ", "����  ����", "  ����  ", "   ���� ", "  ����  "};

    //counter
    int i, j, k, x, y;
    int combo;
    bool meet;

  public:
    void Init();    //��l��
    void Play();    //�ξ�@���p��g��
    void Meet();    //�����P�w
    void Combo();   //combo�p��
    void Drop();    //�]�l�ۥѸ��U
    void Rand();    //�H���üƸ��] �ثe�W���O���Ҽ{���]
    void Display(); //�L�X�ثe���� �H��combo��
};
void disk::Init() //��l��
{
    //�Ȯɹw�]�ϥ�demo���� ���ӱN�i�H�]�w����
    for (j = 0; j < size_y + 1; j++)
        for (i = 0; i < size_x; i++)
            bead[j][i] = demo[j][i];

    //�M�ťΥH�p��������}�C
    for (j = 0; j < size_y; j++)
        for (i = 0; i < size_x; i++)
            meetbead[j][i] = 0;
    cout << "Init_complete" << endl;
    //���mcombo�p��
    combo = 0;
} //end Init
void disk::Play()
{
    Init(); //��l��
    Display();
    _sleep(1000);
    Meet(); //����
    Display();
    _sleep(1000);
    while (meet) //������
    {
        Drop(); //���]
        Display();
        _sleep(1000);
        Meet(); //����
    }
} //end Play
void disk::Meet()
{
    meet = 0;
    //��
    for (j = 0; j < size_y; j++)
        for (i = 0; i < size_x - 2; i++)
            if (bead[j][i] > 0)
                if (bead[j][i] == bead[j][i + 1] && bead[j][i] == bead[j][i + 2])
                {
                    meet = 1;
                    meetbead[j][i] = bead[j][i] - 6;
                    for (k = 0; k < size_x; k++)
                        if (meetbead[j][k + 1] < 0 || meetbead[j][k - 1] < 0)
                            if (bead[j][k] == bead[j][i])
                                meetbead[j][k] = bead[j][k] - 6;
                }
    //��
    for (i = 0; i < size_x; i++)
        for (j = 0; j < size_y - 2; j++)
            if (bead[j][i] > 0)
                if (bead[j][i] == bead[j + 1][i] && bead[j][i] == bead[j + 2][i])
                {
                    meet = 1;
                    meetbead[j][i] = bead[j][i] - 6;
                    for (k = 0; k < size_y; k++)
                        if (meetbead[k + 1][i] < 0 || meetbead[k - 1][i] < 0)
                            if (bead[k][i] == bead[j][i])
                                meetbead[k][i] = bead[k][i] - 6;
                }
    if (meet)
        Combo();
} //end Meet
void disk::Combo()
{
    for (j = 0; j < size_y; j++)
        for (i = 0; i < size_x; i++)
            if (meetbead[j][i] < 0)
            {
                combo++;
                meetbead[j][i] = combo;
                for (x = 0; x < size_x; x++)
                    for (y = 0; y < size_y; y++)
                        if (bead[y][x] == bead[j][i] && meetbead[y][x] < 0)
                        {
                            if (meetbead[y + 1][x] == combo)
                                meetbead[y][x] = combo;
                            if (meetbead[y - 1][x] == combo)
                                meetbead[y][x] = combo;
                            if (meetbead[y][x + 1] == combo)
                                meetbead[y][x] = combo;
                            if (meetbead[y][x - 1] == combo)
                                meetbead[y][x] = combo;
                        }
            }
    for (j = 0; j < size_y; j++)
        for (i = 0; i < size_x; i++)
            if (meetbead[j][i] != 0)
            {
                bead[j][i] = -1;
                meetbead[j][i] = 0;
            }
}
void disk::Drop() //complete
{
    for (i = 0; i < size_x; i++)
        for (j = 0; j < size_y; j++)
            if (bead[j][i] == -1)
            {
                for (k = j; k < 5; k++)
                {
                    bead[k][i] = bead[k + 1][i];
                    Rand();
                }
                j = -1; //�]���|j++ �ҥH�n�q�Y�}�l�ݥ�-1
            }
}
void disk::Rand()
{
    bead[5][i] = 0;
    //temporarily unavailable
}
void disk::Display()
{
    cout << "\tCombo:" << combo << endl;
    /*for (j = size_y - 1; j >= 0; j--)
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
    }*/
    for (j = size_y - 1; j >= 0; j--)
    {
        for (i = 0; i < size_x; i++)
        {
            if (bead[j][i] == -1)
                cout << " ";
            else
                cout << beadBacisStyle[bead[j][i]];
            cout << ' ';
        }
        cout << endl;
    }
    //----------------------BigStyle----------------------
    /*for (j = size_y - 1; j >= 0; j--)
    {
        for (k = 0; k < 3; k++)
            switch (k)
            {
            case 0:
                for (i = 0; i < size_x; i++)
                {
                    if (bead[j][i] == -1)
                        cout << "      ";
                    else
                        cout << beadBigStyle1[bead[j][i]];
                    cout << ' ';
                }
                cout << endl;
                break;
            case 1:
                for (i = 0; i < size_x; i++)
                {
                    if (bead[j][i] == -1)
                        cout << "      ";
                    else
                        cout << beadBigStyle2[bead[j][i]];
                    cout << ' ';
                }
                cout << endl;
                break;
            case 2:
                for (i = 0; i < size_x; i++)
                {
                    if (bead[j][i] == -1)
                        cout << "      ";
                    else
                        cout << beadBigStyle3[bead[j][i]];
                    cout << ' ';
                }
                cout << endl;
                break;
            }
        cout << endl;
    }*/
}
int main()
{
    int userIn = 1;
    while (userIn)
    {
        disk d;
        d.Play();
        cout << "\nFinal";
        d.Display();
        userIn = 0;
    }
}