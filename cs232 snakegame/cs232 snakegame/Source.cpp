#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

// global declarations
bool gameOver;
const int height = 20;
const int width = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail; 

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

// function prototypes
void setup();
void draw();
void input();
void logic();

int main() {
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(100); 
    }
}

void setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void draw() {
    system("cls"); // clear the screen

    // draw the top wallk
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    // draw the map
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#"; 

            if (i == y && j == x)
                cout << "O"; 
            else if (i == fruitY && j == fruitX)
                cout << "F"; 
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // draw the snake's tail
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#"; // draw right wall
        }
        cout << endl;
    }

    // draw the bottom wall
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Score:" << score << endl;
}

void input() {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
        case 'q':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'z':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'e':
            gameOver = true;
            break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // if snake hits the wall, game over
    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;

    // if snake eats the fruit
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++; // increase the length of the tail
    }
}

