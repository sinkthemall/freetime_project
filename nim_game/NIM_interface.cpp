#include "NIM_interface.h"

NIM_interface::NIM_interface()
{
    //ctor
}

NIM_interface::~NIM_interface()
{
    //dtor
}
void NIM_interface::menu()
{
    cout<<"1) Display rules\n";
    cout<<"2) Create random NIM game\n";
    cout<<"3) Create your own NIM game\n";
}
void NIM_interface::create_random()
{
    GAME.random_initialization();
}
void NIM_interface::create()
{
    GAME.initialization();
}
void NIM_interface::rule_explain()
{
    cout<<"In the game, there will be some collumns( let's call the number of collumn is N), each collumn have amount of coins.";
    cout<<"Each player takes turn. In their turn, player choose a collumn with number of coins in it greater than 0(any of them) ";
    cout<<"and take amount of coins out of the collumn(remove it from the game) with condition that the number of coin being taken out is less ";
    cout<<"or equal than the number of coin in the collumn. The player who cannot make a legal move will lose the game.\n";
    cout<<"GOOD LUCK in winning AI.\n";
}
void NIM_interface::result()
{
    if (player_win)
        cout<<"Player win!!!\n";
    else
        cout<<"AI win!!!\n";
}
int NIM_interface::iinput(string a)
{
    cout<<a;
    int val;
    cin>>val;
    return val;
}
string NIM_interface::sinput(string a)
{
    cout<<a;
    string val;
    cin>>val;
    return val;
}
void NIM_interface::NIM_game()
{
    ///first, decide who will play first
    srand(int(time(0)));
    cout<<"Do you want to play first, or second, or let your fate decide(F/S/R)?\n";
    while(true)
    {
        string turn = sinput(">>> ");
        if (turn == "F")
        {
            player_turn = true;
            break;
        }
        else if (turn == "S")
        {
            player_turn = false;
            break;
        }
        else if (turn == "R")
        {
            player_turn = rand()%2;
            break;
        }
        else
            cout<<"Invalid command, please try again!!!\n";
    }
    while(!GAME.game_over())
    {
       int num , col;
       GAME.print_state();
       if (player_turn)
       {
           do
           {
               cout<<"Enter number of coin to take:\n";
               num = iinput(">>> ");
               cout<<"Enter position of collumn:\n";
               col = iinput(">>> ");
           }
           while(!GAME.take_from(num, col));
       }
       else
       {
           pair<int,int> q = AI.decision(GAME.NIM_state());
           num = q.first;
           col = q.second;
           cout<<"AI has choose to remove "<<num<<" coins from collumn "<<col<<"\n";
           GAME.take_from(num, col);
       }

       player_turn = player_turn ^ 1;
    }
    GAME.print_state();
    cout<<"GAME OVER!!!\n";
    if (player_turn)
    {
        player_win = false;
    }
    else player_win = true;

}
void NIM_interface::interface()
{
    cout<<"WELCOME TO THE NIM GAME!!!\n";
    cout<<"##########################\n\n";
    while(true)
    {
        menu();
        cout<<"Please enter your command:\n";
        int cmd = iinput(">>> ");
        if (cmd == 1)
        {
            rule_explain();
        }
        else if (cmd == 2)
        {
            GAME.random_initialization();
            NIM_game();
        }
        else if (cmd == 3)
        {
            GAME.initialization();
            NIM_game();
        }
    }
}
