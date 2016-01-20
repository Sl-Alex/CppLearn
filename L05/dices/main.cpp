#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int dice(void)
{
    return rand() * 6 / (RAND_MAX + 1) + 1;
}

struct stats {
    int wins1;  ///< Player 1 wins
    int wins2;  ///< Player 2 wins
    int ties;   ///< Nobody wins
};

int main()
{
    stats st = {0,0,0};
    srand(time(0));

    cout << "Press \"Enter\" to start the game." << endl;
    cout << "'x' will stop the game." << endl;

    char c[2];
    cin.getline(c,2);
    cin.clear();
    cin.sync();

    cout << "PLAYER1 VS PLAYER2 |" << endl;
    cout << "================== |" << endl;
    while (c[0] != 'x')
    {
        int num1 = dice();
        int num2 = dice();

        cout << "   " << num1 << "          " << num2 << "    | ";

        if (num2 > num1)
        {
            ++st.wins1;
            cout << "P2 ";
        }
        else if (num1 > num2)
        {
            ++st.wins2;
            cout << "P1 ";
        }
        else
        {
            ++st.ties;
            cout << "== ";
        }

        // Wait for the input
        cin.getline(c,2);

        // Clear the rest of the buffer (if any)
        cin.clear();
        cin.sync();
    }
    cout << "================== |" << endl;
    cout << "PLAYER1 wins: " << st.wins1 << endl;
    cout << "PLAYER2 wins: " << st.wins2 << endl;
    cout << "Ties count: "   << st.ties << endl;

    return 0;
}
