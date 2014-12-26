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

Abstract_Turn* Turn::create_turn(string s) { 
  // TODO!!!...
  throw std::logic_error("Turn.create_turn not implemented");
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

void Turn::apply(Field& field) {
  field.setFigure(end, field.get_figure(begin));
  field.setFigure(begin, new Empty_cell());
} 

vector<Coordinates> Turn::path (const Field& field) {
  return field.get_figure(begin).path(this);
  // field.get_figure(begin).path(begin, end)
}

bool Turn::path_free(const Field& field) {
  vector<Coordinates> path_vector = path(field);
  for (int i = 0; i < path_vector.size(); ++i) {
    if (field.get_figure(path_vector[i]).is_empty() == false) {
      return false;
    }
  }
  return true;
}



bool NonEatTurn::check(const Field& field) {
  return field.get_figure(begin).check_not_eat(this) && field.get_figure(end).type() == EMPTY_CELL;
}

bool EatTurn::check(const Field& field) {
  return  field.get_figure(begin).check_eat(this) && \
          field.get_figure(end).color() != field.get_figure(begin).color() && \
          field.get_figure(end).type() != EMPTY_CELL;
}




void Castle::apply_kingside_white (Field& field) {
  field.setFigure(0, 6, new King(WHITE)); // Можно не создавать новых, а воспользоваться старыми королем и ладьей
  field.setFigure(0, 4, new Empty_cell());
  field.setFigure(0, 5, new Rook(WHITE));
  field.setFigure(0, 7, new Empty_cell());
}

void Castle::apply_kingside_black (Field& field) {
  field.setFigure(7, 6, new King(BLACK));
  field.setFigure(7, 4, new Empty_cell());
  field.setFigure(7, 5, new Rook(BLACK));
  field.setFigure(7, 7, new Empty_cell());
}

void Castle::apply_queenside_white (Field& field) {
  field.setFigure(0, 2, new King(WHITE));
  field.setFigure(0, 4, new Empty_cell());
  field.setFigure(0, 3, new Rook(WHITE));
  field.setFigure(0, 0, new Empty_cell());
}

void Castle::apply_queenside_black (Field& field) {
  field.setFigure(7, 2, new King(BLACK));
  field.setFigure(7, 4, new Empty_cell());
  field.setFigure(7, 3, new Rook(BLACK));
  field.setFigure(7, 0, new Empty_cell());
}


bool En_Passant::check(const Field& field) {
  if (field.last_turn == NULL || field.last_turn->turn_type() != NON_EAT_TURN) {
    return false;
  }
  
  Turn *last_turn = (Turn*)field.last_turn;

  bool check_pass_help;
  if(field.get_figure(begin).color() == WHITE) {
    check_pass_help = (to().row() - last_turn->to().row() == 1);
  } else {
    check_pass_help = (to().row() - last_turn->to().row() == -1);
  }

  return field.get_figure(begin).type() == PAWN && field.get_figure(last_turn->to()).type() == PAWN && \
         field.get_figure(last_turn->to()).color() != field.get_figure(begin).color() && \
         abs(last_turn->to().column() - begin.column() ) == 1 && \
         abs(last_turn->row_diff()) == 2 && \
         last_turn->to().row() == begin.row() && \
         end.column() == last_turn->to().column() && \
         check_pass_help;
}

void En_Passant::apply(Field& field) {
  field.setFigure(end, field.get_figure(begin));
  field.setFigure(begin, new Empty_cell());
  
  //установка Empty_cell на место съеденной пешки
  field.setFigure(end.column(), begin.row(), new Empty_cell());
}



bool Pawn_Promotion::check(const Field& field) {
  return field.get_figure(begin).check_promotion(this);
}

void Pawn_Promotion::apply(Field& field) {
  // нам не нужно выбирать тип фигуры, мы его уже знаем. Но нужно создать фигуру этого типа (и нужного цвета)
  Color current_side = field.get_figure(begin).color();
  field.setFigure(end, Figure::build_figure(fig_type, current_side)); 
  field.setFigure(begin, new Empty_cell());
}

// лучше возвращать Fig_Type чтобы передать его в конструктор PawnPromotion
// переделать через SWITCH CASE
Figure_Type Pawn_Promotion::choose_figure() { 
  int choice;
  cout << "Choose the Figure what you want: 1 - Rook, 2 - Knight, 3 - Bishop, 4 - Queen";
  cin >> choice;
  if (choice == 1) {
    return ROOK;
  }
  else if (choice == 2) {
    return KNIGHT;
  }
  else if (choice == 3) {
    return BISHOP;
  }
  else if (choice == 4) {
    return QUEEN;
  }
}
