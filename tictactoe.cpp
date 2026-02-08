#include <iostream>
using namespace std;

char board[9] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };

void printBoard() {
    cout << "\n";
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << "\n";
    cout << "---+---+---\n";
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << "\n";
    cout << "---+---+---\n";
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << "\n\n";
}

bool checkWin(char player) {
    int winPositions[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };

    for(int i = 0; i < 8; i++) {
        if(board[winPositions[i][0]] == player &&
           board[winPositions[i][1]] == player &&
           board[winPositions[i][2]] == player) {
            return true;
        }
    }
    return false;
}

bool isDraw() {
    for(int i = 0; i < 9; i++) {
        if(board[i] == ' ')
            return false;
    }
    return true;
}

int minimax(bool isAI) {
    if(checkWin('O')) return 1;
    if(checkWin('X')) return -1;
    if(isDraw()) return 0;

    if(isAI) {
        int bestScore = -1000;
        for(int i = 0; i < 9; i++) {
            if(board[i] == ' ') {
                board[i] = 'O';
                int score = minimax(false);
                board[i] = ' ';
                bestScore = max(bestScore, score);
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for(int i = 0; i < 9; i++) {
            if(board[i] == ' ') {
                board[i] = 'X';
                int score = minimax(true);
                board[i] = ' ';
                bestScore = min(bestScore, score);
            }
        }
        return bestScore;
    }
}

void aiMove() {
    int bestScore = -1000;
    int bestMove = -1;

    for(int i = 0; i < 9; i++) {
        if(board[i] == ' ') {
            board[i] = 'O';
            int score = minimax(false);
            board[i] = ' ';
            if(score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    board[bestMove] = 'O';
}

void playerMove() {
    int position;
    while(true) {
        cout << "Enter position (1-9): ";
        cin >> position;
        position--;
        if(position >= 0 && position < 9 && board[position] == ' ') {
            board[position] = 'X';
            break;
        }
        cout << "Invalid move! Try again.\n";
    }
}

int main() {
    cout << "TIC TAC TOE\n";
    cout << "You are X | AI is O\n";

    while(true) {
        printBoard();
        playerMove();

        if(checkWin('X')) {
            printBoard();
            cout << "You win!\n";
            break;
        }

        if(isDraw()) {
            printBoard();
            cout << "Game Draw!\n";
            break;
        }

        aiMove();

        if(checkWin('O')) {
            printBoard();
            cout << "AI wins!\n";
            break;
        }

        if(isDraw()) {
            printBoard();
            cout << "Game Draw!\n";
            break;
        }
    }
    return 0;
}
