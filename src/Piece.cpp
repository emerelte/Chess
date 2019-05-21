#include "Piece.h"
#include "Square.h"

Piece::Piece(color col_, Board* board_, Square* square_) {
    /**
     * Constructor
     */

     this->board = board_;
     this->square = square_;
     this->col = col_;
     this->square->setOccupator(this);
}

Piece::~Piece() {
    /**
    * Destructor
    */
}

bool Piece::isCorrect(int x_, int y_) {
	/**
	* Ckeck if proposed move is correct for this type of Piece
	* @return true if is correct false otherwise
	*/
}

bool Piece::isPossible(int x_, int y_) {
	/**
	* Ckeck if proposed move is correct
	* @return true if is move is possible false otherwise
	*/

}

bool Piece::move(char x_, char y_) {
	/**
	* Move Piece to new position
	* @param first cordinate of board
	* @param second cordinate of board
	* @return true if Piece was moved sucesfully false otherwise
	*/
}
