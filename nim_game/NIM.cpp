#include "NIM.h"

NIM::NIM()
{
    //ctor
}

NIM::~NIM()
{
    //dtor
}
bool NIM::game_over()
{
    for(auto i : NIM_collumn)
        if (i>0) return false;
    return true;
}
bool NIM::take_from(int num,int col)
{
    if (col >= int(NIM_collumn.size()))
    {
        cout<<"The collumn doesn't exit, please try again!!!\n";
        return false;
    }
    if (NIM_collumn[col - 1] < num || num <=0)
    {
        cout<<"You can't do that because it violate the rules, please try again!!!\n";
        return false;
    }
    NIM_collumn[col - 1] -= num;
    return true;
}
void NIM::initialization()
{
    NIM_collumn.clear();
    int n;
    cout<<"Enter number of total collumn:\n>>> ";
    cin>>n;
    for(int i = 0;i<n; ++i)
    {
        int val;
        cout<<"Please enter number of coins in collumn "<<i + 1<<":\n>>> ";
        cin>>val;
        NIM_collumn.push_back(val);
    }
    cout<<"INTIALIZATION COMPLETED!!!\n";
}
void NIM::random_initialization()
{
    NIM_collumn.clear();
    /// i suggest the total of collumns should be less than 100 to make game faster, of course you can change it
    srand(int(time(0)));
    int n = rand()%12 + 1;
    for(int i = 0; i<n; ++i)
        NIM_collumn.push_back(rand()%20 + 1);
    cout<<"RANDOM INITIALIZATION COMPLETED!!!\n";
}
void NIM::print_state()
{
    cout<<"GAME CURRENT STATE\n";
    int N = int(NIM_collumn.size());
    for(int  i = 0; i<N; ++i) cout<<"-----";
    cout<<"--------\n";
    cout<<"Collumn:";
    for(int i = 0; i<N; ++i)
        cout<<setw(5)<<(i + 1);
    cout<<"\n";
    cout<<"Value:  ";
    for(auto i : NIM_collumn)
    {
        cout<<setw(5)<<i;
    }
    cout<<"\n";
    for(int  i = 0; i<N; ++i) cout<<"-----";
    cout<<"--------\n";
}
vector<int> NIM::NIM_state()
{
    return NIM_collumn;
}
