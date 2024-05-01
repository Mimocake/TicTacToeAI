#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#define BLANK 0
#define CROSS 1
#define ZERO 2

#define CROSS_WON 10
#define ZERO_WON 11
#define TIE 12
#define GAME_NOT_OVER 13

using namespace sf;
using namespace std;

int game_situation(const vector<int>& board)
{
    if (board[0] == CROSS && board[1] == CROSS && board[2] == CROSS ||
        board[3] == CROSS && board[4] == CROSS && board[5] == CROSS ||
        board[6] == CROSS && board[7] == CROSS && board[8] == CROSS ||
        board[0] == CROSS && board[3] == CROSS && board[6] == CROSS ||
        board[1] == CROSS && board[4] == CROSS && board[7] == CROSS ||
        board[2] == CROSS && board[5] == CROSS && board[8] == CROSS ||
        board[0] == CROSS && board[4] == CROSS && board[8] == CROSS ||
        board[2] == CROSS && board[4] == CROSS && board[6] == CROSS)
        return CROSS_WON;
    if (board[0] == ZERO && board[1] == ZERO && board[2] == ZERO ||
        board[3] == ZERO && board[4] == ZERO && board[5] == ZERO ||
        board[6] == ZERO && board[7] == ZERO && board[8] == ZERO ||
        board[0] == ZERO && board[3] == ZERO && board[6] == ZERO ||
        board[1] == ZERO && board[4] == ZERO && board[7] == ZERO ||
        board[2] == ZERO && board[5] == ZERO && board[8] == ZERO ||
        board[0] == ZERO && board[4] == ZERO && board[8] == ZERO ||
        board[2] == ZERO && board[4] == ZERO && board[6] == ZERO)
        return ZERO_WON;
    for (auto i : board)
    {
        if (i == BLANK) return GAME_NOT_OVER;
    }
    return TIE;
}

int minimax(vector<int>& board, int alpha, int beta, bool is_zero) 
{
    int gs = game_situation(board);
    if (gs == CROSS_WON) return 1000;
    if (gs == ZERO_WON) return -1000;
    if (gs == TIE) return 0;

    if (is_zero)
    {
        int min_score = 1e9;
        for (int i = 0; i < 9; i++)
        {
            if (board[i] != BLANK) continue;
            vector<int> tmp = board;
            tmp[i] = ZERO;
            int cur_score = minimax(tmp, alpha, beta, false);
            min_score = min(min_score, cur_score);
            beta = min(beta, cur_score);
            if (beta <= alpha) break;
        }
        return min_score;
    }
    else
    {
        int max_score = -1e9;
        for (int i = 0; i < 9; i++)
        {
            if (board[i] != BLANK) continue;
            vector<int> tmp = board;
            tmp[i] = CROSS;
            int cur_score = minimax(tmp, alpha, beta, true);
            max_score = max(max_score, cur_score);
            alpha = max(alpha, cur_score);
            if (beta <= alpha) break;
        }
        return max_score;
    }
}

int main()
{
    RenderWindow window(sf::VideoMode(850, 850), "Tic Tac Toe");
    
    Texture field_tex;
    field_tex.loadFromFile("../image/field.png");
    Sprite field_spr;
    field_spr.setTexture(field_tex);
    
    Texture cross_tex;
    cross_tex.loadFromFile("../image/cross.png");

    Texture zero_tex;
    zero_tex.loadFromFile("../image/zero.png");

    vector<int> board(9, BLANK);
    int cnt = 0;
    bool game_over = false;

    while (window.isOpen())
    {
        int gs = game_situation(board);
        if (gs != GAME_NOT_OVER && !game_over)
        {
            switch (gs)
            {
            case CROSS_WON: cout << "CROSS WON" << endl; break;
            case ZERO_WON: cout << "ZERO WON" << endl; break;
            case TIE: cout << "TIE" << endl; break;
            }
            game_over = true;
        }
        
        if (cnt % 2 == 1)
        {
            int best_move, min_eval = 1e9;
            for (int i = 0; i < 9; i++)
            {
                if (board[i] == BLANK)
                {
                    vector<int> tmp = board;
                    tmp[i] = ZERO;
                    int cur = minimax(tmp, -1e9, 1e9, false);
                    if (cur < min_eval)
                    {
                        min_eval = cur;
                        best_move = i;
                    }
                }
            }
            board[best_move] = ZERO;
            cnt++;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed: window.close(); break;
            case Event::KeyPressed:
                if (event.key.code == Keyboard::R)
                {
                    board = vector<int>(9, BLANK);
                    cnt = 0; game_over = false;
                    system("cls");
                }
                break;
            case Event::MouseButtonPressed:
                if (cnt % 2 == 0)
                {
                    if (game_over) continue;
                    Vector2f ev = Vector2f(event.mouseButton.x < 825 ? event.mouseButton.x : 825,
                        event.mouseButton.y < 825 ? event.mouseButton.y : 825);
                    int index = int((ev.y) / 275) * 3 + int((ev.x) / 275);
                    if (board[index] == BLANK) { board[index] = CROSS; cnt++; }
                }
                break;
            }
        }

        vector<Sprite> sprites(9);
        for (int i = 0; i < 9; i++)
        {
            if (board[i] == CROSS) sprites[i].setTexture(cross_tex);
            if (board[i] == ZERO)  sprites[i].setTexture(zero_tex);
            sprites[i].setPosition(Vector2f(25 + 275 * (i % 3), 25 + 275 * (i / 3)));
        }

        window.clear();
        window.draw(field_spr);
        for (auto i : sprites) window.draw(i);
        window.display();
    }

    return 0;
}