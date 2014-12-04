#ifndef _CHESS_FIGURE_H
#define _CHESS_FIGURE_H  1

#include "common.h"
#include "turn.h"

enum Figure_Type {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, EMPTY_CELL};

class Figure {
private:
  Color m_color;
  virtual bool check(Turn* t) = 0; //{return false;}

public:
  virtual bool is_empty();  
  virtual Figure_Type type() = 0;

  // Three geometric checks
  virtual bool check_not_eat(NonEatTurn* t);
  virtual bool check_eat_pass(En_Passant* t);
  virtual bool check_eat(EatTurn* t);
  virtual vector<Coordinates> path(Turn* t) = 0;

  Figure(Color w_b);  
  Color color();
};


class Empty_cell : public Figure {
public:
  Empty_cell();
  
  virtual bool check(Turn* t);
  virtual vector<Coordinates> path(Turn* t);
  virtual Figure_Type type();

  virtual bool is_empty();
};

class King : public Figure {
  public:
  King(Color w_b);
  virtual bool check(Turn* t);
  virtual Figure_Type type();
  virtual vector<Coordinates> path(Turn* t);
};

class Knight : public Figure {
  public:
  Knight(Color w_b);
  virtual bool check(Turn* t);
  virtual Figure_Type type();
  virtual vector<Coordinates> path(Turn* t);
};

class Rook : public Figure {
public:
  Rook(Color w_b);
  virtual bool check(Turn* t);
  virtual Figure_Type type();
  virtual vector<Coordinates> path(Turn* t);
};

class Bishop : public Figure {
public:
  Bishop(Color w_b);
  virtual bool check(Turn* t);

  virtual Figure_Type type();
  virtual vector<Coordinates> path(Turn* t);
};

class Pawn : public Figure {
public:
  Pawn(Color w_b);

  bool check_eat_geometric(Turn* t);
  virtual bool check_eat(Turn* t);
  virtual bool check_promotion(Turn* t);
  virtual bool check_not_eat(Turn* t);
  virtual bool check_eat_pass(En_Passant* t);
  virtual Figure_Type type();
  virtual vector<Coordinates> path(Turn* t);
};

class Queen : public Figure {
public:
  Queen(Color w_b);

  virtual bool check(Turn* t);
  virtual Figure_Type type();
  virtual vector<Coordinates> path(Turn* t);
};

#endif

// Ладья и король пока не помнят, ходили ли они. Им поменять метод apply. 
// Если фигура появилась из пешки, то ее тоже можно сделать ходившей
