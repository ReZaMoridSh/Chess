#include "chess_setting.cpp"

bool checkmate(Chessboard mateboard, int player)
{
    bool checkmate = true;
    string move;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (mateboard.getcolor(i, j) == player)
            {
                move = mateboard.getmove(i, j);
                for (int k = 0; k < move.length(); k = k + 4)
                {
                    int xm, ym;
                    xm = move[k] - '0';
                    ym = move[k + 2] - '0';
                    if (!Check(mateboard, mateboard.gettype(i, j), i, j, xm, ym, player))
                    {
                        checkmate = false;
                        return checkmate;
                    }
                }
            }
    return checkmate;
}

bool oppenentCheck(Chessboard Board, char type, int x_src, int y_src, int x_dest, int y_dest, int nextplayer)
{
    ChM = Board;
    bool CHECK = false;
    int player = 0;
    (nextplayer == 1) ? player = 2 : player = 1;
    string move;
    moveit(ChM, type, x_src, y_src, x_dest, y_dest, player, -1);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (ChM.getcolor(i, j) == player)
            {
                move = ChM.getmove(i, j);
                for (int k = 0; k < move.length(); k = k + 4)
                {
                    int x, y;
                    x = move[k] - '0';
                    y = move[k + 2] - '0';
                    if (x == ChM.get_king_pos(0, nextplayer) && y == ChM.get_king_pos(1, nextplayer))
                    {
                        CHECK = true;
                        return CHECK;
                    }
                }
            }
        }
    return CHECK;
}

bool Is_Check(Chessboard &Board, int player)
{
    bool CHECK = false;
    int next_player;
    (player == 1) ? next_player = 2 : next_player = 1;
    SetMove(Board, 5, next_player);
    string move;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (Board.getcolor(i, j) == next_player)
            {
                move = Board.getmove(i, j);
                for (int k = 0; k < move.length(); k = k + 4)
                {
                    int x, y;
                    x = move[k] - '0';
                    y = move[k + 2] - '0';
                    if (x == Board.get_king_pos(0, player) && y == Board.get_king_pos(1, player))
                    {
                        CHECK = true;
                        return CHECK;
                    }
                }
            }
        }
    return CHECK;
}

bool mate_in_two_moves(Chessboard &Board, vector<string> &warning, int i, int j, string move, int start)
{
    bool mate = false;
    bool BREAK = false;
    bool BREAK1 = false;
    string Warning_move = "";
    string MovePice2;
    string MovePice3;
    int next_player = 0;
    int num = warning.size();
    (start == 1) ? next_player = 2 : next_player = 1;
    board1 = Board;
    moveit(board1, Board.gettype(i, j), i, j, move[0] - '0', move[2] - '0', Board.getcolor(i, j), 1);
    for (int u = 0; u < 8; u++)
    {
        for (int w = 0; w < 8; w++)
        {
            if (board1.getcolor(u, w) == next_player)
            {
                MovePice2 = board1.getmove(u, w);
                for (int z = 0; z < MovePice2.length(); z = z + 4)
                {
                    board2 = board1;
                    BREAK = false;
                    BREAK1 = false;
                    mate = false;
                    int x2, y2;
                    x2 = MovePice2[z] - '0';
                    y2 = MovePice2[z + 2] - '0';
                    moveit(board2, board1.gettype(u, w), u, w, x2, y2, board1.getcolor(u, w), 2);
                    for (int n = 0; n < 8; n++)
                    {
                        for (int m = 0; m < 8; m++)
                            if (board2.getcolor(n, m) == start)
                            {
                                MovePice3 = board2.getmove(n, m);
                                for (int l = 0; l < MovePice3.length(); l = l + 4)
                                {
                                    board3 = board2;
                                    int x3, y3;
                                    x3 = MovePice3[l] - '0';
                                    y3 = MovePice3[l + 2] - '0';
                                    moveit(board3, board2.gettype(n, m), n, m, x3, y3, board2.getcolor(n, m), 3);
                                    if (!checkmate(board3, next_player))
                                        continue;
                                    if (oppenentCheck(board2, board2.gettype(n, m), n, m, x3, y3, next_player))
                                    {
                                        mate = true;
                                        BREAK = true;
                                        break;
                                    }
                                }
                                if (BREAK)
                                {
                                    BREAK1 = true;
                                    break;
                                }
                            }
                        if (BREAK1)
                            break;
                    }

                    if (!mate)
                        return false;
                }
            }
        }
    }
    num++;
    warning.resize(num);
    char color = '-';
    (board.getcolor(i, j) == 1) ? color = 'B' : (board.getcolor(i, j) == 2) ? color = 'W'
                                                                            : 0;
    Warning_move += char(97 + i);
    Warning_move += char(49 + j);
    Warning_move += board.gettype(i, j);
    Warning_move += color;
    Warning_move += char(97 + move[0] - '0');
    Warning_move += char(49 + move[2] - '0');
    warning.at(num - 1) = Warning_move;
    return true;
}

bool mate_in_one_move(Chessboard &Board, vector<string> &warning, int i, int j, string move, int start)
{
    bool mate = false;
    string warning_move = "";
    int nextplayer = 0;
    (start == 1) ? nextplayer = 2 : nextplayer = 1;
    board1 = Board;
    int num = warning.size();
    int xx, yy;
    xx = move[0] - '0';
    yy = move[2] - '0';
    moveit(board1, Board.gettype(i, j), i, j, xx, yy, start, 1);

    if (!checkmate(board1, nextplayer))
        return false;
    if (oppenentCheck(Board, Board.gettype(i, j), i, j, xx, yy, nextplayer))
    {
        mate = true;
        num++;
        warning.resize(num);
        char color = '-';
        (Board.getcolor(i, j) == 1) ? color = 'B' : (Board.getcolor(i, j) == 2) ? color = 'W'
                                                                                : 0;
        warning_move += char(97 + i);
        warning_move += char(49 + j);
        warning_move += Board.gettype(i, j);
        warning_move += color;
        warning_move += char(97 + xx);
        warning_move += char(49 + yy);
        warning.at(num - 1) = warning_move;
        return mate;
    }
    return mate;
}

bool defense_in_two_moves(Chessboard &Board, vector<string> &warning, int i, int j, string move, int start)
{
    bool mate = false;
    bool br = true;
    int nextplayer;
    (start == 1) ? nextplayer = 2 : nextplayer = 1;
    string warning_move = "";
    int color = 0;
    int num = warning.size();
    board1 = Board;
    int xx, yy;
    xx = move[0] - '0';
    yy = move[2] - '0';
    moveit(board1, Board.gettype(i, j), i, j, xx, yy, Board.getcolor(i, j), 1);
    for (int u = 0; u < 8; u++)
        for (int w = 0; w < 8; w++)
        {
            if (board1.getcolor(u, w) == nextplayer)
            {
                string MovePice2 = board1.getmove(u, w);
                for (int z = 0; z < MovePice2.length(); z = z + 4)
                {
                    bool BREAK = false;
                    br = true;
                    board2 = board1;
                    int x2, y2;
                    x2 = MovePice2[z] - '0';
                    y2 = MovePice2[z + 2] - '0';
                    moveit(board2, board1.gettype(u, w), u, w, x2, y2, board1.getcolor(u, w), 2);
                    for (int n = 0; n < 8; n++)
                    {
                        for (int m = 0; m < 8; m++)
                            if (board2.getcolor(n, m) == start)
                                if (!Can_Oppenent_Mate(n, m, start))
                                {
                                    br = false;
                                    BREAK = true;
                                    break;
                                }
                        if (BREAK)
                            break;
                        ;
                    }
                    if (br)
                    {
                        num++;
                        char color = '-';
                        warning.resize(num);
                        (board.getcolor(i, j) == 1) ? color = 'B' : (board.getcolor(i, j) == 2) ? color = 'W'
                                                                                                : 0;
                        warning_move += char(97 + i);
                        warning_move += char(49 + j);
                        warning_move += Board.gettype(i, j);
                        warning_move += color;
                        warning_move += char(97 + xx);
                        warning_move += char(49 + yy);
                        warning.at(num - 1) = warning_move;

                        return true;
                    }
                }
            }
        }
    return mate;
}

bool defense_in_one_move(Chessboard &Board, vector<string> &warning, int i, int j, string move, int start)
{
    bool mate = false;
    int nextplayer = 0;
    (start == 1) ? nextplayer = 2 : nextplayer = 1;
    string warning_move = "";
    int color = 0;
    board1 = Board;
    int num = warning.size();
    int xx, yy;
    xx = move[0] - '0';
    yy = move[2] - '0';
    moveit(board1, Board.gettype(i, j), i, j, xx, yy, Board.getcolor(i, j), 1);
    for (int u = 0; u < 8; u++)
        for (int w = 0; w < 8; w++)
        {
            if (board1.getcolor(u, w) == nextplayer)
            {

                string MovePice2 = board1.getmove(u, w);
                for (int z = 0; z < MovePice2.length(); z = z + 4)
                {
                    board2 = board1;
                    int x2, y2;
                    x2 = MovePice2[z] - '0';
                    y2 = MovePice2[z + 2] - '0';
                    moveit(board2, board1.gettype(u, w), u, w, x2, y2, board1.getcolor(u, w), 2);
                    if (!checkmate(board2, start))
                        continue;
                    if (oppenentCheck(board1, board1.gettype(u, w), u, w, x2, y2, start))
                    {

                        num++;
                        warning.resize(num);
                        mate = true;
                        char color = '-';
                        (board.getcolor(i, j) == 1) ? color = 'B' : (board.getcolor(i, j) == 2) ? color = 'W'
                                                                                                : 0;
                        warning_move += char(97 + i);
                        warning_move += char(49 + j);
                        warning_move += Board.gettype(i, j);
                        warning_move += color;
                        warning_move += char(97 + xx);
                        warning_move += char(49 + yy);
                        warning.at(num - 1) = warning_move;
                        return mate;
                    }
                }
            }
        }
    return mate;
}

bool Can_Oppenent_Mate(int x, int y, int player)
{
    int nextplayer = 0;
    int win = 0;
    int itr = 0;
    (player == 1) ? nextplayer = 2 : nextplayer = 1;
    string MovePice3 = board2.getmove(x, y);
    for (int i = 0; i < MovePice3.length(); i = i + 4)
    {
        bool BREAK = false;
        bool BREAK1 = false;
        itr++;
        board3 = board2;
        int x3, y3;
        x3 = MovePice3[i] - '0';
        y3 = MovePice3[i + 2] - '0';
        moveit(board3, board2.gettype(x, y), x, y, x3, y3, player, 3);
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 8; k++)
                if (board3.getcolor(j, k) != 0 && board3.getcolor(j, k) != player)
                {
                    string MovePice4 = board3.getmove(j, k);
                    for (int d = 0; d < MovePice4.length(); d = d + 4)
                    {
                        board4 = board3;
                        int x4, y4;
                        x4 = MovePice4[d] - '0';
                        y4 = MovePice4[d + 2] - '0';
                        moveit(board4, board3.gettype(j, k), j, k, x4, y4, board3.getcolor(j, k), 4);
                        if (!checkmate(board4, player))
                            continue;
                        if (oppenentCheck(board3, board3.gettype(j, k), j, k, x4, y4, player))
                        {
                            win++;
                            BREAK = true;
                            break;
                        }
                    }
                    if (BREAK)
                    {
                        BREAK1 = true;
                        break;
                    }
                }
            if (BREAK1)
                break;
        }
    }
    if (win == itr)
        return true;
    else
        return false;
}

string WarningMoveMate(Chessboard &Board, int i, int j, int start)
{

    bool all = true;
    string output = "";
    vector<string> answer;
    string answer_string;
    string MovePice1;
    int num = 0;
    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {
    //         if (board.getcolor(i, j) == start)
    //         {
    MovePice1 = Board.getmove(i, j);
    all = true;
    vector<string> warning_move;
    for (int k = 0; k < MovePice1.length(); k = k + 4)
    {
        if (mate_in_one_move(Board, warning_move, i, j, MovePice1.substr(k, 4), start))
        {
            answer_string += MovePice1.substr(k, 4);
            cout<<MovePice1.substr(k, 4)<<endl;
            continue;
        }
        else if (mate_in_two_moves(Board, warning_move, i, j, MovePice1.substr(k, 4), start))
        {
            answer_string += MovePice1.substr(k, 4);
            // cout<<MovePice1.substr(k, 4)<<endl;
            continue;
        }
        else
        {
            all = false;
        }
    }
    // if (all && warning_move.size() != 0)
    // {
    //     num++;
    //     answer.resize(num);
    //     char color;
    //     (board.getcolor(i, j) == 1) ? color = 'B' : (board.getcolor(i, j) == 2) ? color = 'W'
    //                                                                             : 0;
    //     output += char(97 + i);
    //     output += char(49 + j);
    //     output += board.gettype(i, j);
    //     output += color;
    //     answer.at(num - 1) = output;

    //     output = "";
    // }
    // if (warning_move.size() != 0)
    // {
    //     answer.insert(answer.end(), warning_move.begin(), warning_move.end());
    //     num = answer.size();
    // }
    //         }
    //     }
    // }
    return answer_string;
}

string WarningMoveDefense(Chessboard &Board, int i, int j, int start)
{
    string output = "";
    vector<string> answer;
    string answer_string;
    string MovePice1;
    int num = 0;
    // bool all = true;
    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {
    // if (Board.getcolor(i, j) == start)
    // {
    MovePice1 = Board.getmove(i, j);
    // all = true;
    vector<string> warning_move;
    for (int k = 0; k < MovePice1.length(); k = k + 4)
    {
        if (defense_in_one_move(Board, warning_move, i, j, MovePice1.substr(k, 4), start))
        {
            answer_string += MovePice1.substr(k, 4);
            continue;
        }
        else if (defense_in_two_moves(Board, warning_move, i, j, MovePice1.substr(k, 4), start))
        {
            answer_string += MovePice1.substr(k, 4);
            continue;
        }
        // else
        //     all = false;
    }
    // if (all && warning_move.size() != 0)
    // {

    //     num++;
    //     answer.resize(num);
    //     char color = '-';
    //     (Board.getcolor(i, j) == 1) ? color = 'B' : (Board.getcolor(i, j) == 2) ? color = 'W'
    //                                                                             : 0;
    //     output += char(97 + i);
    //     output += char(49 + j);
    //     output += board.gettype(i, j);
    //     output += color;
    //     answer.at(num - 1) = output;

    //     output = "";
    // }
    // else if (warning_move.size() != 0)
    // {
    //     answer.insert(answer.end(), warning_move.begin(), warning_move.end());
    //     num = answer.size();
    // }
    //     }
    // }
    // }
    return answer_string;
}
