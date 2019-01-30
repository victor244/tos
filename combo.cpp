#include <cstdlib>
#include <iostream>

#define size_x 6
#define size_y 5

using namespace std;

class disk
{
  private:
    //版面
    //sizey + 1 = buffer
    int bead[size_x][size_y + 1];

    //預設10C版面
    int demo[size_x][size_y + 1] = {{1,1,1,4,5,0},{4,5,2,2,2,0},{4,5,1,1,1,0},{3,3,3,5,4,0},{5,4,2,2,2,0},{5,4,3,3,3,0}};

    //用以計算消除combo的陣列
    int meetbead[size_x][size_y];

    //counter
    int i, j, k, x, y; 
    int combo;
    bool meet;

  public:
    void Init();//初始化
    void Play();//統整一次計算週期
    void Meet();//消除判定
    void Combo();//combo計算
    void Drop();//珠子自由落下
    void Rand();//隨機亂數落珠 目前規劃是不考慮落珠
    void Display();//印出目前版面 以及combo數
};
void disk::Init()//初始化
{
    //暫時預設使用demo版面 未來將可以設定版面
    for (i = 0; i < size_x; i++)
        for (j = 0; j < size_y + 1; j++)
            bead[i][j] = demo[i][j];

    //清空用以計算消除的陣列
    for (i = 0; i < size_x; i++)
        for (j = 0; j < size_y; j++)
            meetbead[i][j] = 0;

    //重置combo計數
    combo = 0;

    cout << "\nInit";
    Display();
}//end Init
void disk::Play()
{
    Init();//初始化
    Meet();//消除
    while (meet)//有消除
    {
        Drop();//落珠
        Meet();//消除
    }
}//end Play
void disk::Meet()
{
    meet = 0;
    //目前想到以下這種寫法 會存取到bead[-1][-1]到bead[6][6]的部分 邏輯上來說是不允許的 不過就先暫且放置
    //想到的解決辦法是拆分直向消除以及縱向消除 寫在兩個分開的雙重for內
    //並且 在消除的部分有邏輯錯誤 要在未來做修正
    for (i = 0; i < size_x; i++)
        for (j = 0; j < size_y; j++)
            if (bead[i][j] > 0)//等於0為空乏
            {
                if (bead[i][j] == bead[i][j + 1] && bead[i][j] == bead[i][j - 1])//若找到三連
                {
                    meet = 1;
                    for (k = 0; k < size_y; k++)//將此直排的同屬珠消除 邏輯錯誤 需要判斷是否相連
                        if (bead[i][k] == bead[i][j])
                            meetbead[i][k] = bead[i][j] - 6;
                }
                if (bead[i][j] == bead[i + 1][j] && bead[i][j] == bead[i - 1][j])
                {
                    meet = 1;
                    for (k = 0; k < size_x; k++)//將此直排的同屬珠消除 邏輯錯誤 需要判斷是否相連
                        if (bead[k][j] == bead[i][j])
                            meetbead[k][j] = bead[i][j] - 6;
                }
            }
    cout << "\nMeet";
    Display();
    if (meet)
        Combo();
}//end Meet
void disk::Combo()
{
    for (i = 0; i < size_x; i++)
        for (j = 0; j < size_y; j++)
            if (meetbead[i][j] < 0)
            {
                combo++;
                meetbead[i][j] = combo;
                for (x = 0; x < size_x; x++)
                    for (y = 0; y < size_y; y++)
                        if (bead[x][y] == bead[i][j] && meetbead[x][y] < 0)
                        {
                            if (meetbead[x + 1][y] == combo)
                                meetbead[x][y] = combo;
                            if (meetbead[x - 1][y] == combo)
                                meetbead[x][y] = combo;
                            if (meetbead[x][y + 1] == combo)
                                meetbead[x][y] = combo;
                            if (meetbead[x][y - 1] == combo)
                                meetbead[x][y] = combo;
                        }
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
    cout << "\tCombo:" << combo << endl;
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
        d.Play();
        cout << "\nFinal";
        d.Display();
        userIn = 0;
    }
}