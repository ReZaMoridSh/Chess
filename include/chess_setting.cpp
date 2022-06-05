#include "declar.cpp"
bool Check(Chessboard Board, char type, int x_src, int y_src, int x_dest, int y_dest, int player)
{
    Ch = Board;
    bool CHECK = false;
    string move;
    moveit(Ch, type, x_src, y_src, x_dest, y_dest, player, -2);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (Ch.getcolor(i, j) != player && Ch.getcolor(i, j) != 0)
            {
                move = Ch.getmove(i, j);
                for (int k = 0; k < move.length(); k = k + 4)
                {
                    int x, y;
                    x = move[k] - '0';
                    y = move[k + 2] - '0';
                    if (x == Ch.get_king_pos(0, player) && y == Ch.get_king_pos(1, player))
                    {
                        CHECK = true;
                        return CHECK;
                    }
                }
            }
        }
    return CHECK;
}

class piece
{
public:
    piece() = default;
    int color = 0;

    void set(Chessboard &boardhandle, char type, int x, int y, int color, int boardnum);
};

void piece::set(Chessboard &boardhandle, char type, int x, int y, int Color, int boardnum)
{
    piece::color = Color;
    boardhandle.settype(x, y, color, type);
    boardhandle.setcolor(x, y, Color);
    if (Color == 0)
        boardhandle.setoccupied(x, y, color, false);
    else
        boardhandle.setoccupied(x, y, color, true);
    if (type == 'K')
        boardhandle.set_king_pos(x, y, color);
}

class rook : public piece
{
public:
    rook() = default;
    void AvailableMove(Chessboard &boardhandle, int x, int y, bool ischeck, int boardnum);
    string ValidMove(Chessboard &boardhandle, int xpos, int ypos);
    bool CHECK_MOVE(Chessboard &boardhandle, int xpos, int ypos, int x, int y, bool ischeck);
};

bool rook::CHECK_MOVE(Chessboard &boardhandle, int xpos, int ypos, int x, int y, bool ischeck)
{
    bool out = false;
    int COLOR = boardhandle.getcolor(xpos, ypos);
    if (!ischeck && (Check(boardhandle, 'R', xpos, ypos, x, y, COLOR)))
        out = true;
    return out;
}

string rook::ValidMove(Chessboard &boardhandle, int x, int y)
{

    int move[4][7][2] = {{{x, y + 1}, {x, y + 2}, {x, y + 3}, {x, y + 4}, {x, y + 5}, {x, y + 6}, {x, y + 7}},
                         {{x, y - 1}, {x, y - 2}, {x, y - 3}, {x, y - 4}, {x, y - 5}, {x, y - 6}, {x, y - 7}},
                         {{x + 1, y}, {x + 2, y}, {x + 3, y}, {x + 4, y}, {x + 5, y}, {x + 6, y}, {x + 7, y}},
                         {{x - 1, y}, {x - 2, y}, {x - 3, y}, {x - 4, y}, {x - 5, y}, {x - 6, y}, {x - 7, y}}};
    string Move;
    int COLOR = boardhandle.getcolor(x, y);
    for (int p = 0; p < 4; p++)
    {
        for (int i = 0; i < 7; i++)
        {
            if (move[p][i][0] >= 8 || move[p][i][0] < 0 || move[p][i][1] >= 8 || move[p][i][1] < 0)
            {
                break;
            }
            else if (boardhandle.getoccupied(move[p][i][0], move[p][i][1]) && COLOR == boardhandle.getcolor(move[p][i][0], move[p][i][1]))
            {
                break;
            }
            else if (boardhandle.getoccupied(move[p][i][0], move[p][i][1]) && COLOR != boardhandle.getcolor(move[p][i][0], move[p][i][1]))
            {
                Move += to_string(move[p][i][0]);
                Move += "-";
                Move += to_string(move[p][i][1]);
                Move += " ";
                break;
            }
            else
            {
                Move += to_string(move[p][i][0]);
                Move += "-";
                Move += to_string(move[p][i][1]);
                Move += " ";
            }
        }
    }

    return Move;
}

void rook::AvailableMove(Chessboard &boardhandle, int x, int y, bool ischeck, int boardnum)
{

    string availablemove;
    string move = ValidMove(boardhandle, x, y);
    int len = move.length();
    int i = 0;
    for (int p = 0; p < len; p = p + 4)
    {
        int xx, yy;
        xx = move[p] - '0';
        yy = move[p + 2] - '0';
        if (!CHECK_MOVE(boardhandle, x, y, xx, yy, ischeck))
        {
            availablemove += to_string(xx);
            availablemove += "-";
            availablemove += to_string(yy);
            availablemove += " ";
        }
    }
    boardhandle.setmove(x, y, boardhandle.getcolor(x, y), availablemove);
}

class king : public piece
{
public:
    king();
    void AvailableMove(Chessboard &boardhandle, int x, int y, bool ischeck, int boardnum);
    bool IsValidMove(Chessboard &boardhandle, int x_pos, int y_pos, int x, int y, bool ischeck);
};

king::king() {}

bool king::IsValidMove(Chessboard &boardhandle, int xpos, int ypos, int x, int y, bool ischeck)
{
    bool valid = true;
    int COLOR = boardhandle.getcolor(xpos, ypos);
    if (x >= 8 || x < 0 || y >= 8 || y < 0)
        valid = false;
    else if (boardhandle.getcolor(xpos, ypos) == boardhandle.getcolor(x, y))
        valid = false;
    else if (!ischeck && Check(boardhandle, 'K', xpos, ypos, x, y, COLOR))
    {
        valid = false;
    }
    return valid;
}

void king::AvailableMove(Chessboard &boardhandle, int x, int y, bool ischeck, int boardnum)
{
    string availablemove;
    int i = 0;
    int move[8][2] = {{x + 1, y}, {x, y + 1}, {x + 1, y + 1}, {x - 1, y}, {x, y - 1}, {x - 1, y - 1}, {x - 1, y + 1}, {x + 1, y - 1}};
    for (int p = 0; p < 8; p++)
    {
        if (IsValidMove(boardhandle, x, y, move[p][0], move[p][1], ischeck))
        {
            availablemove += to_string(move[p][0]);
            availablemove += "-";
            availablemove += to_string(move[p][1]);
            availablemove += " ";
        }
    }
    boardhandle.setmove(x, y, boardhandle.getcolor(x, y), availablemove);
}

class bishop : public piece
{
public:
    bishop();
    void AvailableMove(Chessboard &boardhandle, int x, int y, bool ischeck, int boardnum);
    string ValidMove(Chessboard &boardhandle, int xpos, int ypos);
    bool CHECK_MOVE(Chessboard &boardhandle, int xpos, int ypos, int x, int y, bool ischeck);
};

bishop::bishop() {}

bool bishop::CHECK_MOVE(Chessboard &boardhandle, int xpos, int ypos, int x, int y, bool ischeck)
{
    bool out = false;
    int COLOR = boardhandle.getcolor(xpos, ypos);
    if (!ischeck && (Check(boardhandle, 'B', xpos, ypos, x, y, COLOR)))
        out = true;
    return out;
}

string bishop::ValidMove(Chessboard &boardhandle, int x, int y)
{

    int move[4][7][2] = {{{x + 1, y + 1}, {x + 2, y + 2}, {x + 3, y + 3}, {x + 4, y + 4}, {x + 5, y + 5}, {x + 6, y + 6}, {x + 7, y + 7}},
                         {{x - 1, y - 1}, {x - 2, y - 2}, {x - 3, y - 3}, {x - 4, y - 4}, {x - 5, y - 5}, {x - 6, y - 6}, {x - 7, y - 7}},
                         {{x + 1, y - 1}, {x + 2, y - 2}, {x + 3, y - 3}, {x + 4, y - 4}, {x + 5, y - 5}, {x + 6, y - 6}, {x + 7, y - 7}},
                         {{x - 1, y + 1}, {x - 2, y + 2}, {x - 3, y + 3}, {x - 4, y + 4}, {x - 5, y + 5}, {x - 6, y + 6}, {x - 7, y + 7}}};
    string Move;
    int COLOR = boardhandle.getcolor(x, y);
    for (int p = 0; p < 4; p++)
        for (int i = 0; i < 7; i++)
        {
            if (move[p][i][0] >= 8 || move[p][i][0] < 0 || move[p][i][1] >= 8 || move[p][i][1] < 0)
            {
                break;
            }
            else if (boardhandle.getoccupied(move[p][i][0], move[p][i][1]) && COLOR == boardhandle.getcolor(move[p][i][0], move[p][i][1]))
            {
                break;
            }
            else if (boardhandle.getoccupied(move[p][i][0], move[p][i][1]) && COLOR != boardhandle.getcolor(move[p][i][0], move[p][i][1]))
            {

                Move += to_string(move[p][i][0]);
                Move += "-";
                Move += to_string(move[p][i][1]);
                Move += " ";
                break;
            }
            else
            {
                Move += to_string(move[p][i][0]);
                Move += "-";
                Move += to_string(move[p][i][1]);
                Move += " ";
            }
        }

    return Move;
}

void bishop::AvailableMove(Chessboard &boardhandle, int x, int y, bool ischeck, int boardnum)
{
    string availablemove;
    string move = ValidMove(boardhandle, x, y);
    int len = move.size();
    int i = 0;
    for (int p = 0; p < len; p = p + 4)
    {
        int xx, yy;
        xx = move[p] - '0';
        yy = move[p + 2] - '0';
        if (!CHECK_MOVE(boardhandle, x, y, xx, yy, ischeck))
        {
            availablemove += move[p];
            availablemove += "-";
            availablemove += move[p + 2];
            availablemove += " ";
        }
    }
    boardhandle.setmove(x, y, boardhandle.getcolor(x, y), availablemove);
}

class queen : public piece
{
public:
    queen() = default;
    void AvailableMove(Chessboard &boardhandle, int x, int y, bool ischeck, int boardnum);
    string ValidMove(Chessboard &boardhandle, int xpos, int ypos);
    bool CHECK_MOVE(Chessboard &boardhandle, int xpos, int ypos, int x, int y, bool ischeck);
};

bool queen::CHECK_MOVE(Chessboard &boardhandle, int xpos, int ypos, int x, int y, bool ischeck)
{
    bool out = false;
    int COLOR = boardhandle.getcolor(xpos, ypos);
    if (!ischeck && (Check(boardhandle, 'Q', xpos, ypos, x, y, COLOR)))
        out = true;
    return out;
}

string queen::ValidMove(Chessboard &boardhandle, int x, int y)
{
    int move[8][7][2] = {{{x, y + 1}, {x, y + 2}, {x, y + 3}, {x, y + 4}, {x, y + 5}, {x, y + 6}, {x, y + 7}},
                         {{x, y - 1}, {x, y - 2}, {x, y - 3}, {x, y - 4}, {x, y - 5}, {x, y - 6}, {x, y - 7}},
                         {{x + 1, y}, {x + 2, y}, {x + 3, y}, {x + 4, y}, {x + 5, y}, {x + 6, y}, {x + 7, y}},
                         {{x - 1, y}, {x - 2, y}, {x - 3, y}, {x - 4, y}, {x - 5, y}, {x - 6, y}, {x - 7, y}},
                         {{x + 1, y + 1}, {x + 2, y + 2}, {x + 3, y + 3}, {x + 4, y + 4}, {x + 5, y + 5}, {x + 6, y + 6}, {x + 7, y + 7}},
                         {{x - 1, y - 1}, {x - 2, y - 2}, {x - 3, y - 3}, {x - 4, y - 4}, {x - 5, y - 5}, {x - 6, y - 6}, {x - 7, y - 7}},
                         {{x + 1, y - 1}, {x + 2, y - 2}, {x + 3, y - 3}, {x + 4, y - 4}, {x + 5, y - 5}, {x + 6, y - 6}, {x + 7, y - 7}},
                         {{x - 1, y + 1}, {x - 2, y + 2}, {x - 3, y + 3}, {x - 4, y + 4}, {x - 5, y + 5}, {x - 6, y + 6}, {x - 7, y + 7}}};
    string Move;
    int COLOR = boardhandle.getcolor(x, y);
    for (int p = 0; p < 8; p++)
        for (int i = 0; i < 7; i++)
        {
            if (move[p][i][0] >= 8 || move[p][i][0] < 0 || move[p][i][1] >= 8 || move[p][i][1] < 0)
            {
                break;
            }
            else if (boardhandle.getoccupied(move[p][i][0], move[p][i][1]) && COLOR == boardhandle.getcolor(move[p][i][0], move[p][i][1]))
            {
                break;
            }
            else if (boardhandle.getoccupied(move[p][i][0], move[p][i][1]) && COLOR != boardhandle.getcolor(move[p][i][0], move[p][i][1]))
            {
                Move += to_string(move[p][i][0]);
                Move += "-";
                Move += to_string(move[p][i][1]);
                Move += " ";
                break;
            }
            else
            {
                Move += to_string(move[p][i][0]);
                Move += "-";
                Move += to_string(move[p][i][1]);
                Move += " ";
            }
        }
    return Move;
}

void queen::AvailableMove(Chessboard &boardhandle, int x, int y, bool ischeck, int boardnum)
{
    string availablemove;
    string move = ValidMove(boardhandle, x, y);
    int len = move.length();
    int i = 0;
    for (int p = 0; p < len; p = p + 4)
    {
        int xx, yy;
        xx = move[p] - '0';
        yy = move[p + 2] - '0';
        if (!CHECK_MOVE(boardhandle, x, y, xx, yy, ischeck))
        {
            availablemove += move[p];
            availablemove += "-";
            availablemove += move[p + 2];
            availablemove += " ";
        }
    }
    boardhandle.setmove(x, y, boardhandle.getcolor(x, y), availablemove);
}

class pawn : public piece
{
public:
    pawn();

    int **Move(int x, int y, int color, int first);
    void AvailableMove(Chessboard &boardhandle, int x, int y, bool ischeck, int boardnum);
    vector<bool> IsValidMove(Chessboard &boardhandle, int xpos, int ypos, int first, int *arr[4], bool ischeck);
};
pawn::pawn()
{
}

int **pawn::Move(int x, int y, int color, int first)
{
    int neg = 1;
    if (color == 1)
        neg = -1;
    int **moveptr = new int *[3 + first];
    for (int i = 0; i < (3 + first); i++)
        moveptr[i] = new int[2];
    if (first == 1)
    {
        int move[4][2] = {{x + 1, y + 1 * neg}, {x - 1, y + 1 * neg}, {x, y + 1 * neg}, {x, y + 2 * neg}};

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 2; j++)
                moveptr[i][j] = move[i][j];
    }
    else if (first == 0)
    {
        int move[3][2] = {{x + 1, y + 1 * neg}, {x - 1, y + 1 * neg}, {x, y + 1 * neg}};

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 2; j++)
                moveptr[i][j] = move[i][j];
    }
    return moveptr;
}

std::vector<bool> pawn::IsValidMove(Chessboard &boardhandle, int xpos, int ypos, int first, int *arr[2], bool ischeck)
{
    std::vector<bool> valid = {true, true, true, true};
    int COLOR = boardhandle.getcolor(xpos, ypos);
    for (int i = 0; i < (3 + first); i++)
    {
        if (arr[i][0] >= 8 || arr[i][0] < 0 || arr[i][1] >= 8 || arr[i][1] < 0)
            valid[i] = false;
        else if (!ischeck && Check(boardhandle, 'P', xpos, ypos, arr[i][0], arr[i][1], COLOR))
            valid[i] = false;
    }
    if (boardhandle.getoccupied(arr[2][0], arr[2][1]))
        valid[2] = false;
    if (first == 1 && (!valid[2] || boardhandle.getcolor(arr[3][0], arr[3][1]) != 0))
        valid[3] = false;

    if ((boardhandle.getoccupied(arr[0][0], arr[0][1]) && (COLOR == boardhandle.getcolor(arr[0][0], arr[0][1]))) || !boardhandle.getoccupied(arr[0][0], arr[0][1]))
        valid[0] = false;
    if ((boardhandle.getoccupied(arr[1][0], arr[1][1]) && (COLOR == boardhandle.getcolor(arr[1][0], arr[1][1]))) || !boardhandle.getoccupied(arr[1][0], arr[1][1]))
    {
        valid[1] = false;
    }
    return valid;
}

void pawn::AvailableMove(Chessboard &boardhandle, int x, int y, bool ischeck, int boardnum)
{
    string availablemove;
    int first = 0;
    int COLOR = boardhandle.getcolor(x, y);
    if ((COLOR == 1 && y == 6) || (COLOR == 2 && y == 1))
        first = 1;
    int **move = Move(x, y, COLOR, first);
    std::vector<bool> valid = IsValidMove(boardhandle, x, y, first, move, ischeck);
    for (int p = 0; p < 3 + first; p++)
        if (valid[p])
        {
            availablemove += to_string(move[p][0]);
            availablemove += "-";
            availablemove += to_string(move[p][1]);
            availablemove += " ";
        }
    boardhandle.setmove(x, y, boardhandle.getcolor(x, y), availablemove);
}

class knight : public piece
{
public:
    knight();
    void AvailableMove(Chessboard &boardhandle, int x, int y, bool ischeck, int boardnum);
    bool IsValidMove(Chessboard &boardhandle, int xpos, int ypos, int x, int y, bool ischeck);
};
knight::knight() {}

bool knight::IsValidMove(Chessboard &boardhandle, int xpos, int ypos, int x, int y, bool ischeck)
{
    bool valid = true;
    int COLOR = boardhandle.getcolor(xpos, ypos);
    if (x >= 8 || x < 0 || y >= 8 || y < 0)
        valid = false;
    else if (boardhandle.getoccupied(x, y) == true && boardhandle.getcolor(xpos, ypos) == boardhandle.getcolor(x, y))
        valid = false;
    else if (ischeck == false && Check(boardhandle, 'N', xpos, ypos, x, y, COLOR))
        valid = false;
    return valid;
}

void knight::AvailableMove(Chessboard &boardhandle, int x, int y, bool ischeck, int boardnum)
{
    string availablemove;
    int i = 0;
    int move[8][2] = {{x + 1, y + 2}, {x + 1, y - 2}, {x - 1, y + 2}, {x - 1, y - 2}, {x + 2, y - 1}, {x + 2, y + 1}, {x - 2, y + 1}, {x - 2, y - 1}};

    for (int p = 0; p < 8; p++)
        if (IsValidMove(boardhandle, x, y, move[p][0], move[p][1], ischeck))
        {
            availablemove += to_string(move[p][0]);
            availablemove += "-";
            availablemove += to_string(move[p][1]);
            availablemove += " ";
        }
    boardhandle.setmove(x, y, boardhandle.getcolor(x, y), availablemove);
}

class Null : public piece
{
public:
    Null();
    void AvailableMove(Chessboard &boardhandle, int x, int y, int boardnum);
};

Null::Null() {}

void Null::AvailableMove(Chessboard &boardhandle, int x, int y, int boardnum)
{
    string null;

    boardhandle.setmove(x, y, boardhandle.getcolor(x, y), null);
}

void moveit(Chessboard &boardhandle, char type, int x_src, int y_src, int x_dest, int y_dest, int color, int boardnum)
{
    int next_player;
    (color == 1) ? next_player = 2 : (color == 2) ? next_player = 1
                                                  : next_player = 0;
    Null n;
    n.set(boardhandle, '-', x_src, y_src, 0, boardnum);
    n.AvailableMove(boardhandle, x_src, y_src, boardnum);
    if (type == 'K')
    {
        king p;
        p.set(boardhandle, 'K', x_dest, y_dest, color, boardnum);
    }
    else if (type == 'Q')
    {
        queen p;
        p.set(boardhandle, 'Q', x_dest, y_dest, color, boardnum);
    }
    else if (type == 'R')
    {
        rook p;
        p.set(boardhandle, 'R', x_dest, y_dest, color, boardnum);
    }
    else if (type == 'N')
    {
        knight p;
        p.set(boardhandle, 'N', x_dest, y_dest, color, boardnum);
    }
    else if (type == 'P')
    {
        pawn p;
        p.set(boardhandle, 'P', x_dest, y_dest, color, boardnum);
    }
    else if (type == 'B')
    {
        bishop p;
        p.set(boardhandle, 'B', x_dest, y_dest, color, boardnum);
    }
    SetMove(boardhandle, boardnum, next_player);
}

void SetMove(Chessboard &boardhandle, int boardnum, int next_player)
{
    bool ischeck = false;
    char type = '-';
    int player = 0;
    (next_player == 2) ? player = 1 : player = 2;
    if (boardnum == -2)
        ischeck = true;
    else if (boardnum == -1)
        next_player = player;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if ((boardhandle.getcolor(i, j) == next_player) || next_player == -1)
            {
                type = boardhandle.gettype(i, j);

                if (type == 'K')
                {
                    king p;
                    p.AvailableMove(boardhandle, i, j, ischeck, boardnum);
                }
                else if (type == 'Q')
                {

                    queen p;
                    p.AvailableMove(boardhandle, i, j, ischeck, boardnum);
                }
                else if (type == 'P')
                {
                    pawn p;
                    p.AvailableMove(boardhandle, i, j, ischeck, boardnum);
                }
                else if (type == 'R')
                {
                    rook p;
                    p.AvailableMove(boardhandle, i, j, ischeck, boardnum);
                }
                else if (type == 'N')
                {
                    knight p;
                    p.AvailableMove(boardhandle, i, j, ischeck, boardnum);
                }
                else if (type == 'B')
                {
                    bishop p;
                    p.AvailableMove(boardhandle, i, j, ischeck, boardnum);
                }
            }
        }
}




void setboard()
{
    char type = '-';
    int color = 0;
    char c = '-';
    for (int j = 7; j > -1; j--)
    {
        for (int i = 0; i < 8; i++)
        {
            string str = "";
            cin >> str;
            type = str[0];
            c = str[1];
            (c == 'W') ? color = 2 : (c == 'B') ? color = 1
                                                : 0;
            if (type == 'K')
            {
                king k;
                k.set(board, type, i, j, color, 0);
            }
            else if (type == 'Q')
            {
                queen q;
                q.set(board, type, i, j, color, 0);
            }
            else if (type == 'B')
            {
                bishop b;
                b.set(board, type, i, j, color, 0);
            }
            else if (type == 'P')
            {
                pawn p;
                p.set(board, type, i, j, color, 0);
            }
            else if (type == 'N')
            {
                knight n;
                n.set(board, type, i, j, color, 0);
            }
            else if (type == 'R')
            {
                rook r;
                r.set(board, type, i, j, color, 0);
            }
        }
    }
    SetMove(board, 0, -1);
}
