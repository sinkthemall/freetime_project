#include <bits/stdc++.h>
#define _for(i,a,b) for(int i=(a),_b=(b);i<_b;++i)
#ifndef NIM_H
#define NIM_H
using namespace std;

class NIM
{
private:
    vector<int> NIM_collumn;
    public:
        NIM();
        ~NIM();
        void initialization();
        void random_initialization();
        bool take_from(int num, int col);
        bool game_over();
        void print_state();
        vector<int> NIM_state();
};

#endif // NIM_H
