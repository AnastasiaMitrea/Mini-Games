#include <iostream>
using namespace std;
void TicTacToe();

int main(){
    TicTacToe();
    int a;
    cin >> a;
    return 0;
}

void TicTacToe(){
    cout << "Player 1: 1    &    Player 2: 2" << endl
         << endl;
    cout << "Positions: " << endl
         << endl;
    int pos = 1;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout << pos << ' ';
            pos++;
        }
        cout << endl;
    }

    const int n = 3;
    int matrice[n][n];

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            matrice[i][j] = 0;
        }
    }

    cout << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << matrice[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    int win = -1;
    for (int k = 0; k < 9 && win == -1; k++){
        int simbol;

        if (k % 2 == 0){
            simbol = 1;
            cout << endl;
            cout << "Player 1's turn" << endl;
        }
        else{
            simbol = 2;
            cout << endl;
            cout << "Player 2's turn" << endl;
        }
        cout << endl;

        int location;
        cin >> location;

        switch (location){
        case 1:
            matrice[0][0] = simbol;
            break;
        case 2:
            matrice[0][1] = simbol;
            break;
        case 3:
            matrice[0][2] = simbol;
            break;
        case 4:
            matrice[1][0] = simbol;
            break;
        case 5:
            matrice[1][1] = simbol;
            break;
        case 6:
            matrice[1][2] = simbol;
            break;
        case 7:
            matrice[2][0] = simbol;
            break;
        case 8:
            matrice[2][1] = simbol;
            break;
        case 9:
            matrice[2][2] = simbol;
            break;
        }

        cout << endl;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cout << matrice[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        if (matrice[0][0] != 0 && matrice[0][0] == matrice[0][1] && matrice[0][1] == matrice[0][2])
            win = matrice[0][0];
        else if (matrice[1][0] != 0 && matrice[1][0] == matrice[1][1] && matrice[1][1] == matrice[1][2])
            win = matrice[1][0];
        else if (matrice[2][0] != 0 && matrice[2][0] == matrice[2][1] && matrice[2][1] == matrice[2][2])
            win = matrice[2][0];
        else if (matrice[0][0] != 0 && matrice[0][0] == matrice[1][0] && matrice[1][0] == matrice[2][0])
            win = matrice[0][0];
        else if (matrice[0][1] != 0 && matrice[0][1] == matrice[1][1] && matrice[1][1] == matrice[2][1])
            win = matrice[0][1];
        else if (matrice[0][2] != 0 && matrice[0][2] == matrice[1][2] && matrice[1][2] == matrice[2][2])
            win = matrice[0][2];
        else if (matrice[0][0] != 0 && matrice[0][0] == matrice[1][1] && matrice[1][1] == matrice[2][2]) // diag principala
            win = matrice[0][0];
        else if (matrice[0][2] != 0 && matrice[0][2] == matrice[1][1] && matrice[1][1] == matrice[2][0]) // diag secundara
            win = matrice[0][2];

        if (win != -1)
            cout << "Player " << win << " has won the game!" << endl;
    }
    if (win == -1)
        cout << "Draw - None of the players has won." << endl;
}