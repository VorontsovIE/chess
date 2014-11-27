enum Color { WHITE, BLACK };

enum Figure_Type {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, EMPTY_CELL};

class Figure {
private:
  Color m_color;
  virtual bool check(Turn* t) = 0; //{return false;}

public:
  virtual bool is_empty() {
    return false;
  }
  
  virtual Figure_Type type() = 0;

  // Three geometric checks
  virtual bool check_not_eat(NotEatTurn* t){
    return check(t);
  }

  virtual bool check_eat_pass(En_Passant* t){
    return false;
  }
  
  virtual bool check_eat(EatTurn* t) {
    return check(t);
  }
  
  virtual vector<Coordinates> path(Turn* t) = 0;

  Figure(Color w_b){
    m_color = w_b;
  }
  
  Color color() {
    return m_color;
  }
};

class Empty_cell : public Figure {
public:
	Empty_cell() : Figure(WHITE) { } // cheap and dirty
	
  virtual bool check(Turn* t) {
    throw std::logic_error("Empty_cell isn't able to call #check function");
  }
  virtual vector<Coordinates> path(Turn* t) {
    throw std::logic_error("Empty_cell isn't able to call #path function");
  }

  virtual Figure_Type type() {
    return EMPTY_CELL;
  }

	virtual bool is_empty() {
  	return true;
	}

};

class King : public Figure {
	public:
	King(Color w_b) : Figure(w_b) { }
	virtual bool check(Turn* t) {
    // return ( abs(t->col_diff() == 1) && abs(t->row_diff() == 1) ) || ( abs(t->col_diff() + abs(t->row_diff() ) == 1;
    return max(abs(t->col_diff()), abs(t->row_diff()) ) == 1;
	}

  virtual Figure_Type type() {
    return KING;
  }


	virtual vector<Coordinates> path(Turn* t) {
    return vector<Coordinates>();
  }

};

class Knight : public Figure {
	public:
	Knight(Color w_b) : Figure(w_b) { }
	virtual bool check(Turn* t) {
  	return abs(t->col_diff()) < 3 && abs(t->col_diff()) >= 1 && abs(t->row_diff()) < 3 && abs(t->row_diff()) >= 1 && \
           ( abs(t->row_diff()) + abs(t->col_diff()) ) == 3;
	}
  virtual Figure_Type type() {
    return KNIGHT;
  }


	virtual vector<Coordinates> path(Turn* t) { //нужно
    return vector<Coordinates>();
  }
};

class Rook : public Figure {
public:
  Rook(Color w_b) : Figure(w_b) { }
  virtual bool check(Turn* t) { // Fix dereference
    return t.from().column() == t.to().column() || t.from().row() == t.to().row();
  }
  virtual Figure_Type type() {
    return ROOK;
  }

  virtual vector<Coordinates> path(Turn* t) {
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

};

class Bishop : public Figure {
public:
  Bishop(Color w_b) : Figure(w_b) { }
  virtual bool check(Turn* t) {
      return abs(t.from().column() - t.to().column()) == abs(t.from().row() - t.to().row());
  }

    virtual Figure_Type type() {
    return BISHOP;
  }

  virtual vector<Coordinates> path(Turn* t) {

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

};

class Pawn : public Figure {
public:
  Pawn(Color w_b) : Figure(w_b) { }

  bool check_eat_geometric(Turn* t) {

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

  virtual bool check_eat(Turn* t) {
	 // && final state is enemy and is not empty cell
    return check_eat_geometric(t) && /
		field.get_figure(end.row(), end.column()).color() != field.get_figure(begin.row(), begin.column()).color() && /
		field.get_figure(end.row(), end.column()).type() != EMPTY_CELL;
  }

  virtual bool check_promotion(Turn* t) {
	  return check_not_eat(t) || check_eat(t);  
  }

  virtual bool check_not_eat(Turn* t) {
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

    virtual bool check_eat_pass(En_Passant* t){
    return t->check_history_pass() && check_eat_geometric(t);
  }

    virtual Figure_Type type() {
    return PAWN;
  }

  virtual vector<Coordinates> path(Turn* t) {
    vector<Coordinates> v_path;
    if (abs(t->row_diff()) == 2) {
      v_path.push_back(Coordinates((t->from().row() + t->to().row())/2, t->from().column()));  
    } 
    return v_path;
  }

};

class Queen : public Figure {
public:
  Queen(Color w_b) : Figure(w_b) {  }

  virtual bool check(Turn* t) {
    return abs(t->from().column() - t->to().column()) == abs(t->from().row() - t->to().row())  ||  t.from().column() == t.to().column() || t.from().row() == t.to().row();
  }

  virtual Figure_Type type() {
    return QUEEN;
  }

  virtual vector<Coordinates> path(Turn* t) {
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
};

// Ладья и король пока не помнят, ходили ли они. Им поменять метод apply. 
// Если фигура появилась из пешки, то ее тоже можно сделать ходившей