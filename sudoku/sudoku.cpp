#include "sudoku.h"

sudoku::sudoku()
{
    //ctor
}

sudoku::~sudoku()
{
    //dtor
}
bool sudoku::check_row(int i)
{
    int cnt[10] = {0,0,0,0,0,0,0,0,0,0};
    _for(j,0,9)
    {
        if (a[i][j] != 0) cnt[a[i][j]] ++ ;
        if (cnt[a[i][j]] > 1) return false;
    }
    return true;
}

bool sudoku::check_collumn(int j)
{
    int cnt[10] = {0,0,0,0,0,0,0,0,0,0};
    _for(i,0,9)
    {
        if (a[i][j] != 0) cnt[a[i][j]] ++;
        if (cnt[a[i][j]] > 1) return false;
    }
    return true;
}

bool sudoku::check_grid(int x,int y)
{
    int X = x/3,Y = y/3;
    int cnt[10] = {0,0,0,0,0,0,0,0,0,0};
    _for(i,0,3)
        _for(j,0,3)
        {
            int newx = X*3 + i;
            int newy = Y*3 + j;
            if (a[newx][newy] != 0) ++cnt[a[newx][newy]];
            if (cnt[a[newx][newy]] > 1) return false;
        }
    return true;
}

bool sudoku::valid_board()
{
    _for(i,0,9)
        _for(j,0,9)
            if (a[i][j] < 0 || a[i][j] > 9) return false;
    _for(i,0,9)
        if (!check_row(i) || !check_collumn(i)) return false;
    for(int i = 0; i<9; i += 3)
        for(int j = 0; j<9; j += 3)
            if (!check_grid(i, j)) return false;
    return true;
}

bool sudoku::board_solved()
{
    _for(i,0,9)
        _for(j,0,9)
            if ( a[i][j] == 0) return false;
    if (!valid_board()) return false;
    solved = true;
    return true;
}

void sudoku::backtracking(int x,int y)
{
    if (x>=9)
    {
        if (board_solved()) return;
    }
    else if (y>=9) backtracking(x + 1, 0);
    else
    {
        if (a[x][y] == 0)
        {
            _for(val, 1, 10)
            {
                a[x][y] = val;
                if (check_row(x) && check_collumn(y) && check_grid(x,y)) backtracking(x,y);
                if (solved) return ;
            }
            a[x][y] = 0;
        }
        else backtracking(x, y + 1);
    }
}

void sudoku::print_board()
{
    _for(i,0,9)
    {
        _for(j,0,9)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
}


void sudoku::solve()
{
    if (!valid_board())
    {
        cout<<"Board is not valid to solve!!!!\n";
    }
    else
    {
        backtracking(0,0);
        if (solved)
        {
            cout<<"Board after solving:\n";
            print_board();
        }
        else cout<<"Cannot solve board!!!\n";
    }
}

void sudoku::enter()
{
    cout<<"Enter sudoku board:\n";
    _for(i,0,9)
        _for(j,0,9)
            cin>>a[i][j];
}

void sudoku::generate_fullboard()
{
    ///fill 3 diagonal matrices
    vector<int> numbers;
    _for(val,1,10) numbers.push_back(val);
    _for(i,0,9)
        _for(j,0,9) a[i][j] = 0; ///empty the board

    _for(k,0,3)
    {
        random_shuffle(numbers.begin(), numbers.end());
        _for(i,0,3)
            _for(j,0,3)
            {
                int I = k*3 + i;
                int J = k*3 + j;
                a[I][J] = numbers[i*3 + j];
            }
    }
    backtracking(0,0);
    solved = false;
}

int sudoku::backtracking_with_count(int x,int y)
{
    if (x>=9)
    {
        if (board_solved()) return 1;
        else return 0;
    }
    else if (y>=9) return backtracking_with_count(x + 1, 0);
    else
    {

        if (a[x][y] == 0)
        {
            int sum  = 0;
            _for(val, 1, 10)
            {
                a[x][y] = val;
                if (check_row(x) && check_collumn(y) && check_grid(x,y)) sum += backtracking_with_count(x,y);
                if (sum > 1)
                {
                    a[x][y] = 0;
                    return sum;
                }
            }
            a[x][y] = 0;
            return sum;
        }
        else return backtracking_with_count(x, y + 1);
    }
}
void sudoku::generate_easy()
{
    generate_fullboard();
    #define fi first
    #define se second
    #define pir pair<int,int>
    vector<pir> coor;
    _for(i,0,9)
        _for(j,0,9) coor.push_back(pir(i,j));
    random_shuffle(coor.begin(), coor.end());
    int cnt = 0;
    for(auto i : coor)
    {
        int las = a[i.fi][i.se];
        a[i.fi][i.se] = 0;
        if (backtracking_with_count(0,0) > 1) a[i.fi][i.se] = las;
        else ++cnt;
        if (cnt == 20) break;
    }
    cout<<"Generating board:\n";
    print_board();
    solved = false;
}
void sudoku::generate_normal()
{
    generate_fullboard();
    #define fi first
    #define se second
    #define pir pair<int,int>
    vector<pir> coor;
    _for(i,0,9)
        _for(j,0,9) coor.push_back(pir(i,j));
    random_shuffle(coor.begin(), coor.end());
    int cnt = 0;
    for(auto i : coor)
    {
        int las = a[i.fi][i.se];
        a[i.fi][i.se] = 0;
        if (backtracking_with_count(0,0) > 1) a[i.fi][i.se] = las;
        else ++cnt;
        if (cnt == 30) break;
    }
    cout<<"Generating board:\n";
    print_board();
    solved = false;
}
void sudoku::generate_master()
{
    generate_fullboard();
    #define fi first
    #define se second
    #define pir pair<int,int>
    vector<pir> coor;
    _for(i,0,9)
        _for(j,0,9) coor.push_back(pir(i,j));
    random_shuffle(coor.begin(), coor.end());
    int cnt = 0;
    for(auto i : coor)
    {
        int las = a[i.fi][i.se];
        a[i.fi][i.se] = 0;
        if (backtracking_with_count(0,0) > 1) a[i.fi][i.se] = las;
        else ++cnt;
        if (cnt == 40) break;
    }
    cout<<"Generating board:\n";
    print_board();
    solved = false;
}
