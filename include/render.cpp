#include "analyze.cpp"
#include "setting.cpp"

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
    string path="resources/";
    Texture tx;
    tx.loadFromFile(path + "images/" + "bg1.jpg");
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
    font.loadFromFile(path + "fonts/" + "Impact.ttf");
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

    Texture mode;
    mode.loadFromFile(path + "images/" + "mode.png");
    mode.setSmooth(true);
    Sprite M;
    M.setTexture(mode);
    M.setPosition(Vector2f(830, 415));
    M.setScale(Vector2f(0.086, 0.08));
    Text Mode;
    Mode.setString("Set Your Board");
    Mode.setPosition(835, 565);
    Mode.setFont(font);
    Mode.setScale(Vector2f(.8, .8));

    Texture s;
    s.loadFromFile(path + "images/" + "start.png");
    s.setSmooth(true);
    Sprite start;
    start.setTexture(s);
    start.setPosition(Vector2f(1035, 410));
    start.setScale(Vector2f(0.33, 0.33));

    RectangleShape switch_turn;
    switch_turn.setSize(Vector2f(250, 50));
    switch_turn.setPosition(875, 620);
    Text Switch;
    Switch.setFont(font);
    Switch.setScale(1, 1);
    Switch.setPosition(915, 630);
    Switch.setString("White's Turn");
    Switch.setFillColor(Color::Black);

    Text text;
    Font f;
    f.loadFromFile(path + "fonts/" + "Terserah.otf");
    text.setFont(f);
    text.setFillColor(Color::White);
    text.setOutlineThickness(5);
    text.setOutlineColor(Color(138,0,0));
    text.setScale(2, 2);
    text.setPosition(840, 70);

    Texture white_king;
    white_king.loadFromFile(path + "images/" + "KW.png");
    white_king.setSmooth(true);
    Sprite KW;
    KW.setTexture(white_king);
    KW.setPosition(830, 700);
    RectangleShape kw;
    kw.setSize(Vector2f(60, 60));
    kw.setPosition(835, 705);

    Texture black_king;
    black_king.loadFromFile(path + "images/" + "KB.png");
    black_king.setSmooth(true);
    Sprite KB;
    KB.setTexture(black_king);
    KB.setPosition(830, 760);
    RectangleShape kb;
    kb.setSize(Vector2f(60, 60));
    kb.setPosition(835, 765);

    Texture white_queen;
    white_queen.loadFromFile(path + "images/" + "QW.png");
    white_queen.setSmooth(true);
    Sprite QW;
    QW.setTexture(white_queen);
    QW.setPosition(890, 700);
    RectangleShape qw;
    qw.setSize(Vector2f(60, 60));
    qw.setPosition(895, 705);

    Texture black_queen;
    black_queen.loadFromFile(path + "images/" + "QB.png");
    black_queen.setSmooth(true);
    Sprite QB;
    QB.setTexture(black_queen);
    QB.setPosition(890, 760);
    RectangleShape qb;
    qb.setSize(Vector2f(60, 60));
    qb.setPosition(895, 765);

    Texture white_rook;
    white_rook.loadFromFile(path + "images/" + "RW.png");
    white_rook.setSmooth(true);
    Sprite RW;
    RW.setTexture(white_rook);
    RW.setPosition(950, 700);
    RectangleShape rw;
    rw.setSize(Vector2f(60, 60));
    rw.setPosition(955, 705);

    Texture black_rook;
    black_rook.loadFromFile(path + "images/" + "RB.png");
    black_rook.setSmooth(true);
    Sprite RB;
    RB.setTexture(black_rook);
    RB.setPosition(950, 760);
    RectangleShape rb;
    rb.setSize(Vector2f(60, 60));
    rb.setPosition(955, 765);

    Texture white_knight;
    white_knight.loadFromFile(path + "images/" + "NW.png");
    white_knight.setSmooth(true);
    Sprite NW;
    NW.setTexture(white_knight);
    NW.setPosition(1010, 700);
    RectangleShape nw;
    nw.setSize(Vector2f(60, 60));
    nw.setPosition(1015, 705);

    Texture black_knight;
    black_knight.loadFromFile(path + "images/" + "NB.png");
    black_knight.setSmooth(true);
    Sprite NB;
    NB.setTexture(black_knight);
    NB.setPosition(1010, 760);
    RectangleShape nb;
    nb.setSize(Vector2f(60, 60));
    nb.setPosition(1015, 765);

    Texture white_bishop;
    white_bishop.loadFromFile(path + "images/" + "BW.png");
    white_bishop.setSmooth(true);
    Sprite BW;
    BW.setTexture(white_bishop);
    BW.setPosition(1070, 700);
    RectangleShape bw;
    bw.setSize(Vector2f(60, 60));
    bw.setPosition(1075, 705);

    Texture black_bishop;
    black_bishop.loadFromFile(path + "images/" + "BB.png");
    black_bishop.setSmooth(true);
    Sprite BB;
    BB.setTexture(black_bishop);
    BB.setPosition(1070, 760);
    RectangleShape bb;
    bb.setSize(Vector2f(60, 60));
    bb.setPosition(1075, 765);

    Texture white_pawn;
    white_pawn.loadFromFile(path + "images/" + "PW.png");
    white_pawn.setSmooth(true);
    Sprite PW;
    PW.setTexture(white_pawn);
    PW.setPosition(1130, 700);
    RectangleShape pw;
    pw.setSize(Vector2f(60, 60));
    pw.setPosition(1135, 705);

    Texture black_pawn;
    black_pawn.loadFromFile(path + "images/" + "PB.png");
    black_pawn.setSmooth(true);
    Sprite PB;
    PB.setTexture(black_pawn);
    PB.setPosition(1130, 755);
    RectangleShape pb;
    pb.setSize(Vector2f(60, 60));
    pb.setPosition(1135, 765);

    static bool clicked;
    static bool IS_CHECK;
    static bool IS_CHECKMATE=false;
    static string amove;
    static bool warn;
    static string defense_warn;
    static string mate_warn;
    static bool new_board;
    static bool select_piece;
    static bool choose;
    int r, c, px, py;
    char type;

    while (window.isOpen())
    {
        window.clear(Color::Black);
        window.draw(sp);
        window.draw(analyze_rect);
        window.draw(def);
        window.draw(anz);
        window.draw(text);
        window.draw(M);
        window.draw(rs);
        window.draw(R);
        window.draw(Mode);

        if (new_board)
        {
            window.draw(start);
            window.draw(switch_turn);
            window.draw(Switch);
            window.draw(kw);
            window.draw(KW);
            window.draw(kb);
            window.draw(KB);
            window.draw(qw);
            window.draw(QW);
            window.draw(qb);
            window.draw(QB);
            window.draw(rw);
            window.draw(RW);
            window.draw(rb);
            window.draw(RB);
            window.draw(nw);
            window.draw(NW);
            window.draw(nb);
            window.draw(NB);
            window.draw(bw);
            window.draw(BW);
            window.draw(bb);
            window.draw(BB);
            window.draw(pw);
            window.draw(PW);
            window.draw(pb);
            window.draw(PB);
        }

        if (!choose)
        {
            kw.setFillColor(Color(64, 64, 64));
            kb.setFillColor(Color(64, 64, 64));
            qw.setFillColor(Color(64, 64, 64));
            qb.setFillColor(Color(64, 64, 64));
            rw.setFillColor(Color(64, 64, 64));
            rb.setFillColor(Color(64, 64, 64));
            nw.setFillColor(Color(64, 64, 64));
            nb.setFillColor(Color(64, 64, 64));
            bw.setFillColor(Color(64, 64, 64));
            bb.setFillColor(Color(64, 64, 64));
            pw.setFillColor(Color(64, 64, 64));
            pb.setFillColor(Color(64, 64, 64));
        }

        (set.Turn == 2 and !IS_CHECKMATE and !new_board) ? text.setString("White's Turn") : text.setString("Black's Turn");
        if (new_board)
            text.setString("Make a Board");

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
            (set.Turn == 1 and !new_board) ? text.setString("White wins !!") : text.setString("Black wins !!");
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
            switch (event.type)
            {
            case Event::EventType::Closed:
                if (event.type == Event::EventType::Closed)
                {
                    window.close();
                }
                break;
            case Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    int mouse_x = event.mouseButton.x;
                    int mouse_y = event.mouseButton.y;
                    if (mouse_x > 830 && mouse_x < 990 && mouse_y > 415 && mouse_y < 565)
                    {
                        IS_CHECK = false;
                        IS_CHECKMATE = false;
                        new_board = true;
                        CurrentBoard = empty;
                    }

                    if (new_board)
                    {
                        if (mouse_x > 875 && mouse_x < 1125 && mouse_y > 620 && mouse_y < 670)
                        {
                            set.flipturn();
                            Color col;
                            if (set.Turn == 1)
                            {
                                col = Color(51, 51, 51);
                                Switch.setFillColor(Color::White);
                                Switch.setString("Black's Turn");
                            }
                            else
                            {
                                col = Color(240, 240, 240);
                                Switch.setFillColor(Color::Black);
                                Switch.setString("White's Turn");
                            }
                            switch_turn.setFillColor(col);
                        }
                    }

                    if (clicked)
                    {
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

                    if (!select_piece)
                    {
                        if (clicked && mouse_x < set.cell_offset + 8 * set.cell_size && mouse_x > set.cell_offset && mouse_y < set.cell_offset + 8 * set.cell_size && mouse_y > set.cell_offset)
                        {
                            clicked=false;
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
                        }
                        if (!clicked && mouse_x < set.cell_offset + 8 * set.cell_size && mouse_x > set.cell_offset && mouse_y < set.cell_offset + 8 * set.cell_size && mouse_y > set.cell_offset)
                        {
                            r = (mouse_x - set.cell_offset) / (set.cell_size);
                            c = 7 - (mouse_y - set.cell_offset) / (set.cell_size);
                            if (CurrentBoard.getoccupied(r, c) and set.your_turn(r, c) and CurrentBoard.getmove(r, c).length() > 0)
                                clicked = true;
                            amove = CurrentBoard.getmove(r, c);
                        }
                        else if (!warn)
                            clicked = false;
                    }

                    if (new_board && CurrentBoard.get_king_pos(0, 1) != -1 && CurrentBoard.get_king_pos(0, 2) != -1)
                    {
                        if (mouse_x > 1040 and mouse_x < 1190 && mouse_y > 415 && mouse_y < 565)
                        {
                            new_board = false;
                            select_piece = false;
                            SetMove(CurrentBoard, 5, -1);
                            if (checkmate(CurrentBoard,set.Turn))
                                IS_CHECKMATE=true;
                            if(Is_Check(CurrentBoard,set.Turn) && !IS_CHECKMATE)
                                IS_CHECK=true;
                        }
                    }

                    if (!clicked && mouse_x > 830 && mouse_x < 990 && mouse_y > 220 && mouse_y < 370)
                    {
                        CurrentBoard = empty;
                        new_board = false;
                        IS_CHECK = false;
                        IS_CHECKMATE = false;
                        restart();
                        set.Turn = 2;
                    }



                    if (select_piece)
                    {
                        select_piece = false;
                        if (mouse_x < set.cell_offset + 8 * set.cell_size && mouse_x > set.cell_offset && mouse_y < set.cell_offset + 8 * set.cell_size && mouse_y > set.cell_offset)
                        {
                            int r2 = (mouse_x - set.cell_offset) / (set.cell_size);
                            int c2 = 7 - (mouse_y - set.cell_offset) / (set.cell_size);
                            CurrentBoard.setcolor(r2, c2, py + 1);
                            CurrentBoard.setoccupied(r2, c2, py + 1, true);
                            CurrentBoard.settype(r2, c2, py + 1, type);
                            if (type == 'K')
                            {
                                int king_x = CurrentBoard.get_king_pos(0, py + 1);
                                int king_y = CurrentBoard.get_king_pos(1, py + 1);
                                if (king_x != -1)
                                {
                                    Null n;
                                    n.set(CurrentBoard, type, king_x, king_y, 0, 5);
                                }
                                CurrentBoard.set_king_pos(r2, c2, py + 1);
                            }
                        }
                    }

                    if (new_board && mouse_x > 830 && mouse_x < 1200 && mouse_y > 700 && mouse_y < 830)
                    {
                        select_piece = true;
                        px = (mouse_x - 830) / 60;
                        py = 1 - (mouse_y - 700) / 65;

                        switch (px)
                        {
                        case 0:
                            type = 'K';
                            (py == 0) ? kb.setFillColor(Color(131, 122, 122)) : kw.setFillColor(Color(131, 122, 122));
                            break;
                        case 1:
                            type = 'Q';
                            (py == 0) ? qb.setFillColor(Color(131, 122, 122)) : qw.setFillColor(Color(131, 122, 122));
                            break;
                        case 2:
                            type = 'R';
                            (py == 0) ? rb.setFillColor(Color(131, 122, 122)) : rw.setFillColor(Color(131, 122, 122));
                            break;
                        case 3:
                            type = 'N';
                            (py == 0) ? nb.setFillColor(Color(131, 122, 122)) : nw.setFillColor(Color(131, 122, 122));
                            break;
                        case 4:
                            type = 'B';
                            (py == 0) ? bb.setFillColor(Color(131, 122, 122)) : bw.setFillColor(Color(131, 122, 122));
                            break;
                        case 5:
                            type = 'P';
                            (py == 0) ? pb.setFillColor(Color(131, 122, 122)) : pw.setFillColor(Color(131, 122, 122));
                            break;
                        }
                    }
                }
            }
            break;
            }
        }

        window.display();
    }
}