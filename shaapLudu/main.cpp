//
//  main.cpp
//  shaapLudu
//
//  Created by Md Reshad Bin Harun on 5/11/18.
//  Copyright © 2018 Md Reshad Bin Harun. All rights reserved.
//

#include <iostream>
#include <vector>
#include <utility> //to include pair
#include <cstdlib> //to include random number
#include <ctime>
#include <cmath>
using namespace std;

/*
 ladders: 4->14, 9->31, 19->38, 21->42, 28->84, 51->67, 71->91, 80->100
 snakes: 98->79, 95->75, 93->73, 64->60, 62->19, 17->7, 87->24
 potential handles: loaded die, snake count, ladder count
*/

/*
 To do:
Populate board with snakes!
 
 CLASSES
 
 Board:
 --> move: takes a die roll outcome, and a player object and updates position on board
 --> display: displays board
 --> initializes board
 Snake:
 --> randomly makes valid snakes
 --> make snakes:
    * contain board_size number of snakes
    * floor(board_size*.2) will span board_size/2 rows, floor(board_size*.5) will span board_size/4,
        floor(board_size*.3) will span board_size/8 rows
    * checks when putting a snake on board
        - is head/ tail out of bound
        - is position already occupied
 Ladder:
 Player:
 --> stores coordinates of position, and string id
 --> rolls die
 */


//vector<Snake> snakes;
enum snakeSize {big = 1, medium, small};

class Board {
public:
    Board(int size_b);
    int get_board_size();
    vector<vector<string>> get_board();
private:
    vector<vector <string>> board;
    int board_size;
};

Board::Board(int size_b){
    board_size = size_b;
    vector<vector <string>> temp_board(board_size, vector<string>(board_size));
    for(int i = 0; i < board_size; i++){
        for (int j = 0; j < board_size; j++){
            temp_board[i][j] = to_string(board_size*i+j);
            cout << temp_board[i][j] << " ";
        }
        cout << endl;
    }
    board = temp_board;
}

int Board::get_board_size(){
    return board_size;
}

vector<vector<string>> Board::get_board(){
    return board;
}

class Snake {
public:
    Snake(int x1, int x2, int y1, int y2, string h, string t);
    Snake();
    vector <int> make_snake(Board board, snakeSize span);
    bool isValidPos(int x, int y, Board board);
private:
    int eat_pos_x, eat_pos_y, poo_pos_x, poo_pos_y;
    string head, tail;
};

Snake::Snake(){
    //empty constructor
}

Snake::Snake(int x1, int y1, int x2, int y2, string h, string t){
    eat_pos_x = x1;
    eat_pos_y = y1;
    poo_pos_x = x2;
    poo_pos_y = y2;
    head = h;
    tail = h;
}

vector <int> Snake::make_snake(Board board, snakeSize span){
    int snake_span = 0;
    int bord_sze = board.get_board_size();
    if (span == big){
        snake_span = bord_sze/2;
    } else if (span == medium){
        snake_span = bord_sze/4;
    }
    else{
        snake_span = bord_sze/8;
    }
        //pick head from last half

        srand((unsigned)time(0));
        int tail_x, tail_y, head_x, head_y;
        do{
            tail_x = rand() % bord_sze;
            head_x = (tail_x + (snake_span)) % bord_sze;
            tail_y = rand() % bord_sze;
            head_y = rand() % bord_sze;
        } while (!isValidPos(tail_x, tail_y, board) && !isValidPos(head_x, head_y, board));
    cout << bord_sze << endl;
    cout << tail_x << " " << tail_y << " " << head_x << " " << head_y << " " << endl;
    return {tail_x, tail_y, head_x, head_y};
    //make head
    //make tail
}

bool Snake::isValidPos(int x, int y, Board board){
    int board_size = board.get_board_size();
    vector <vector <string>> bord = board.get_board();
    if (x <= board_size && y <= board_size && (("0" <= bord[x][y])||(bord[x][y]) <= to_string(board_size*board_size-1)) ) return true;
    return false;
}

int main() {
    Board b(10);
    Snake s;
    vector <int> test = s.make_snake(b, big);
    return 0;
}
