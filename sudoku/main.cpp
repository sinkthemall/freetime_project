#include <bits/stdc++.h>
///made by d4rkn19ht
#include "sudoku.h"

using namespace std;

void menu()
{
    cout<<"WELCOME TO MY SUDOKU PROGRAM!!!!\n";
    cout<<"1. Solve board\n";
    cout<<"2. Generate easy board\n";
    cout<<"3. Generate normal board\n";
    cout<<"4. Generate master board\n";
}
int main()
{
    srand(int(time(0)));
    sudoku a;
    while (true)
    {
        menu();
        int choice;
        cin>>choice;
        if (choice==1)
        {
            a.enter();
            a.solve();
        }
        else if (choice == 2)
        {
            a.generate_easy();
        }
        else if (choice == 3)
        {
            a.generate_normal();
        }
        else if (choice == 4)
        {
            a.generate_master();
        }
        else cout<<"Invalid option!!!\n";
    }
    return 0;
}
