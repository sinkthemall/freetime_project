#include <bits/stdc++.h>
#include "NIM.h"
#include "NIM_AI.h"
#ifndef NIM_INTERFACE_H
#define NIM_INTERFACE_H

using namespace std;


class NIM_interface
{
    ///remember this game is between player and AI
    /// i'm gonna build the player vs player feature later
    NIM GAME;
    NIM_AI AI;
    bool player_win,player_turn;
    public:
        NIM_interface();
        ~NIM_interface();
        void menu();
        void rule_explain();/// 1
        void create_random();/// 2
        void create();/// 3
        void NIM_game();
        void result();
        void interface();/// this is the main interface
        int iinput(string a);
        string sinput(string a);
};

#endif // NIM_INTERFACE_H
