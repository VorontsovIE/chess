enum Color { WHITE, BLACK };

class Figure {
private:
  Color m_color;
public:
  virtual bool is_empty() {
    return false;
  }
  // Three geometric checks
  virtual bool check(Turn* t) = 0; //{return false;}
  virtual bool check_not_eat(NotEatTurn* t){
    return check(t);
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

class Rook : public Figure {
public:
  Rook(Color w_b) : Figure(w_b) { }
  virtual bool check(Turn* t) { // Fix dereference
    return t.from().column() == t.to().column() || t.from().row() == t.to().row();
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

  virtual vector<Coordinates> path(Turn* t) {

  vector<Coordinates> v_path;

  if (t->from().row() < t->to().row() && t->from().column() < t->to().column()) { //слева снизу -> наверх вправо
    for (int row = t->from().row() + 1, int col = t->from().column() + 1; row < t->to().row(), col < t->to().column(); ++row, ++col ) {
    v_path.push_back(Coordinates(row, col));
    }
  }
  else if (t->from().row() > t->to().row() && t->from().column() > t->to().column()) { // сверху справа -> вниз налево
    for (int row = t->to().row() + 1, int col = t->to().column() + 1; row < t->from().row(), col < t->from().column(); ++row, ++col ) {
    v_path.push_back(Coordinates(row, col));
    }
  }
  else if (t->from().row() > t->to().row() && t->from().column() < t->to().column()) { //слева сверху -> вниз вправо
    for (int row = t->from().row() - 1, int col = t->from().column() + 1; row > t->to().row(), col < t->to().column(); --row, ++col ) {
    v_path.push_back(Coordinates(row, col));
    }
  }

  else if (t->from().row() < t->to().row() && t->from().column() > t->to().column()) { //снизу справа -> наверх налево
    for (int row = t->to().row() - 1, int col = t->to().column() + 1; row > t->from().row(), col < t->from().column(); --row, ++col ) {
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

  virtual bool check(Turn* t) {
    if (color() == WHITE) {
      if (t.from().row() == 1 && t.col_diff() == 0) {
        return t.row_diff() == 2 || t.row_diff() == 1;
      }
      else {
        return t.row_diff() == 1 && t.col_diff() == 0;
      }
    }
    else {
      if (t.from().row() == 6 && t.col_diff() == 0) {
        return t.row_diff() == -2 || t.row_diff() == -1;
      }
      else {
        return t.row_diff() == -1 && t.col_diff() == 0;
      }
    }
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


  virtual vector<Coordinates> path(Turn* t) {
    if (abs(t->from().column() - t->to().column()) == abs(t->from().row() - t->to().row())) {

      vector<Coordinates> v_path;

      if (t->from().row() < t->to().row() && t->from().column() < t->to().column()) { //слева снизу -> наверх вправо
        for (int row = t->from().row() + 1, int col = t->from().column() + 1; row < t->to().row(), col < t->to().column(); ++row, ++col ) {
          v_path.push_back(Coordinates(row, col));
        }
      }
      else if (t->from().row() > t->to().row() && t->from().column() > t->to().column()) { // сверху справа -> вниз налево
        for (int row = t->to().row() + 1, int col = t->to().column() + 1; row < t->from().row(), col < t->from().column(); ++row, ++col ) {
          v_path.push_back(Coordinates(row, col));
        }
      }
      else if (t->from().row() > t->to().row() && t->from().column() < t->to().column()) { //слева сверху -> вниз вправо
        for (int row = t->from().row() - 1, int col = t->from().column() + 1; row > t->to().row(), col < t->to().column(); --row, ++col ) {
          v_path.push_back(Coordinates(row, col));
        }
      }

      else if (t->from().row() < t->to().row() && t->from().column() > t->to().column()) { //снизу справа -> наверх налево
        for (int row = t->to().row() - 1, int col = t->to().column() + 1; row > t->from().row(), col < t->from().column(); --row, ++col ) {
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
