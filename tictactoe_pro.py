import random
import os
import time

class TicTacToe:
    def __init__(self):
    
        self.board = [" " for _ in range(9)]
        self.wins = [
            [0, 1, 2], [3, 4, 5], [6, 7, 8], 
            [0, 3, 6], [1, 4, 7], [2, 5, 8], 
            [0, 4, 8], [2, 4, 6]             
        ]

    def draw_board(self):
        
        os.system('cls' if os.name == 'nt' else 'clear')
        print("\n   --- Tic-Tac-Toe Pro ---")
        
        display_board = [str(i+1) if val == " " else val for i, val in enumerate(self.board)]
        
        print(f"      {display_board[0]} | {display_board[1]} | {display_board[2]} ")
        print("     ---+---+---")
        print(f"      {display_board[3]} | {display_board[4]} | {display_board[5]} ")
        print("     ---+---+---")
        print(f"      {display_board[6]} | {display_board[7]} | {display_board[8]} ")
        print("   -----------------------\n")

    def check_winner(self, board, player):
        """Returns True if the specified player has won."""
        return any(all(board[pos] == player for pos in combo) for combo in self.wins)

    def is_board_full(self, board):
        """Returns True if no empty spaces remain."""
        return " " not in board

    def minimax(self, board, is_maximizing):
        """AI logic to calculate the best possible outcome."""
        if self.check_winner(board, 'O'): return 1
        if self.check_winner(board, 'X'): return -1
        if self.is_board_full(board): return 0

        if is_maximizing:
            best_score = -float('inf')
            for i in range(9):
                if board[i] == " ":
                    board[i] = 'O'
                    score = self.minimax(board, False)
                    board[i] = " "
                    best_score = max(score, best_score)
            return best_score
        else:
            best_score = float('inf')
            for i in range(9):
                if board[i] == " ":
                    board[i] = 'X'
                    score = self.minimax(board, True)
                    board[i] = " "
                    best_score = min(score, best_score)
            return best_score

    def get_ai_move(self, difficulty):
        """Handles AI move selection based on difficulty."""
        available_moves = [i for i, x in enumerate(self.board) if x == " "]

        if difficulty == 1: 
            return random.choice(available_moves)

        if difficulty == 2: 
            for p in ['O', 'X']:
                for move in available_moves:
                    self.board[move] = p
                    if self.check_winner(self.board, p):
                        self.board[move] = " "
                        return move
                    self.board[move] = " "
            return 4 if 4 in available_moves else random.choice(available_moves)

        best_score = -float('inf')
        best_move = None
        for move in available_moves:
            self.board[move] = 'O'
            score = self.minimax(self.board, False)
            self.board[move] = " "
            if score > best_score:
                best_score = score
                best_move = move
        return best_move

    def start_game(self):
        """Main game loop."""
        mode = input("1. vs AI | 2. PvP: ")
        diff = 0
        if mode == '1':
            diff = int(input("Difficulty (1-Easy, 2-Med, 3-Hard): "))

        current_player = 'X'

        while True:
            self.draw_board()
            
            try:
                move = int(input(f"Player {current_player} (1-9): ")) - 1
                if self.board[move] != " ":
                    print("Spot taken! Try again.")
                    time.sleep(1)
                    continue
            except (ValueError, IndexError):
                print("Invalid input! Enter 1-9.")
                time.sleep(1)
                continue

            self.board[move] = current_player

            if self.check_winner(self.board, current_player):
                self.draw_board()
                print(f"🎉 Winner: {current_player}!")
                break
            if self.is_board_full(self.board):
                self.draw_board()
                print("🤝 It's a Draw!")
                break

            if mode == '1':
                self.draw_board()
                print("🤖 AI is thinking...")
                time.sleep(0.6)
                ai_move = self.get_ai_move(diff)
                self.board[ai_move] = 'O'
                
                if self.check_winner(self.board, 'O'):
                    self.draw_board()
                    print("💀 AI Wins! Better luck next time.")
                    break
            else:
                current_player = 'O' if current_player == 'X' else 'X'

if __name__ == "__main__":
    game = TicTacToe()
    game.start_game()