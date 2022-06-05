#include "Chessboard.cpp"

void printboard(Chessboard board)
{
    char null;
    char type;
    for (int i = 7; i > -1; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            char color;
            if (board.getcolor(j, i) == 1)
            {
                color = 'B';
            }
            else if (board.getcolor(j, i) == 2)
            {
                color = 'W';
            }
            else
                color = '-';
            if (board.gettype(j, i) == null)
                type = '-';
            else
                type = board.gettype(j, i);
            cout << type << color << "   ";
        }
        cout << std::endl
             << std::endl;
        ;
    }
}