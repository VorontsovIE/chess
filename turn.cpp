#ifndef _CHESS_TURN_H
#define _CHESS_TURN_H  1

#include "turn.h"

ostream& operator << (ostream& out, const Turn& turn) {
   out << turn.begin << "-" << turn.end;
   return out;
}

Turn::Turn(Coordinates new_begin, Coordinates new_end) : begin(new_begin), end(new_end) { 
  if (new_begin == new_end) {
    throw std::invalid_argument("Incorrect coordinates"); 
  }
}

static Abstract_Turn* Turn::create_turn(string s) { 
  // TODO!!!...
}

Coordinates Turn::from () {
  return begin;
}

 Coordinates Turn::to () {
  return end;
}

int Turn::col_diff() {
  return to().column() - from().column();
}

int Turn::row_diff() {
  return to().row() - from().row();
}

virtual void Turn::apply(Field& field) {
  field.setFigure(end, field.get_figure(begin));
  field.setFigure(begin, new Empty_cell());
} 

virtual vector<Coordinates> Turn::path (const Field& field) {
  return field.get_figure(begin).path(this);
  // field.get_figure(begin).path(begin, end)
}

virtual bool Turn::path_free(const Field& field) {
  vector<Coordinates> path_vector = path(field);
  for (int i = 0; i < path_vector.size(); ++i) {
    if (field.get_figure(path_vector[i]).is_empty() == false) {
      return false;
    }
  }
  return true;
}



virtual bool NonEatTurn::check(const Field& field) {
  return field.get_figure(begin).check_not_eat(this);
}

virtual bool EatTurn::check(const Field& field) {
  return field.get_figure(begin).check_eat(this) && field.get_figure(end).color() != field.get_figure(begin).color();
}




void Castle::apply_kingside_white (Field& field) {
  field.setFigure(0, 6, new King(true)); // Можно не создавать новых, а воспользоваться старыми королем и ладьей
  field.setFigure(0, 4, new Empty_cell());
  field.setFigure(0, 5, new Rook(true));
  field.setFigure(0, 7, new Empty_cell());
}

void Castle::apply_kingside_black (Field& field) {
  field.setFigure(7, 6, new King(false));
  field.setFigure(7, 4, new Empty_cell());
  field.setFigure(7, 5, new Rook(false));
  field.setFigure(7, 7, new Empty_cell());
}

void Castle::apply_queenside_white (Field& field) {
  field.setFigure(0, 2, new King(true));
  field.setFigure(0, 4, new Empty_cell());
  field.setFigure(0, 3, new Rook(true));
  field.setFigure(0, 0, new Empty_cell());
}

void Castle::apply_queenside_black (Field& field) {
  field.setFigure(7, 2, new King(false));
  field.setFigure(7, 4, new Empty_cell());
  field.setFigure(7, 3, new Rook(false));
  field.setFigure(7, 0, new Empty_cell());
}


virtual bool En_Passant::check(const Field& field) {
  return field.get_figure(begin).check_eat_pass(this);
}
virtual void En_Passant::apply(Field& field) {
  field.setFigure(end, field.get_figure(begin));
  field.setFigure(begin, new Empty_cell());
  
  //установка Empty_cell на место съеденной пешки
  field.setFigure(end.column(), begin.row(), new Empty_cell());
}



virtual bool Pawn_Promotion::check(const Field& field) {
  return field.get_figure(begin).check_promotion(this);
}

virtual void Pawn_Promotion::apply(Field& field) {
  // нам не нужно выбирать тип фигуры, мы его уже знаем. Но нужно создать фигуру этого типа (и нужного цвета)
  field.setFigure(end, field.choose_figure()); 
  field.setFigure(begin, new Empty_cell());
}


#endif
