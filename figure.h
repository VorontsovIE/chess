#ifndef _CHESS_FIGURE_H
#define _CHESS_FIGURE_H  1

class Figure;
#include "common.h"
#include "turn.h"


class Figure {
private:
  Color m_color;
  virtual bool check(Turn* t) = 0; //{return false;}

public:
  virtual string symbol() = 0;
  virtual bool is_empty();  
  virtual Figure_Type type() = 0;

  // Three geometric checks
  virtual bool check_not_eat(NonEatTurn* t);
  // virtual bool check_eat_pass(En_Passant* t);
  virtual bool check_eat(EatTurn* t);
  virtual bool check_promotion(Pawn_Promotion* t);
  virtual vector<Coordinates> path(Turn* t) = 0;

  Figure(Color w_b);  
  Color color();

  static Figure* build_figure(Figure_Type choice, Color color);
};


class Empty_cell : public Figure {
  virtual bool check(Turn* t);
public:
  Empty_cell();
  virtual string symbol();
  virtual vector<Coordinates> path(Turn* t);
  virtual Figure_Type type();

  virtual bool is_empty();
};

class King : public Figure {
  virtual bool check(Turn* t);
public:
  King(Color w_b);
  virtual string symbol();
  virtual Figure_Type type();
  virtual vector<Coordinates> path(Turn* t);
};

class Knight : public Figure {
  virtual bool check(Turn* t);
public:
  Knight(Color w_b);
  virtual string symbol();
  virtual Figure_Type type();
  virtual vector<Coordinates> path(Turn* t);
};

class Rook : public Figure {
  virtual bool check(Turn* t);
public:
  Rook(Color w_b);
  virtual string symbol();
  virtual Figure_Type type();
  virtual vector<Coordinates> path(Turn* t);
};

class Bishop : public Figure {
  virtual bool check(Turn* t);
public:
  Bishop(Color w_b);
  virtual string symbol();
  virtual Figure_Type type();
  virtual vector<Coordinates> path(Turn* t);
};

class Pawn : public Figure {
public:
  Pawn(Color w_b);
  virtual string symbol();
  virtual bool check(Turn* t);
  virtual bool check_promotion(Pawn_Promotion* t);
  virtual bool check_eat(EatTurn* t); // they can take Pawn_Promotion or En_Passant turn, not only Eat/NonEat turns
  virtual bool check_not_eat(NonEatTurn* t); // ditto
  // virtual bool check_eat_pass(En_Passant* t);
  virtual Figure_Type type();
  virtual vector<Coordinates> path(Turn* t);
};

class Queen : public Figure {
  virtual bool check(Turn* t);
public:
  Queen(Color w_b);
  virtual string symbol();
  virtual Figure_Type type();
  virtual vector<Coordinates> path(Turn* t);
};

#endif

// Ладья и король пока не помнят, ходили ли они. Им поменять метод apply. 
// Если фигура появилась из пешки, то ее тоже можно сделать ходившей
