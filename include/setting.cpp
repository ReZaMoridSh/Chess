#include <SFML/Graphics.hpp>
#include "Chessboard.cpp"
using namespace sf;
class setting 
{
public:
    int cell_size = 90;
    int cell_offset = 50;
    int line_space = 0;
    int Turn=2;
    sf::Vector2f get_cell_position(int row,int column)
    {
    return sf::Vector2f(
        cell_offset + (row) * ( cell_size + line_space),
        cell_offset + (7-column )* ( cell_size + line_space));
    }

    sf::Vector2f set_cicle_position(int row,int column)
    {
        Vector2f position= get_cell_position(row,column);
        position.x=position.x+32;
        position.y=position.y+32;
        return position;
    }

    sf::Vector2f set_cicle2_position(int row,int column)
    {
        Vector2f position= get_cell_position(row,column);
        position.x=position.x;
        position.y=position.y;
        return position;
    }

    sf::Vector2f set_rec_position(int row,int column)
    {
        Vector2f position= get_cell_position(row,column);
        position.x=position.x+10;
        position.y=position.y+80;
        return position;
    }


    bool your_turn(int x, int y)
    {
        if(CurrentBoard.getcolor(x,y)==Turn)
            return true;
        return false;
    }

    void flipturn()
    {
        (Turn==2)?Turn=1:Turn=2;
    }
};


class Piece : public setting
{
public:
    Texture texture;
    Sprite sprite;
    void load_texture(char type ,int color);
};


class Cell:setting
{
public:
    sf::RectangleShape rect;
    Piece *piece ;

};



sf::Color cell_color(int row,int col)
{
    if((row+col)%2==0)
        return (Color(187,135,96));
    else return (Color(242,219,178));
}

typedef typename std::vector<std::vector<Cell>> Cells;
