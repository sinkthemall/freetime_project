#include "NIM_AI.h"

NIM_AI::NIM_AI()
{
    //ctor
}

NIM_AI::~NIM_AI()
{
    //dtor
}
void NIM_AI::get_state(vector<int> a)
{
    state.clear();
    state = a;
}
pair<int,int> NIM_AI::decision(vector<int> a)/// first is number of coin, second is the position of collumn
{
    get_state(a);
    ///this is strategy decision part
    int NIMXOR = 0;
    int N = int(state.size());
    for(auto i : state)
    {
        NIMXOR = NIMXOR^ i;
    }
    /// if state is winable
    if (NIMXOR != 0)
    {
        for(int i  =0; i< N; ++i)
        {
            if (state[i] >= NIMXOR)
            {
                return pair<int,int> ((state[i] - (NIMXOR ^ state[i])), i + 1);/// of course i won't proof this theorem, u have to do it yourself
            }
        }
    }
    else
    {
        for(int i = 0;i<N; ++i)
        {
            if (state[i] > 0)
            {
                return pair<int,int> (1, i + 1);
            }
        }
        return pair<int,int> (-1,1);/// this is added just to make compiler not warnning
    }
    return pair<int,int> (-1,1); /// this is added just to make compiler not warnning
}
