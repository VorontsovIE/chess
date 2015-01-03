#ifndef _CHESS_COMMON_H
#define _CHESS_COMMON_H  1

#include <stdlib.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cctype>
#include <memory>

using namespace std;

enum Color { WHITE, BLACK };
enum Figure_Type {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, EMPTY_CELL};
enum Turn_Type {CASTLE, EAT_TURN, NON_EAT_TURN, EN_PASSANT, PAWN_PROMOTION};


#endif
