board = [' ' for _ in range(9)]

def print_board():
    print()
    print(f" {board[0]} | {board[1]} | {board[2]}")
    print("---+---+---")
    print(f" {board[3]} | {board[4]} | {board[5]}")
    print("---+---+---")
    print(f" {board[6]} | {board[7]} | {board[8]}")
    print()

def check_win(player):
    win_positions = [
        (0,1,2), (3,4,5), (6,7,8),
        (0,3,6), (1,4,7), (2,5,8),
        (0,4,8), (2,4,6)
    ]
    for a, b, c in win_positions:
        if board[a] == player and board[b] == player and board[c] == player:
            return True
    return False

def is_draw():
    return ' ' not in board

def minimax(is_ai):
    if check_win('O'):
        return 1
    if check_win('X'):
        return -1
    if is_draw():
        return 0

    if is_ai:
        best_score = -1000
        for i in range(9):
            if board[i] == ' ':
                board[i] = 'O'
                score = minimax(False)
                board[i] = ' '
                best_score = max(best_score, score)
        return best_score
    else:
        best_score = 1000
        for i in range(9):
            if board[i] == ' ':
                board[i] = 'X'
                score = minimax(True)
                board[i] = ' '
                best_score = min(best_score, score)
        return best_score

def ai_move():
    best_score = -1000
    best_move = -1
    for i in range(9):
        if board[i] == ' ':
            board[i] = 'O'
            score = minimax(False)
            board[i] = ' '
            if score > best_score:
                best_score = score
                best_move = i
    board[best_move] = 'O'

def player_move():
    while True:
        position = int(input("Enter position (1-9): ")) - 1
        if 0 <= position < 9 and board[position] == ' ':
            board[position] = 'X'
            break
        else:
            print("Invalid move! Try again.")

def main():
    print("TIC TAC TOE")
    print("You are X | AI is O")

    while True:
        print_board()
        player_move()

        if check_win('X'):
            print_board()
            print("You win!")
            break

        if is_draw():
            print_board()
            print("Game Draw!")
            break

        ai_move()

        if check_win('O'):
            print_board()
            print("AI wins!")
            break

        if is_draw():
            print_board()
            print("Game Draw!")
            break

if __name__ == "__main__":
    main()
