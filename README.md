Connect 4 Project
=========================

See the [Getting Started](https://github.com/eecs183/Connect4/wiki/Getting-Started) guide for more information.
I believe my AI will beats your hard AI. So our team choose to beats all your AI from Easy to Hard.
    Paragraph describing the functionality of my algorithm in ai:For the AI of connect4, we applied Minimax theory and in order to reach that goal, we involved some concepts and methods which beyond the scope of our class during the coding. Concepts such as vector and pair and algorithm such as Iterative approaches and so on. The AI is so powerful that you can only win it by setting a trap during the opening  , a chess terminology " Force To win". 
    All the functions' RME are attached below:
    /**
 * Requires: nothing.
 * Modifies: nothing.
 * Effects: Chooses a column for the next move
 *          and returns the column index. The
 *          return value must be in range
 *          [0, NUM_COLS-1].
 */
int connect4AI(const Board& board);

#endif /* AI_H__ */

/**
* Requires: nothing.
* Modifies: nothing.
* Effects:  copy the current borad, save it for simulation 
*           return a buffer of the current board           
*/
Board copy_board(const Board &board);

/**
* Requires: n > 0
* Modifies: nothing.
* Effects:  start at (start_row, start_col), increase with (delta_row, delta_col)
*           n: number of pieces that connected together
*           piece: specify piece type
*           return total number of a specific n connected pieces
*/ 
int count_n_connected_pieces(Board& board, int n, PieceType piece,
    int start_row, int start_col,
    int delta_row, int delta_col);

/**
* Requires: n > 0
* Modifies: nothing.
* Effects:  count n connected pieces in the current board 
*           call funtion: count_n_connected_pieces
*           directions: diagonal 1, diagonal 2, count at each column, count at each row
*           return total number of a specific n connected pieces in all driections
*/
int count_n_connected_pieces(Board& board, int n, PieceType piece);

/**
* Requires: just need to think the cases of 2 or 3 connected pieces in a line  
* Modifies: nothing.
* Effects:  decide whose term 
*           define an opponent piece type
*           If AI: asign a positive valve
*           If opponent: asign a negetive value 
*           return a value score for current board
*/
double heuristic(Board& board, PieceType ai_piece);

/**
* Requires: MINIMAX_LEVEL is 5
* Modifies: nothing.
* Effects:  Minimax decision theory 
*           define a best move for each part, the move corresponding to a higher score of each players 
*           Assign a postive number to AI's best move, a negative number to opponent's best move
*           When depth is 5: on the top of the game tree 
*           When depth is 0：on bottom of the tree, stop simulation process 
*           When depth is smallar than or equal to 0, reach the bottom of the tree, retun a current score of node and a rand move 
*           define a vector of an cols={0,1,2,3,4,5,6}
*           shuffle the columns so that make the AI more like a human
*           read a board from current pattern, call the function $result$ in board.cpp, try each cols:
*                  if current player win: sign a score to that player( AI is inf ; Opponent is -inf)
*                  if current player not win and the col we try is a legal move: 
*                           apply the Iterative Approaches: assign the player to the next player
*                                                           assign depth -= 1
*           after finished all the game tree (base on the current pattern, try each possible move for each death)
*           return a best move corresponding to the highest score of the AI 
*/
pair<double, int> minimax(Board& node, int depth, bool isMaximizing,
    PieceType ai_piece);
