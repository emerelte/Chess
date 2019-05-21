#include "Bishop.h"


Bishop::Bishop(color col_, Board* board_, Square* square_) : Piece (col_, board_, square_) {
    this->type = BISHOP;
}

Bishop::~Bishop() {

}

bool Bishop::isCorrect() {
    return false;
}

bool Bishop::isPossible() {
    return false;
}

bool Bishop::move(char x_, char y_) {
    return false;
}
