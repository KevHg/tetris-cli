#include <iostream>

using namespace std;

struct Space {
    char pattern;
    bool occupied;
};

void setup(Space (&board)[10][10]);

void displayBoard(Space (&board)[10][10]);

void generateShape(char (&shape)[3][3]);

bool dropShape(Space (&board)[10][10], char shape[3][3], int column);

int main() {
    Space board[10][10];
    char shape[3][3];
    int column;
    bool game_over;

    setup(board);
    displayBoard(board);
    generateShape(shape);

    cout << "Drop on which column (0-7): ";
    cin >> column;
    while (column >= 0 && column <= 7) {
        game_over = dropShape(board, shape, column);
        if (game_over)
            break;

        displayBoard(board);
        generateShape(shape);

        cout << "Drop on which column (0-7): ";
        cin >> column;
    }
    cout << "Game over! Thank you for playing!" << endl;
    return 0;
}

void setup(Space (&board)[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            board[i][j].pattern = '.';
            board[i][j].occupied = false;
        }
    }
}

void displayBoard(Space (&board)[10][10]) {
    for (int i = 0; i < 10; i++) {
        if (i == 0)
            cout << "  ";
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < 10; i++) {
        cout << i << " ";
        for (int j = 0; j < 10; j++)
            cout << board[i][j].pattern << " ";
        cout << endl;
    }
}

void generateShape(char (&shape)[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            shape[i][j] = '.';
    }
    shape[2][0] = 'X';
    shape[2][1] = 'X';
    shape[2][2] = 'X';
    shape[1][1] = 'X';
}

// Return true if initial placement unsuccessful, i.e. game over
bool dropShape(Space (&board)[10][10], char shape[3][3], int column) {
    bool end = false;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (shape[i][j] != '.' && board[i][column + j].occupied) {
                end = true;
            } else {
                board[i][column + j].pattern = shape[i][j];
                if (shape[i][j] != '.')
                    board[i][column + j].occupied = true;
            }
        }
    }
    //displayBoard(board);
    if (end)
        return end;

    int row = 1;
    while (row <= 7 && !end) {
        //check if going down once is fine
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (shape[i][j] != '.') {
                    board[row - 1 + i][column + j].pattern = '.';
                    board[row - 1 + i][column + j].occupied = false;
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (shape[i][j] != '.' && board[row + i][column + j].occupied)
                    end = true;
            }
        }
        if (!end) {
            //shift down
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (shape[i][j] != '.') {
                        board[row - 1 + i][column + j].pattern = '.';
                        board[row - 1 + i][column + j].occupied = false;
                    }
                }
            }
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (shape[i][j] != '.') {
                        board[row + i][column + j].pattern = shape[i][j];
                        board[row + i][column + j].occupied = true;
                    }
                }
            }
        } else {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (shape[i][j] != '.') {
                        board[row -1 + i][column + j].pattern = shape[i][j];
                        board[row -1 + i][column + j].occupied = true;
                    }
                }
            }

        }
        row++;
        //displayBoard(board);
    }
    return false;
}


