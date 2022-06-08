#ifndef SUDOKU_H
#define SUDOKU_H
#include <bits/stdc++.h>
#define _for(i,a,b) for(int i=(a),_b=(b);i<_b;++i)
using namespace std;
class sudoku
{
    public:
        sudoku();
        ~sudoku();
        bool valid_board();
        void enter();
        void solve();
        void print_board();
        void generate_fullboard();
        void generate_easy(); ///20 cells
        void generate_normal();/// 30 cells
        void generate_master();/// 40 cells
    protected:
        int a[9][9];
        bool solved = false;
    private:
        int backtracking_with_count(int x,int y);
        bool board_solved();
        void backtracking(int x,int y);
        bool check_row(int i);
        bool check_collumn(int j);
        bool check_grid(int x,int y);
};

#endif // SUDOKU_H
