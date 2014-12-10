#include "common.h"

virtual bool Figure::is_empty() {
  return false;
}

virtual Figure_Type type() = 0;

// Three geometric checks
virtual bool Figure::check_not_eat(NonEatTurn* t){
  return check(t);
}

virtual bool Figure::check_eat(EatTurn* t) {
  return check(t);
}

virtual bool Figure::check_eat_pass(En_Passant* t){
  return false;
}

virtual vector<Coordinates> path(Turn* t) = 0;

Figure::Figure(Color w_b){
  m_color = w_b;
}

Color Figure::color() {
  return m_color;
}

static Figure* Figure::build_figure(Figure_Type choice, Color color) {
  switch(choice){
    case ROOK:
      return new Rook(color);
      break;
    case KNIGHT:
      return new Knight(color);
      break;
    case BISHOP:
      return new Bishop(color);
      break;
    case QUEEN:
      return new Queen(color);
      break;
    case KING:
      return new King(color);
      break;
    case PAWN:
      return new Pawn(color);
      break;
    case EMPTY_CELL:
      return new Empty_cell();
      break;
    // default: 
    //   ...
    //   break;
  }
  
  // if (choice == ROOK) {
  //   return new Rook(color);
  // }
  // else if (choice == KNIGHT) {
  //   return new Knight(color);
  // }
  // else if (choice == BISHOP) {
  //   return new Bishop(color);
  // }
  // else if (choice == QUEEN) {
  //   return new Queen(color);
  // }
  // else if (choice == EMPTY_CELL) {
  //   return new Empty_cell();
  // }
  // else if (choice == KING) {
  //   return new King(color);
  // }
  // else if (choice == PAWN) {
  //   return new Pawn(color);
  // }
}



Empty_Cell::Empty_cell() : Figure(WHITE) { } // cheap and dirty

virtual bool Empty_Cell::check(Turn* t) {
  throw std::logic_error("Empty_cell isn't able to call #check function");
}
virtual vector<Coordinates> Empty_Cell::path(Turn* t) {
  throw std::logic_error("Empty_cell isn't able to call #path function");
}

virtual Figure_Type Empty_Cell::type() {
  return EMPTY_CELL;
}

virtual bool Empty_Cell::is_empty() {
	return true;
}



King::King(Color w_b) : Figure(w_b) { }
virtual bool King::check(Turn* t) {
  // return ( abs(t->col_diff() == 1) && abs(t->row_diff() == 1) ) || ( abs(t->col_diff() + abs(t->row_diff() ) == 1;
  return max(abs(t->col_diff()), abs(t->row_diff()) ) == 1;
}

virtual Figure_Type King::type() {
  return KING;
}


virtual vector<Coordinates> King::path(Turn* t) {
  return vector<Coordinates>();
}




Knight::Knight(Color w_b) : Figure(w_b) { }
virtual bool Knight::check(Turn* t) {
	return abs(t->col_diff()) < 3 && abs(t->col_diff()) >= 1 && abs(t->row_diff()) < 3 && abs(t->row_diff()) >= 1 && \
         ( abs(t->row_diff()) + abs(t->col_diff()) ) == 3;
}
virtual Figure_Type Knight::type() {
  return KNIGHT;
}


virtual vector<Coordinates> Knight::path(Turn* t) { //нужно
  return vector<Coordinates>();
}


Rook::Rook(Color w_b) : Figure(w_b) { }
virtual bool Rook::check(Turn* t) { // Fix dereference
  return t.from().column() == t.to().column() || t.from().row() == t.to().row();
}
virtual Figure_Type Rook::type() {
  return ROOK;
}

virtual vector<Coordinates> Rook::path(Turn* t) {
  vector<Coordinates> v_path;
  if (t->row_diff() == 0) {
		for (int col = min(t->from().column(), t->to().column()) + 1; col < max(t->from().column(), t->to().column()) ; ++col) {
			v_path.push_back(Coordinates(t->from().row(), col));  
    }
  } else if (t->col_diff() == 0) {
		for (int row = min(t->from().row(), t->to().row()) + 1; row < max(t->from().row(), t->to().row()) ; ++row) {
			v_path.push_back(Coordinates(row, t->from().column()));  
    }
  } else {
	throw std::logic_error("Impossible situation");
  }
  return v_path;
}


Bishop::Bishop(Color w_b) : Figure(w_b) { }
virtual bool Bishop::check(Turn* t) {
    return abs(t.from().column() - t.to().column()) == abs(t.from().row() - t.to().row());
}

  virtual Figure_Type Bishop::type() {
  return BISHOP;
}

virtual vector<Coordinates> Bishop::path(Turn* t) {

vector<Coordinates> v_path;

if (t->from().row() < t->to().row() && t->from().column() < t->to().column()) { //слева снизу -> наверх вправо
	for (int row = t->from().row() + 1, int col = t->from().column() + 1; row < t->to().row() && col < t->to().column(); ++row, ++col ) {
		v_path.push_back(Coordinates(row, col));
	}
}
else if (t->from().row() > t->to().row() && t->from().column() > t->to().column()) { // сверху справа -> вниз налево
	for (int row = t->to().row() + 1, int col = t->to().column() + 1; row < t->from().row() && col < t->from().column(); ++row, ++col ) {
		v_path.push_back(Coordinates(row, col));
	}
}
else if (t->from().row() > t->to().row() && t->from().column() < t->to().column()) { //слева сверху -> вниз вправо
	for (int row = t->from().row() - 1, int col = t->from().column() + 1; row > t->to().row() && col < t->to().column(); --row, ++col ) {
		v_path.push_back(Coordinates(row, col));
	}
}

else if (t->from().row() < t->to().row() && t->from().column() > t->to().column()) { //снизу справа -> наверх налево
	for (int row = t->to().row() - 1, int col = t->to().column() + 1; row > t->from().row() && col < t->from().column(); --row, ++col ) {
		v_path.push_back(Coordinates(row, col));
	}
}

else {
throw std::logic_error("Impossible situation");
}
return v_path;
}



Pawn::Pawn(Color w_b) : Figure(w_b) { }

virtual bool Pawn::check(Turn* t) {
  throw std::logic_error("This function should not be used");
}

bool Pawn::check_eat_geometric(Turn* t) {

   if (begin.row() > end.row() && begin.column() > end.column()) {
		 return begin.column()-1 == end.column() && begin.row()-1 == end.row();
   }
   else if (begin.row() > end.row() && begin.column() < end.column()) {
	  return begin.column()+1 == end.column() && begin.row()-1 == end.row();
	 }
   else if (begin.row() < end.row() && begin.column() < end.column()) {
	  return begin.column()+1 == end.column() && begin.row()+1 == end.row();
   }
   else if (begin.row() < end.row() && begin.column() > end.column()) {
	  return begin.column()-1 == end.column() && begin.row()+1 == end.row();
   }

}

virtual bool Pawn::check_eat(Turn* t) {
 // && final state is enemy and is not empty cell
  return check_eat_geometric(t) && /
	field.get_figure(end.row(), end.column()).color() != field.get_figure(begin.row(), begin.column()).color() && /
	field.get_figure(end.row(), end.column()).type() != EMPTY_CELL;
}

virtual bool Pawn::check_promotion(Turn* t) {
  return check_not_eat(t) || check_eat(t);  
}

virtual bool Pawn::check_not_eat(Turn* t) {
  if (t.col_diff() != 0 || field.get_figure(end.row(), end.column()).type() != EMPTY_CELL) {
    return false;
  }
  if (color() == WHITE) {
    if (t.from().row() == 1) {
      return t.row_diff() == 2 || t.row_diff() == 1;
    }
    else {
      return t.row_diff() == 1;
    }
  }
  else {
    if (t.from().row() == 6) {
      return t.row_diff() == -2 || t.row_diff() == -1;
    }
    else {
      return t.row_diff() == -1;
    }
  }
}

virtual bool Pawn::check_eat_pass(En_Passant* t){
  return t->check_history_pass() && check_eat_geometric(t);
}

  virtual Figure_Type Pawn::type() {
  return PAWN;
}

virtual vector<Coordinates> Pawn::path(Turn* t) {
  vector<Coordinates> v_path;
  if (abs(t->row_diff()) == 2) {
    v_path.push_back(Coordinates((t->from().row() + t->to().row())/2, t->from().column()));  
  } 
  return v_path;
}



Queen::Queen(Color w_b) : Figure(w_b) {  }

virtual bool Queen::check(Turn* t) {
  return abs(t->from().column() - t->to().column()) == abs(t->from().row() - t->to().row())  ||  t.from().column() == t.to().column() || t.from().row() == t.to().row();
}

virtual Figure_Type Queen::type() {
  return QUEEN;
}

virtual vector<Coordinates> Queen::path(Turn* t) {
  if (abs(t->from().column() - t->to().column()) == abs(t->from().row() - t->to().row())) {

    vector<Coordinates> v_path;

    if (t->from().row() < t->to().row() && t->from().column() < t->to().column()) { //слева снизу -> наверх вправо
		for (int row = t->from().row() + 1, int col = t->from().column() + 1; row < t->to().row() && col < t->to().column(); ++row, ++col ) {
			v_path.push_back(Coordinates(row, col));
      }
    }
    else if (t->from().row() > t->to().row() && t->from().column() > t->to().column()) { // сверху справа -> вниз налево
		for (int row = t->to().row() + 1, int col = t->to().column() + 1; row < t->from().row() && col < t->from().column(); ++row, ++col ) {
			v_path.push_back(Coordinates(row, col));
      }
    }
    else if (t->from().row() > t->to().row() && t->from().column() < t->to().column()) { //слева сверху -> вниз вправо
		for (int row = t->from().row() - 1, int col = t->from().column() + 1; row > t->to().row() && col < t->to().column(); --row, ++col ) {
			v_path.push_back(Coordinates(row, col));
      }
    }

    else if (t->from().row() < t->to().row() && t->from().column() > t->to().column()) { //снизу справа -> наверх налево
		for (int row = t->to().row() - 1, int col = t->to().column() + 1; row > t->from().row() && col < t->from().column(); --row, ++col ) {
			v_path.push_back(Coordinates(row, col));
      }
    }

    else {
		throw std::logic_error("Impossible situation");
    }

  } else if (t.from().column() == t.to().column() || t.from().row() == t.to().row()) {
    vector<Coordinates> v_path;
    if (t->row_diff() == 0) {
		for (int col = min(t->from().column(), t->to().column()) + 1; col < max(t->from().column(), t->to().column()) ; ++col) {
			v_path.push_back(Coordinates(t->from().row(), col));  
      }
    } else if (t->col_diff() == 0) {
		for (int row = min(t->from().row(), t->to().row()) + 1; row < max(t->from().row(), t->to().row()) ; ++row) {
			v_path.push_back(Coordinates(row, t->from().column()));  
      }
    } else {
		throw std::logic_error("Impossible situation");
    }

  }
	return v_path;
}

// Ладья и король пока не помнят, ходили ли они. Им поменять метод apply. 
// Если фигура появилась из пешки, то ее тоже можно сделать ходившей
