#include <iostream>
#include <climits>
using namespace std;

char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

char AI = 'O', HUMAN = 'X';

// Check who won
int checkWinner() {
    // Rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2]) {
            if (board[i][0] == AI) return 10;
            if (board[i][0] == HUMAN) return -10;
        }

        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i]) {
            if (board[0][i] == AI) return 10;
            if (board[0][i] == HUMAN) return -10;
        }
    }

    // Diagonals
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        if (board[0][0] == AI) return 10;
        if (board[0][0] == HUMAN) return -10;
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        if (board[0][2] == AI) return 10;
        if (board[0][2] == HUMAN) return -10;
    }

    return 0;
}

// Check if empty cells exist
bool movesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return true;

    return false;
}

// Minimax with Alpha-Beta Pruning
int minimax(bool isAI, int alpha, int beta) {

    int score = checkWinner();

    if (score == 10 || score == -10)
        return score;

    if (!movesLeft())
        return 0;

    // AI = Maximizer
    if (isAI) {
        int best = INT_MIN;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {

                if (board[i][j] == ' ') {
                    board[i][j] = AI;

                    best = max(best,
                        minimax(false, alpha, beta));

                    board[i][j] = ' ';

                    alpha = max(alpha, best);

                    if (beta <= alpha)
                        return best;
                }
            }
        }

        return best;
    }

    // Human = Minimizer
    else {
        int best = INT_MAX;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {

                if (board[i][j] == ' ') {
                    board[i][j] = HUMAN;

                    best = min(best,
                        minimax(true, alpha, beta));

                    board[i][j] = ' ';

                    beta = min(beta, best);

                    if (beta <= alpha)
                        return best;
                }
            }
        }

        return best;
    }
} 

// Find best move for AI
pair<int, int> bestMove() {

    int bestScore = INT_MIN;
    pair<int, int> move = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            if (board[i][j] == ' ') {

                board[i][j] = AI;

                int score =
                    minimax(false, INT_MIN, INT_MAX);

                board[i][j] = ' ';

                if (score > bestScore) {
                    bestScore = score;
                    move = {i, j};
                }
            }
        }
    }

    return move;
}

// Display board
void display() {
    cout << "\n";

    for (int i = 0; i < 3; i++) {
        cout << " ";

        for (int j = 0; j < 3; j++) {
            cout << board[i][j];

            if (j < 2)
                cout << " | ";
        }

        cout << "\n";

        if (i < 2)
            cout << "---+---+---\n";
    }
}

// Main Game
int main() {

    cout << "You = X, AI = O\n";

    while (true) {

        display();

        int row, col;

        cout << "\nEnter row and column (1-3): ";
        cin >> row >> col;

        row--;
        col--;

        if (row < 0 || row >= 3 ||
            col < 0 || col >= 3 ||
            board[row][col] != ' ') {

            cout << "Invalid move!\n";
            continue;
        }

        board[row][col] = HUMAN;

        if (checkWinner() == -10) {
            display();
            cout << "\nYou Win!\n";
            break;
        }

        if (!movesLeft()) {
            display();
            cout << "\nDraw!\n";
            break;
        }

        // AI chooses optimal move
        pair<int, int> move = bestMove();

        board[move.first][move.second] = AI;

        cout << "\nAI played: "
             << move.first + 1 << " "
             << move.second + 1 << "\n";

        if (checkWinner() == 10) {
            display();
            cout << "\nAI Wins!\n";
            break;
        }

        if (!movesLeft()) {
            display();
            cout << "\nDraw!\n";
            break;
        }
    }

    return 0;
}