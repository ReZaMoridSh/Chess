#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Chessboard
{
public:
    string getmove(int x, int y);
    bool occupied[8][8] = {false};
    char type[8][8] = {'-'};
    int color[8][8] = {0};    // black is 1 and white is 2 and empty is 0
    int king_pos[2][2] = {{-1,-1},{-1,-1}}; // black is 0 and white is 1;

    string move[8][8];
    Chessboard() = default;
    void setcolor(int x, int y, int color);
    void setoccupied(int x, int y, int color, bool occ);
    void settype(int x, int y, int color, char type);
    void setmove(int x, int y, int color, string m);
    void set_king_pos(int x, int y, int color);
    int getcolor(int x, int y);
    bool getoccupied(int x, int y);
    char gettype(int x, int y);
    int get_king_pos(int p, int color);
};

void Chessboard::setcolor(int x, int y, int color)
{
    this->color[x][y] = color;
}

void Chessboard::setoccupied(int x, int y, int color, bool occ)
{
    this->occupied[x][y] = occ;
}

void Chessboard::setmove(int x, int y, int color, string m)
{
    this->move[x][y] = m;
}

void Chessboard::settype(int x, int y, int color, char type)
{
    this->type[x][y] = type;
}

int Chessboard::getcolor(int x, int y)
{
    return (this->color[x][y]);
}

bool Chessboard::getoccupied(int x, int y)
{
    return (this->occupied[x][y]);
}

string Chessboard::getmove(int x, int y)
{
    return (this->move[x][y]);
}
char Chessboard::gettype(int x, int y)
{
    return (this->type[x][y]);
}
void Chessboard::set_king_pos(int x, int y, int color)
{
    this->king_pos[color - 1][0] = x;
    this->king_pos[color - 1][1] = y;
}

int Chessboard::get_king_pos(int p, int color)
{
    return (this->king_pos[color - 1][p]);
}

static Chessboard board;
static Chessboard board1;
static Chessboard board2;
static Chessboard board3;
static Chessboard board4;
static Chessboard Ch;
static Chessboard ChM;
static Chessboard CurrentBoard;
static Chessboard empty;
