#include <iostream>
#include <random>
#include <time.h>

using namespace std;

struct Space {
    char pattern;
    bool occupied;
};

void setup(Space (&board)[10][10]);

void displayBoard(Space (&board)[10][10]);

void generateShape(char (&shape)[3][3], int type);

void displayShape(char shape[3][3]);

bool dropShape(Space (&board)[10][10], char shape[3][3], int column);

void checkBoard(Space (&board)[10][10]);

int main() {
    Space board[10][10];
    char shape[3][3];
    int column;
    bool game_over;

    default_random_engine generator((unsigned int) time(0));
    uniform_int_distribution<int> distribution(0, 5);
    int number = distribution(generator); //To remove initial random value of 0
    number = distribution(generator);

    setup(board);
    generateShape(shape, number);

    cout<<"Your next shape is: "<<endl;
    displayShape(shape);
    displayBoard(board);

    cout << "Drop on which column (0-7, otherwise to quit): ";
    cin >> column;
    while (column >= 0 && column <= 7) {
        game_over = dropShape(board, shape, column);
        if (game_over)
            break;

        checkBoard(board);
        number = distribution(generator);
        generateShape(shape, number);
        cout<<"Your next shape is: "<<endl;
        displayShape(shape);
        displayBoard(board);

        cout << "Drop on which column (0-7, otherwise to quit): ";
        cin >> column;
    }
    cout << "Game over! Thank you for playing!" << endl;
    //system("pause");
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

void generateShape(char (&shape)[3][3], int type) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            shape[i][j] = '.';
    }
    if (type == 0) { //T-shaped (reversed)
        shape[2][0] = 'T';
        shape[2][1] = 'T';
        shape[2][2] = 'T';
        shape[1][1] = 'T';
    } else if (type == 1) { //I-shaped
        shape[0][1] = 'I';
        shape[1][1] = 'I';
        shape[2][1] = 'I';
    } else if (type == 2) { //Z-shaped
        shape[1][0] = 'Z';
        shape[1][1] = 'Z';
        shape[2][1] = 'Z';
        shape[2][2] = 'Z';
    } else if (type == 3) { //Block-shaped
        shape[1][0] = 'B';
        shape[1][1] = 'B';
        shape[2][0] = 'B';
        shape[2][1] = 'B';
    } else if (type == 4) { //L-shaped
        shape[2][0] = 'L';
        shape[2][1] = 'L';
        shape[2][2] = 'L';
        shape[1][2] = 'L';
    } else if (type == 5) { //L-shaped standing
        shape[0][2] = 'P';
        shape[1][2] = 'P';
        shape[2][2] = 'P';
        shape[0][1] = 'P';
    }
}

void displayShape(char shape[3][3]){
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout<<shape[i][j]<<" ";
        cout<<endl;
    }
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
        //Clear original block location before checking if shifting down is possible
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (shape[i][j] != '.') {
                    board[row - 1 + i][column + j].pattern = '.';
                    board[row - 1 + i][column + j].occupied = false;
                }
            }
        }
        //Check if shift down is fine (not occupied), set end = true if occupied
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (shape[i][j] != '.' && board[row + i][column + j].occupied)
                    end = true;
            }
        }
        if (!end) {
            //Below is not occupied, shift block down
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (shape[i][j] != '.') {
                        board[row + i][column + j].pattern = shape[i][j];
                        board[row + i][column + j].occupied = true;
                    }
                }
            }
        } else {
            //Below is occupied, add original block i.e. don't shift down
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (shape[i][j] != '.') {
                        board[row - 1 + i][column + j].pattern = shape[i][j];
                        board[row - 1 + i][column + j].occupied = true;
                    }
                }
            }

        }
        row++;
    }
    return false;
}

void checkBoard(Space (&board)[10][10]){
    bool bottomClear = true;
    for (int j=0; j<10; j++){
        if(!board[9][j].occupied)
            bottomClear = false;
    }
    if(bottomClear){
        cout<<"CLEAR"<<endl;
        for(int i=8; i>=0; i--){
            for(int j=0; j<10; j++){
                board[i+1][j].pattern = board[i][j].pattern;
                board[i+1][j].occupied = board[i][j].occupied;
            }
        }
        for(int j=0; j<10; j++){
            board[0][j].pattern = '.';
            board[0][j].occupied = false;
        }
    }
}


