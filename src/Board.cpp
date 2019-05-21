#include <assert.h>
#include "Board.h"

Board::Board() {
    /**
     * Parameterless constructor, initializes table with all pieces
     */
    turn = WHITE;
    game_s = NORMAL;
    for (char tmp_y = '1'; tmp_y <= '8'; ++tmp_y) {
            for (char tmp_x='a';tmp_x<='h';++tmp_x) {
                matrix.insert(std::pair<std::pair<char, char>, Square>(std::make_pair(tmp_x, tmp_y), Square(tmp_x, tmp_y)));
        }
    }
}

Board::~Board() {
    /**
     * Destructor
     */
}

bool Board::isCheck() {
    /**
     * Checks if there was check.
     * @return true if there was check, false otherwise
     */
    return game_s == CHECK || game_s == CHECK_MATE;
}

bool Board::move(std::string instruction) {
    /**
     * Moves piece like said in the instruction
     * @param instruction next move in chess notation
     * @return true if the move was successfully performed, false otherwise
     */
    // TO DO roszada

    if (instruction.size() < 2){
        return false;
    }
    char dest_x; char dest_y;Piece_type figToMove;
    // figure move
    if (isupper(instruction.at(0))){
        if (instruction.size()!=3)
            return false;
        dest_x = instruction.at(1);
        dest_y = instruction.at(2);
        switch(instruction.at(0)){
            case 'B':
                figToMove = BISHOP;
                break;
            case 'K':
                figToMove = KING;
                break;
            case 'N':
                figToMove = KNIGHT;
                break;
            case 'Q':
                figToMove = QUEEN;
                break;
            case 'R':
                figToMove = ROOK;
                break;
            default:
                return false;
        }
     }
    else{
        if (instruction.size()!=2)
            return false;
        dest_x = instruction.at(0);
        dest_y = instruction.at(1);
        figToMove = PAWN;
    }
    std::vector<Piece *> candidatesToMove = this->findPieces(turn,figToMove);
    for (auto it=candidatesToMove.begin();it!=candidatesToMove.end();++it){
        if ((*it)->move(dest_x,dest_y)) {
            history.push_back(instruction);
            turn = turn == WHITE ? BLACK : WHITE;
            return true;
        }
    }
    return false;
}

std::string Board::getHistory() {
    /**
     * Getter of history
     * @return history of the chess game, using standard chess notation
     */
    std::string formattedHistory = "";
    for (int i=0;i<history.size();++i){
        formattedHistory += history[i];
        formattedHistory += "\t";
        if (i%2==1){
            formattedHistory+="\n";
        }
    }
    return formattedHistory;
}

std::map<std::pair<char, char>, Square> Board::getMatrix() {
    /**
     * Getter of matrix
     * @return map containing indexes of squares and object Square describing the square
     */
    return matrix;
}

color Board::getTurn() {
    /**
     * Getter of turn
     * @return if black or white is about to move
     */
    return turn;
}

std::vector<Piece *> Board::findPieces(color col, Piece_type typ) {
    /**
     * Searches for every possible type of piece on the whole board
     * @return vector of suitable pieces
     */
    std::vector<Piece *> matching_pieces;
    for (auto & sq : matrix){
        Piece * sq_occup = sq.second.getOccupator();
        if (sq_occup->getColor()==col && sq_occup->getType()==typ){
            matching_pieces.push_back(sq_occup);
        }
    }
    return std::vector<Piece *>();
}
