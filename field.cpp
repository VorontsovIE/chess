#include "field.h"
#include "turn.h"

Field::Field(Abstract_Turn* new_last_turn) {
  last_turn = new_last_turn;
  v_field = vector<vector<Figure*> >();
  for (int i = 0; i<=7; ++i) {
    v_field.push_back(vector<Figure*>());
    for (int k = 0; k<=7; ++k) {
      v_field[i].push_back(new Empty_cell());
    }
  }

  setFigure(0,0, new Rook(WHITE));
  setFigure(0,1, new Pawn(WHITE));
  setFigure(0,6, new Pawn(BLACK));
  setFigure(0,7, new Rook(BLACK));

  setFigure(1,0, new Knight(WHITE));
  setFigure(1,1, new Pawn(WHITE));
  setFigure(1,6, new Pawn(BLACK));
  setFigure(1,7, new Knight(BLACK));

  setFigure(2,0, new Bishop(WHITE));
  setFigure(2,1, new Pawn(WHITE));
  setFigure(2,6, new Pawn(BLACK));
  setFigure(2,7, new Bishop(BLACK));

  setFigure(3,0, new Queen(WHITE));
  setFigure(3,1, new Pawn(WHITE));
  setFigure(3,6, new Pawn(BLACK));
  setFigure(3,7, new Queen(BLACK));

  setFigure(4,0, new King(WHITE));
  setFigure(4,1, new Pawn(WHITE));
  setFigure(4,6, new Pawn(BLACK));
  setFigure(4,7, new King(BLACK));

  setFigure(5,0, new Bishop(WHITE));
  setFigure(5,1, new Pawn(WHITE));
  setFigure(5,6, new Pawn(BLACK));
  setFigure(5,7, new Bishop(BLACK));

  setFigure(6,0, new Knight(WHITE));
  setFigure(6,1, new Pawn(WHITE));
  setFigure(6,6, new Pawn(BLACK));
  setFigure(6,7, new Knight(BLACK));

  setFigure(7,0, new Rook(WHITE));
  setFigure(7,1, new Pawn(WHITE));
  setFigure(7,6, new Pawn(BLACK));
  setFigure(7,7, new Rook(BLACK));
}

// Field::Field (const vector<vector <Figure*> >& new_field) {
//   v_field = new_field;
// }

void Field::draw() {
  cout << "--------\n";
  for (int row = 7; row >= 0; --row ) {
    for (int col = 0; col < 8; ++col) {
      cout << v_field[col][row]->symbol();
    }
    cout << "\n";
  }
  cout << "--------\n";
}

void Field::setFigure(int m_letter, int m_digit, Figure* figure) {
  setFigure(Coordinates(m_letter, m_digit), figure);
}

void Field::setFigure(const Coordinates& coord, Figure* figure) {
  delete v_field[coord.column()][coord.row()];
  v_field[coord.column()][coord.row()] = figure;
}

void Field::setFigure(const Coordinates& coord, Figure& figure) {
  setFigure(coord, &figure);
}

Figure& Field::get_figure (int m_letter, int m_digit) const {
  return get_figure(Coordinates(m_letter, m_digit));
}

Figure& Field::get_figure (const Coordinates& coord) const {
  return *v_field[coord.column()][coord.row()];
}


Coordinates Field::king_position (Color current_side) {
  for (int i = 0; i<=7; ++i) {
    for (int k = 0; k<=7; ++k) {
      if (get_figure(i,k).type() == KING && get_figure(i,k).color() == current_side ) {
        return Coordinates(i,k);
      }
    }
  }
}

bool Field::check_check (Color current_side) { // проверка, поставлен ли шах игроку переданного цвета
  Coordinates king_pos = king_position(current_side); // this line is
  // Coordinates king_pos(king_position(current_side)); // equivalent
  // Coordinates king_pos; king_pos = king_position(current_side); // not equivalent
  for (int i = 0; i<=7; ++i) {
    for (int k = 0; k<=7; ++k) {
    //*v_field[i][k].check_eat?
      if (get_figure(i,k).type() != KING && get_figure(i,k).type() != EMPTY_CELL && get_figure(i,k).color() != current_side) {
        EatTurn t  = EatTurn( Coordinates(i,k), king_pos );
        if (get_figure(i,k).check_eat(&t)) {
          return true;
        }
		  }
	  }
  }
  return false;
}

vector<Coordinates> Field::coords_assault_on_king_figs (Color current_side) { // возвращение вектора координат фигур, ставящих шах

  vector<Coordinates> v_coords_assault_on_king_figs = vector<Coordinates>();

  Coordinates king_pos = king_position(current_side);
  for (int i = 0; i<=7; ++i) {
	  for (int k = 0; k<=7; ++k) {
		  if (get_figure(i,k).type() != KING && get_figure(i,k).type() != EMPTY_CELL && get_figure(i,k).color() != current_side) {
        EatTurn t  = EatTurn( Coordinates(i,k), king_pos );
			
			  if (get_figure(i,k).check_eat(&t)) {
					Coordinates assault_on_king_figure = Coordinates(i,k);
					v_coords_assault_on_king_figs.push_back(assault_on_king_figure);
			  }
		  }
	  }
  }
  return v_coords_assault_on_king_figs;
}


vector<Coordinates> Field::king_possibilities (Color current_side) {
  vector<Coordinates> vector_king_possibilities;
  Coordinates center_coord = king_position(current_side);
  int center_row = center_coord.row();
  int center_col = center_coord.column();
	for (int i = center_row - 1; i <= center_row + 1; ++i ) {
		for (int k = center_col - 1; k <= center_col + 1; ++k) {
			if (i != k ) {
				Coordinates el_vector_k_p = Coordinates(i,k);
				vector_king_possibilities.push_back(el_vector_k_p);
			}
		}
	}
	return vector_king_possibilities;
}

bool Field::check_mate (Color current_side) {
  if (!check_check(current_side)) {
      return false;
  }
  // vector<AbstractTurn*> king_possibilities_2(...)

  vector<Coordinates> vector_king_possibilities = king_possibilities(current_side);
  for (int i = 0; i < vector_king_possibilities.size(); ++i) {
    if (get_figure(vector_king_possibilities[i]).type() == EMPTY_CELL) {
      NonEatTurn t(king_position(current_side), vector_king_possibilities[i]);
      if (t.check(*this)) {
        Field field_copy = *this;
        t.apply(field_copy);
        if (!field_copy.check_check(current_side)) {
          return false;
        }
      }
    } // else { ...eat turn... }
    else {
      EatTurn t(king_position(current_side), vector_king_possibilities[i]);
      if (t.check(*this)) {
        Field field_copy = *this;
        t.apply(field_copy);
        if (!field_copy.check_check(current_side)) {
          return false;
        }
      }
    }
  }

  vector<Coordinates> coords_assault_figs =  coords_assault_on_king_figs(current_side);
  // проверка загораживания
  if (coords_assault_figs.size() == 2) {
    return true;
  } else {
    Coordinates coord_assault = coords_assault_figs[0];
    EatTurn e_t = EatTurn(coord_assault, king_position(current_side));
    vector<Coordinates> v_for_check_defense =  get_figure(coord_assault).path(&e_t);
    for (int i = 0; i<=7; ++i) {
      for (int k = 0; k<=7; ++k) {
        if (get_figure(i,k).type() != EMPTY_CELL && get_figure(i,k).color() == current_side) {
          for (int counter = 0; counter < v_for_check_defense.size(); ++counter) {
            NonEatTurn n_e_t = NonEatTurn(Coordinates(i,k), v_for_check_defense[counter]);
            if (n_e_t.check(*this)) {
              Field field_copy = *this;
              n_e_t.apply(field_copy);
              if (!field_copy.check_check(current_side)) {
                return false;
              }
            }
          }
        }
      }
    }
  }

  //проверка съедения атакующей фигуры
  Coordinates coord_assault = coords_assault_figs[0];
  for (int i = 0; i<=7; ++i) {
    for (int k = 0; k<=7; ++k) {
      if (get_figure(i,k).type() != EMPTY_CELL && get_figure(i,k).color() == current_side) {
        EatTurn e_t = EatTurn(Coordinates(i,k), coord_assault);
        if (e_t.check(*this)) {
          Field field_copy = *this;
          e_t.apply(field_copy);
          if (!field_copy.check_check(current_side)) {
            return false;
          }
        }
      }
    }
  }
  return true;
}

void Field::apply(Abstract_Turn* t) {
  t->apply(*this);
  last_turn = t;
}
