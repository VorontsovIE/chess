#include "common.h"
#include "figure.h"

bool Figure::is_empty() {
  return false;
}

Figure_Type type();

// Three geometric checks
bool Figure::check_not_eat(NonEatTurn* t){
  return check(t);
}

bool Figure::check_eat(EatTurn* t) {
  return check(t);
}

bool Figure::check_promotion(Pawn_Promotion* t) {
  return false;  
}

// bool Figure::check_eat_pass(En_Passant* t){
//   return false;
// }

vector<Coordinates> path(Turn* t);

Figure::Figure(Color w_b){
  m_color = w_b;
}

Color Figure::color() {
  return m_color;
}

Figure* Figure::build_figure(Figure_Type choice, Color color) {
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



Empty_cell::Empty_cell() : Figure(WHITE) { } // cheap and dirty

bool Empty_cell::check(Turn* t) {
  throw std::logic_error("Empty_cell isn't able to call #check function");
}
vector<Coordinates> Empty_cell::path(Turn* t) {
  throw std::logic_error("Empty_cell isn't able to call #path function");
}

Figure_Type Empty_cell::type() {
  return EMPTY_CELL;
}

bool Empty_cell::is_empty() {
	return true;
}



King::King(Color w_b) : Figure(w_b) { }
bool King::check(Turn* t) {
  // return ( abs(t->col_diff() == 1) && abs(t->row_diff() == 1) ) || ( abs(t->col_diff() + abs(t->row_diff() ) == 1;
  return max(abs(t->col_diff()), abs(t->row_diff()) ) == 1;
}

Figure_Type King::type() {
  return KING;
}


vector<Coordinates> King::path(Turn* t) {
  return vector<Coordinates>();
}




Knight::Knight(Color w_b) : Figure(w_b) { }
bool Knight::check(Turn* t) {
	return abs(t->col_diff()) < 3 && abs(t->col_diff()) >= 1 && abs(t->row_diff()) < 3 && abs(t->row_diff()) >= 1 && \
         ( abs(t->row_diff()) + abs(t->col_diff()) ) == 3;
}
Figure_Type Knight::type() {
  return KNIGHT;
}


vector<Coordinates> Knight::path(Turn* t) { //нужно
  return vector<Coordinates>();
}


Rook::Rook(Color w_b) : Figure(w_b) { }
bool Rook::check(Turn* t) { // Fix dereference
  return t->from().column() == t->to().column() || t->from().row() == t->to().row();
}
Figure_Type Rook::type() {
  return ROOK;
}

vector<Coordinates> Rook::path(Turn* t) {
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
bool Bishop::check(Turn* t) {
    return abs(t->from().column() - t->to().column()) == abs(t->from().row() - t->to().row());
}

  Figure_Type Bishop::type() {
  return BISHOP;
}

vector<Coordinates> Bishop::path(Turn* t) {

vector<Coordinates> v_path;

if (t->from().row() < t->to().row() && t->from().column() < t->to().column()) { //слева снизу -> наверх вправо
	for (int row = t->from().row() + 1, col = t->from().column() + 1; row < t->to().row() && col < t->to().column(); ++row, ++col ) {
		v_path.push_back(Coordinates(row, col));
	}
}
else if (t->from().row() > t->to().row() && t->from().column() > t->to().column()) { // сверху справа -> вниз налево
	for (int row = t->to().row() + 1, col = t->to().column() + 1; row < t->from().row() && col < t->from().column(); ++row, ++col ) {
		v_path.push_back(Coordinates(row, col));
	}
}
else if (t->from().row() > t->to().row() && t->from().column() < t->to().column()) { //слева сверху -> вниз вправо
	for (int row = t->from().row() - 1, col = t->from().column() + 1; row > t->to().row() && col < t->to().column(); --row, ++col ) {
		v_path.push_back(Coordinates(row, col));
	}
}

else if (t->from().row() < t->to().row() && t->from().column() > t->to().column()) { //снизу справа -> наверх налево
	for (int row = t->to().row() - 1, col = t->to().column() + 1; row > t->from().row() && col < t->from().column(); --row, ++col ) {
		v_path.push_back(Coordinates(row, col));
	}
}

else {
throw std::logic_error("Impossible situation");
}
return v_path;
}



Pawn::Pawn(Color w_b) : Figure(w_b) { }

bool Pawn::check(Turn* t) {
  throw std::logic_error("This function should not be used");
}

bool Pawn::check_eat(Turn* t) {
  if (t->from().row() > t->to().row() && t->from().column() > t->to().column()) {
     return t->from().column()-1 == t->to().column() && t->from().row()-1 == t->to().row();
   }
   else if (t->from().row() > t->to().row() && t->from().column() < t->to().column()) {
    return t->from().column()+1 == t->to().column() && t->from().row()-1 == t->to().row();
   }
   else if (t->from().row() < t->to().row() && t->from().column() < t->to().column()) {
    return t->from().column()+1 == t->to().column() && t->from().row()+1 == t->to().row();
   }
   else if (t->from().row() < t->to().row() && t->from().column() > t->to().column()) {
    return t->from().column()-1 == t->to().column() && t->from().row()+1 == t->to().row();
   }
}

bool Pawn::check_promotion(Pawn_Promotion* t) {
  return check_not_eat(t) || check_eat(t);  
}

bool Pawn::check_not_eat(Turn* t) {
  if (t->col_diff() != 0) {
    return false;
  }
  if (color() == WHITE) {
    if (t->from().row() == 1) {
      return t->row_diff() == 2 || t->row_diff() == 1;
    }
    else {
      return t->row_diff() == 1;
    }
  }
  else {
    if (t->from().row() == 6) {
      return t->row_diff() == -2 || t->row_diff() == -1;
    }
    else {
      return t->row_diff() == -1;
    }
  }
}

// bool Pawn::check_eat_pass(En_Passant* t){
//   // check_eat is just a geometrical check (it doesn't check whether figure is on place)
//   return t->check_history_pass() && check_eat(t);
// }

Figure_Type Pawn::type() {
  return PAWN;
}

vector<Coordinates> Pawn::path(Turn* t) {
  vector<Coordinates> v_path;
  if (abs(t->row_diff()) == 2) {
    v_path.push_back(Coordinates((t->from().row() + t->to().row())/2, t->from().column()));  
  } 
  return v_path;
}



Queen::Queen(Color w_b) : Figure(w_b) {  }

bool Queen::check(Turn* t) {
  return abs(t->from().column() - t->to().column()) == abs(t->from().row() - t->to().row())  ||  t->from().column() == t->to().column() || t->from().row() == t->to().row();
}

Figure_Type Queen::type() {
  return QUEEN;
}

vector<Coordinates> Queen::path(Turn* t) {
  vector<Coordinates> v_path;
  if (abs(t->from().column() - t->to().column()) == abs(t->from().row() - t->to().row())) {

    if (t->from().row() < t->to().row() && t->from().column() < t->to().column()) { //слева снизу -> наверх вправо
		for (int row = t->from().row() + 1, col = t->from().column() + 1; row < t->to().row() && col < t->to().column(); ++row, ++col ) {
			v_path.push_back(Coordinates(row, col));
      }
    }
    else if (t->from().row() > t->to().row() && t->from().column() > t->to().column()) { // сверху справа -> вниз налево
		for (int row = t->to().row() + 1, col = t->to().column() + 1; row < t->from().row() && col < t->from().column(); ++row, ++col ) {
			v_path.push_back(Coordinates(row, col));
      }
    }
    else if (t->from().row() > t->to().row() && t->from().column() < t->to().column()) { //слева сверху -> вниз вправо
		for (int row = t->from().row() - 1, col = t->from().column() + 1; row > t->to().row() && col < t->to().column(); --row, ++col ) {
			v_path.push_back(Coordinates(row, col));
      }
    }

    else if (t->from().row() < t->to().row() && t->from().column() > t->to().column()) { //снизу справа -> наверх налево
		for (int row = t->to().row() - 1, col = t->to().column() + 1; row > t->from().row() && col < t->from().column(); --row, ++col ) {
			v_path.push_back(Coordinates(row, col));
      }
    }

    else {
		throw std::logic_error("Impossible situation");
    }

  } else if (t->from().column() == t->to().column() || t->from().row() == t->to().row()) {
    
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
