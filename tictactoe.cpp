#include <iostream>
#include <vector>
#include <limits>
using namespace std;
char board[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
void printBoard() {
    cout << "\n";
    cout << board[0] << " | " << board[1] << " | " << board[2] << "\n";
    cout << "--+---+--\n";
    cout << board[3] << " | " << board[4] << " | " << board[5] << "\n";
    cout << "--+---+--\n";
    cout << board[6] << " | " << board[7] << " | " << board[8] << "\n\n";
}
bool checkWin(char p) {
    int w[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };
    for(auto &x : w)
        if(board[x[0]]==p && board[x[1]]==p && board[x[2]]==p)
            return true;
    return false;
}

bool isDraw() {
    for(int i=0;i<9;i++)
        if(board[i]==' ') return false;
    return true;
}
int minimax(bool isMax) {
    if(checkWin('O')) return 1;
    if(checkWin('X')) return -1;
    if(isDraw()) return 0;

    if(isMax) {
        int best = -1000;
        for(int i=0;i<9;i++) {
            if(board[i]==' ') {
                board[i]='O';
                best = max(best, minimax(false));
                board[i]=' ';
            }
        }
        return best;
    } else {
        int best = 1000;
        for(int i=0;i<9;i++) {
            if(board[i]==' ') {
                board[i]='X';
                best = min(best, minimax(true));
                board[i]=' ';
            }
        }
        return best;
    }
}
void aiMove() {
    int bestScore = -1000, move = -1;
    for(int i=0;i<9;i++) {
        if(board[i]==' ') {
            board[i]='O';
            int score = minimax(false);
            board[i]=' ';
            if(score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    board[move] = 'O';
}
void playerMove() {
    int pos;
    while(true) {
        cout << "Choose position (1-9): ";
        cin >> pos;
        pos--;
        if(pos>=0 && pos<9 && board[pos]==' ') {
            board[pos]='X';
            break;
        }
        cout << "Invalid move. Try again.\n";
    }
}
int main() {
    cout << "TIC TAC TOE - You (X) vs AI (O)\n";
    while(true) {
        printBoard();
        playerMove();
        if(checkWin('X')) { printBoard(); cout<<"You win!\n"; break; }
        if(isDraw()) { printBoard(); cout<<"Draw!\n"; break; }

        aiMove();
        if(checkWin('O')) { printBoard(); cout<<"AI wins!\n"; break; }
        if(isDraw()) { printBoard(); cout<<"Draw!\n"; break; }
    }
    return 0;
}
