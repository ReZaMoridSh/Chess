#include "Chessboard.cpp"

bool Check(Chessboard Board, char type, int x_src, int y_src, int x_dest, int y_dest, int player);
void printboard(Chessboard board);
void SetMove(Chessboard &boardhandle, int boardnum, int player);
void moveit(Chessboard &boardhandle, char type, int x_src, int y_src, int x_dest, int y_dest, int color, int boardnum);
bool defense_in_one_move(Chessboard& Board,string &str, int x, int y, string move, int start);
bool mate_in_one_move(string &str, int i, int j, string move, int start);
bool defense_in_two_moves(Chessboard & Board,string &str, int i, int j, string move, int start);
bool mate_in_two_moves(string &str, int i, int j, string move, int start);
bool Can_Oppenent_Mate(int x, int y, int player);
bool checkmate(Chessboard mateboard, int player);
void setboard();
void restart();
string WarningMoveMate(int start);
string WarningMoveDefense(Chessboard & Board,int i,int j,int start);
bool oppenentCheck(Chessboard Board, char type, int x_src, int y_src, int x_dest, int y_dest, int nextplayer);
