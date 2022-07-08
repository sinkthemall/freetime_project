#include <bits/stdc++.h>

#ifndef NIM_AI_H
#define NIM_AI_H
using namespace std;


class NIM_AI
{
    vector<int> state;
    public:
        NIM_AI();
        ~NIM_AI();
        void get_state(vector<int> a);
        pair<int,int> decision(vector<int> a);
};

#endif // NIM_AI_H
