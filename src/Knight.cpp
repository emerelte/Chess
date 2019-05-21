#include "Knight.h"


Knight::Knight(color col_, std::shared_ptr<Board> board_, std::shared_ptr<Square> square_) : Piece(col_, board_, square_){
    this->type = KNIGHT;
}

Knight::~Knight() {

}

bool Knight::isPossible() {
    return false;
}

bool Knight::isCorrect() {
    return false;
}

bool Knight::move(char x_, char y_) {
    return false;
}
