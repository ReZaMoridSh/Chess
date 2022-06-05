#include "../include/analyze.cpp"
#include "../include/setting.cpp"
#include "../include/print.cpp"
void restart()
{
    for (int i = 0; i < 8; i++)
    {
        pawn p1;
        p1.set(CurrentBoard, 'P', i, 1, 2, 5);
        pawn p2;
        p2.set(CurrentBoard, 'P', i, 6, 1, 5);
    }
    king kw;
    kw.set(CurrentBoard, 'K', 4, 0, 2, 5);
    king kb;
    kb.set(CurrentBoard, 'K', 4, 7, 1, 5);
    queen qw;
    qw.set(CurrentBoard, 'Q', 3, 0, 2, 5);
    queen qb;
    qb.set(CurrentBoard, 'Q', 3, 7, 1, 5);
    rook rw1;
    rw1.set(CurrentBoard, 'R', 0, 0, 2, 5);
    rook rw2;
    rw2.set(CurrentBoard, 'R', 7, 0, 2, 5);
    rook rb1;
    rb1.set(CurrentBoard, 'R', 0, 7, 1, 5);
    rook rb2;
    rb2.set(CurrentBoard, 'R', 7, 7, 1, 5);
    bishop bw1;
    bw1.set(CurrentBoard, 'B', 2, 0, 2, 5);
    bishop bw2;
    bw2.set(CurrentBoard, 'B', 5, 0, 2, 5);
    bishop bb1;
    bb1.set(CurrentBoard, 'B', 2, 7, 1, 5);
    bishop bb2;
    bb2.set(CurrentBoard, 'B', 5, 7, 1, 5);
    knight nw1;
    nw1.set(CurrentBoard, 'N', 1, 0, 2, 5);
    knight nw2;
    nw2.set(CurrentBoard, 'N', 6, 0, 2, 5);
    knight nb1;
    nb1.set(CurrentBoard, 'N', 1, 7, 1, 5);
    knight nb2;
    nb2.set(CurrentBoard, 'N', 6, 7, 1, 5);

    SetMove(CurrentBoard, 5, 2);
}

void render(sf::RenderWindow &window)
{
    string path = "../resources/";
    Texture tx;
    tx.loadFromFile(path + "images/" + "bg.jpg");
    Sprite sp;
    sp.setTexture(tx);
    sp.setOrigin(0, 0);
    sp.setScale(2, 2.125);
    restart();
    Cells cells;
    setting set;

    int r, c;

    while (window.isOpen())
    {
        window.clear(Color::Black);
        window.draw(sp);


        cells.resize(8);
        for (int row = 0; row < 8; row++)
        {
            cells[row].resize(8);
            for (int col = 0; col < 8; col++)
            {
                cells[row][col].rect.setSize(Vector2f(90, 90));
                cells[row][col].rect.setFillColor(cell_color(row, col));
                cells[row][col].rect.setPosition(set.get_cell_position(row, col));
                window.draw(cells[row][col].rect);
            }
        }

        
        for (int row = 0; row < 8; row++)
            for (int col = 0; col < 8; col++)
            {
                if (CurrentBoard.getoccupied(row, col))
                {
                    Sprite sprite;
                    Texture txt;
                    string Path = path + "images/";
                    Path += CurrentBoard.gettype(row, col);
                    Path += (CurrentBoard.getcolor(row, col) == 1) ? "B" : "W";
                    Path += ".png";
                    txt.loadFromFile(Path);
                    txt.setSmooth(true);
                    sprite.setPosition(set.get_cell_position(row, col));
                    sprite.setTexture(txt);
                    float piece_scale_x = (float)set.cell_size / sprite.getTexture()->getSize().x;
                    float piece_scale_y = (float)set.cell_size / sprite.getTexture()->getSize().y;
                    sprite.setScale(piece_scale_x, piece_scale_y);
                    window.draw(sprite);
                }
            }
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::EventType::Closed)
            {
                
                window.close();
                
            }



        }


        window.display();
    }
}