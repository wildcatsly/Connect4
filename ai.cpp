#include "ai.h"
#include "board.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <sstream>
#include <utility>
#include <limits>
#include <algorithm>
#include <vector>
using namespace std;

// infinity 
//vector<int>
//int a[]
const double INF = numeric_limits<double>::infinity();

// two level, only consider (NUM_FOR_WIN - 1, NUM_FOR_WIN - 2)
// as heuristic value
const int HEURISTIC_LEVEL = 3;

// minimax algorithm level, high level take more time
const int MINIMAX_LEVEL = 5;

// return a copy of board
// wh
Board copy_board(const Board &board) {
    //we need to have a buffer for the each patern save it as a fen 
    stringstream buffer;
    board.printBoard_as_FENstring(buffer);
    return Board(buffer.str());
}

// return total number of n connected pieces,
// start at (start_row, start_col), increase with (delta_row, delta_col)
// n: number of pieces that connected together
// piece: specify piece type
int count_n_connected_pieces(Board& board, int n, PieceType piece,
                             int start_row, int start_col,
                             int delta_row, int delta_col) {
    // number of n connected pieces
    int num = 0;
    
    // number of pieces that connected
    int pieces = 0;
    
    for (int row = start_row, col = start_col;
         row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS;
         row += delta_row, col += delta_col) {
        
        if (board.atLocation(row, col) == piece) {
            pieces++;
        } else {
            if (pieces == n) {
                num++;
            }
            pieces = 0;
        }
    }
    
    return num;
}

// return total number of n connected pieces
// n: number of pieces that connected together
// piece: specify piece type
int count_n_connected_pieces(Board& board, int n, PieceType piece) {
    // ignore illegal n
    if (n <= 0) {
        return 0;
    }
    
    // the result, total number of n-connected pieces
    int num = 0;
    
    // count at each row
    for (int row = 0; row < NUM_ROWS; row++) {
        num += count_n_connected_pieces(board, n, piece, row, 0, 0, 1);
    }
    
    // count at each column
    for (int col = 0; col < NUM_COLS; col++) {
        num += count_n_connected_pieces(board, n, piece, 0, col, 1, 0);
    }
    
    // diagonal 1
    for (int row = NUM_ROWS - 1; row >= 0; row--) {
        num += count_n_connected_pieces(board, n, piece, row, 0, 1, 1);
    }
    for (int col = 1; col < NUM_COLS; col++) {
        num += count_n_connected_pieces(board, n, piece, 0, col, 1, 1);
    }
    
    // diagonal 2
    for (int col = 0; col < NUM_COLS; col++) {
        num += count_n_connected_pieces(board, n, piece, 0, col, 1, -1);
    }
    for (int row = 1; row < NUM_ROWS; row++) {
        num += count_n_connected_pieces(board, n, piece,
                                        row, NUM_COLS - 1, 1, -1);
    }
    
    return num;
}

// compute the heuristic value of board
// asign a value to current board  
double heuristic(Board& board, PieceType ai_piece) {
    // define an opponent piece type 
    PieceType opponent_piece = ai_piece == Player1 ? Player2 : Player1;
    
    double value = 0.0;
    
    for (int i = 0; i < HEURISTIC_LEVEL; i++) {
        int num;
        
        num = count_n_connected_pieces(board, NUM_FOR_WIN - i - 1, ai_piece);
        //3^n > 2^n 
        value += pow((double)(NUM_FOR_WIN - i - 1), num);
        
        num = count_n_connected_pieces(board, NUM_FOR_WIN - i - 1,
                                       opponent_piece);
        value -= pow((double)(NUM_FOR_WIN - i - 1), num);
    }
    
    return value;
}

// minimax decision theory
// recursive function 
pair<double, int> minimax(Board& node, int depth, bool isMaximizing,
    PieceType ai_piece) {
    // when depth = 0 we will stop the backward induction, in our case 5-0
    // when should we stop?
    if (depth <= 0) {
        
        //hur is the score of your pattern on the current board
   
        return pair<double, int>(heuristic(node, ai_piece), rand() % NUM_COLS);
    }

    // initialise best value
    // if you want AI(us) win find the max score 
    // try to find the largest score 
    pair<double, int> best;
    if (isMaximizing) {
        best = make_pair(-INF, rand() % NUM_COLS);
    }
    else {
        best = make_pair(INF, rand() % NUM_COLS);
    }

    // shuffle the columns,
    // then if there are some heuristic value same choice, choose randomly
    vector<int> cols;
    for (int col = 0; col < NUM_COLS; col++) {
        // push_back is a member function for you to add a new element into the vector
        cols.push_back(col);
    }
    random_shuffle(cols.begin(), cols.end());

int connect4AI(const Board& board){
    // This is the Easy AI. It returns a random column.
    // You need to delete this and write your own AI.
    return rand() % NUM_COLS;
}
