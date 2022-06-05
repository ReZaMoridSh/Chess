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

    Texture analyze;
    analyze.loadFromFile(path + "images/" + "Analyze.png");
    analyze.setSmooth(true);
    Sprite anz;
    anz.setTexture(analyze);
    anz.setPosition(Vector2f(1040, 220));
    anz.setScale(Vector2f(0.158, 0.158));
    RectangleShape analyze_rect;
    analyze_rect.setSize(Vector2f(152, 152));
    analyze_rect.setPosition(1040, 220);
    Text def;
    Font font;
    font.loadFromFile(path + "fonts/" +"Impact.ttf");
    def.setFont(font);
    def.setScale(Vector2f(.8, .8));



    Texture Restart;
    Restart.loadFromFile(path + "images/" + "restart.png");
    Restart.setSmooth(true);
    Sprite rs;
    rs.setTexture(Restart);
    rs.setPosition(Vector2f(830, 220));
    rs.setScale(Vector2f(0.3, 0.3));
    Text R;
    R.setString("Restart Game");
    R.setPosition(840, 380);
    R.setFont(font);
    R.setScale(Vector2f(.8, .8));








    Text text;
    Font f;
    f.loadFromFile(path + "fonts/" +"Terserah.otf");
    text.setFont(f);
    text.setFillColor(Color::White);
    text.setOutlineThickness(5);
    text.setOutlineColor(Color(131,122,122));
    text.setScale(2,2);
    text.setPosition(840, 70);



    


    static bool clicked;
    static bool IS_CHECK;
    static bool IS_CHECKMATE;
    static string amove;
    static bool warn;
    static string defense_warn;
    static string mate_warn;
    int r, c,px,py;
    char type;

    while (window.isOpen())
    {
        window.clear(Color::Black);
        window.draw(sp);
        window.draw(analyze_rect);
        window.draw(def);
        window.draw(anz);
        window.draw(text);
        window.draw(rs);
        window.draw(R);


        (set.Turn==2 and !IS_CHECKMATE )?text.setString("White's Turn"):text.setString("Black's Turn");

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

        if (clicked)
        {
            anz.setColor(Color::White);
            analyze_rect.setFillColor(Color(37, 183, 211));
            def.setFillColor(Color::White);
            def.setString("Start Analyze");
            def.setPosition(1050, 380);
            for (int m = 0; m < amove.length(); m = m + 4)
            {
                int X_dest = amove[m] - '0';
                int Y_dest = amove[m + 2] - '0';
                if (!CurrentBoard.getoccupied(X_dest, Y_dest))
                {
                    CircleShape circle;
                    circle.setRadius(12);
                    circle.setFillColor(Color(12, 152, 5));
                    circle.setPosition(set.set_cicle_position(X_dest, Y_dest));
                    window.draw(circle);
                }
                else
                {
                    RectangleShape rec;
                    rec.setSize(Vector2f(70, 10));
                    rec.setFillColor(Color(2, 152, 5));
                    rec.setPosition(set.set_rec_position(X_dest, Y_dest));
                    window.draw(rec);
                }
            }
        }
        else
        {
            anz.setColor(Color(95, 95, 95));
            analyze_rect.setFillColor(Color(14, 68, 79));
            def.setFillColor(Color(80, 80, 80));
            def.setString("Select a piece");
            def.setPosition(1045, 380);
        }
        if (IS_CHECKMATE)
        {
            (set.Turn==1 )?text.setString("White wins !!"):text.setString("Black wins !!");
            int king_x = CurrentBoard.get_king_pos(0, set.Turn);
            int king_y = CurrentBoard.get_king_pos(1, set.Turn);
            cells[king_x][king_y].rect.setFillColor(Color(199, 0, 57));
            window.draw(cells[king_x][king_y].rect);
        }

        if (IS_CHECK and !IS_CHECKMATE)
        {
            int king_x = CurrentBoard.get_king_pos(0, set.Turn);
            int king_y = CurrentBoard.get_king_pos(1, set.Turn);
            CircleShape c;
            c.setRadius(45);
            c.setFillColor(Color(250, 110, 90));
            c.setPosition(set.set_cicle2_position(king_x, king_y));
            window.draw(c);
        }
        if (warn)
        {
            def.setString("Done !");
            anz.setColor(Color(0, 255, 0));
            analyze_rect.setFillColor(Color(0, 183, 0));
            def.setFillColor(Color::White);
            def.setPosition(1080, 380);
            for (int w = 0; w < defense_warn.length(); w = w + 4)
            {
                int X_dest = defense_warn[w] - '0';
                int Y_dest = defense_warn[w + 2] - '0';
                if (!CurrentBoard.getoccupied(X_dest, Y_dest))
                {
                    CircleShape circle;
                    circle.setRadius(12);
                    circle.setFillColor(Color::Red);
                    circle.setPosition(set.set_cicle_position(X_dest, Y_dest));
                    window.draw(circle);
                }
                else
                {
                    RectangleShape rec;
                    rec.setSize(Vector2f(70, 10));
                    rec.setFillColor(Color::Red);
                    rec.setPosition(set.set_rec_position(X_dest, Y_dest));
                    window.draw(rec);
                }
            }

            for (int w = 0; w < mate_warn.length(); w = w + 4)
            {
                int X_dest = mate_warn[w] - '0';
                int Y_dest = mate_warn[w + 2] - '0';
                if (!CurrentBoard.getoccupied(X_dest, Y_dest))
                {
                    CircleShape circle;
                    circle.setRadius(12);
                    circle.setFillColor(Color::Blue);
                    circle.setPosition(set.set_cicle_position(X_dest, Y_dest));
                    window.draw(circle);
                }
                else
                {
                    RectangleShape rec;
                    rec.setSize(Vector2f(70, 10));
                    rec.setFillColor(Color::Blue);
                    rec.setPosition(set.set_rec_position(X_dest, Y_dest));
                    window.draw(rec);
                }
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



            

            if (event.mouseButton.button == Mouse::Left and clicked)
            {
                int mouse_x = event.mouseButton.x;
                int mouse_y = event.mouseButton.y;
                if (mouse_x > 1040 and mouse_x < 1190 and mouse_y > 220 and mouse_y < 370)
                {
                    if (CurrentBoard.getmove(r, c).length() > 0)
                    {
                        defense_warn = WarningMoveDefense(CurrentBoard, r, c, set.Turn);
                        mate_warn = WarningMoveMate(CurrentBoard, r, c, set.Turn);
                        warn = true;
                    }
                    else
                        clicked = false;
                }
                else
                    warn = false;
                // else clicked=false;
            }

            if (event.mouseButton.button == Mouse::Left && clicked)
            {
                int mouse_x = event.mouseButton.x;
                int mouse_y = event.mouseButton.y;
                if (mouse_x < set.cell_offset + 8 * set.cell_size && mouse_x > set.cell_offset && mouse_y < set.cell_offset + 8 * set.cell_size && mouse_y > set.cell_offset)
                {
                    int r2 = (mouse_x - set.cell_offset) / (set.cell_size);
                    int c2 = 7 - (mouse_y - set.cell_offset) / (set.cell_size);
                    for (int a = 0; a < amove.length(); a = a + 4)
                        if (r2 == amove[a] - '0' and c2 == amove[a + 2] - '0' and set.your_turn(r, c))
                        {

                            moveit(CurrentBoard, CurrentBoard.gettype(r, c), r, c, r2, c2, CurrentBoard.getcolor(r, c), 5);

                            set.flipturn();

                            if (Is_Check(CurrentBoard, set.Turn))
                                IS_CHECK = true;
                            else
                                IS_CHECK = false;

                            if (checkmate(CurrentBoard, set.Turn))
                                IS_CHECKMATE = true;
                        }
                        else
                            warn = false;
                    clicked = false;
                }
                else if (!warn)
                    clicked = false;
            }

            if (event.mouseButton.button == Mouse::Left && !clicked)
            {
                int mouse_x = event.mouseButton.x;
                int mouse_y = event.mouseButton.y;
                if (mouse_x < set.cell_offset + 8 * set.cell_size && mouse_x > set.cell_offset && mouse_y < set.cell_offset + 8 * set.cell_size && mouse_y > set.cell_offset)
                {
                    r = (mouse_x - set.cell_offset) / (set.cell_size);
                    c = 7 - (mouse_y - set.cell_offset) / (set.cell_size);
                    if (CurrentBoard.getoccupied(r, c) and set.your_turn(r, c) and CurrentBoard.getmove(r, c).length() > 0)
                        clicked = true;
                    amove = CurrentBoard.getmove(r, c);
                }
                else
                    clicked = false;
            }

            if (event.mouseButton.button == Mouse::Left && !clicked)
            {
                int mouse_x = event.mouseButton.x;
                int mouse_y = event.mouseButton.y;
                if (mouse_x >830  && mouse_x <990  && mouse_y > 220 && mouse_y < 370)
                {
                    CurrentBoard=empty;
                    IS_CHECK=false;
                    IS_CHECKMATE=false;
                    restart();
                    set.Turn=2;
                }
            }


        }


        window.display();
    }
}