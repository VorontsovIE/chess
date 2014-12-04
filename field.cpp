#include "coord.cpp"
#include "turn.h"
#include "figure.cpp"

class Field {
private:
  vector<vector <Figure*>> v_field;
public:
  Field () {
    v_field = vector<vector<Figure*>>();
    for (int i = 0; i<=7; ++i) {
      v_field.push_back(vector<Figure*>());
      for (int k = 0; k<=7; ++k) {
        v_field[i].push_back(new Empty_cell());
      }
    }

    setFigure(0,0, new Rook(true));
    setFigure(0,1, new Pawn(true));
    setFigure(0,6, new Pawn(false));
    setFigure(0,7, new Rook(false));

    setFigure(1,0, new Knight(true));
    setFigure(1,1, new Pawn(true));
    setFigure(1,6, new Pawn(false));
    setFigure(1,7, new Knight(false));

    setFigure(2,0, new Bishop(true));
    setFigure(2,1, new Pawn(true));
    setFigure(2,6, new Pawn(false));
    setFigure(2,7, new Bishop(false));

    setFigure(3,0, new Queen(true));
    setFigure(3,1, new Pawn(true));
    setFigure(3,6, new Pawn(false));
    setFigure(3,7, new Queen(false));

    setFigure(4,0, new King(true));
    setFigure(4,1, new Pawn(true));
    setFigure(4,6, new Pawn(false));
    setFigure(4,7, new King(false));

    setFigure(5,0, new Bishop(true));
    setFigure(5,1, new Pawn(true));
    setFigure(5,6, new Pawn(false));
    setFigure(5,7, new Bishop(false));

    setFigure(6,0, new Knight(true));
    setFigure(6,1, new Pawn(true));
    setFigure(6,6, new Pawn(false));
    setFigure(6,7, new Knight(false));

    setFigure(7,0, new Rook(true));
    setFigure(7,1, new Pawn(true));
    setFigure(7,6, new Pawn(false));
    setFigure(7,7, new Rook(false));
  }

  Field (const vector<vector <Figure*>>& new_field) {
    v_field = new_field;
  }

  // bool check_frame(int m_letter, int m_digit) {
  //   return m_letter <= 7 && m_letter >= 0  &&  m_digit <= 7 && m_digit >= 0;
  // }

  void setFigure(int m_letter, int m_digit, Figure* figure) {
    setFigure(Coordinates(m_letter, m_digit), figure);
    // if (check_frame(m_letter, m_digit)) {
    //   delete v_field[m_letter][m_digit];
    //   v_field[m_letter][m_digit] = figure;
    //   return;
    // }
    // throw std::logic_error ("Not allowed co-ordinates");
  }

  void setFigure(const Coordinates& coord, Figure* figure) {
    delete v_field[coord.column()][coord.row()];
    v_field[coord.column()][coord.row()] = figure;
  }

  Figure& get_figure (int m_letter, int m_digit) {
    return get_figure(Coordinates(m_letter, m_digit));
    // if (check_frame(m_letter, m_digit)) {
    //   return *v_field[m_letter][m_digit];
    // }
    // throw std::logic_error ("Not allowed co-ordinates");
  }

  Figure& get_figure (const Coordinates& coord) {
    return *v_field[coord.column()][coord.row()];
  }


  Coordinates king_position (Color current_side) {
    for (int i = 0; i<=7; ++i) {
      for (int k = 0; k<=7; ++k) {
        if (get_figure(i,k).type() == KING && get_figure(i,k).colour() == current_side ) {
          return Coordinates(i,k);
        }
      }
    }
  }

  bool check_check (Color current_side) { // проверка, поставлен ли шах игроку переданного цвета

    Coordinates king_position = king_position(current_side); // this line is
    // Coordinates king_position(king_position(current_side)); // equivalent
    // Coordinates king_position; king_position = king_position(current_side); // not equivalent

	  for (int i = 0; i<=7; ++i) {
		  for (int k = 0; k<=7; ++k) {
			//*v_field[i][k].check_eat?
			  if (get_figure(i,k).type() != KING && get_figure(i,k).type() != EMPTY_CELL && get_figure(i,k).colour() != current_side) {
          EatTurn t  = EatTurn( Coordinates(i,k), king_position );
				  if (get_figure(i,k).check_eat(&t)) {
						return true;
				  }
			  }
		  }
	  }
	  return false;
  }

  vector<Coordinates> coords_assault_on_king_figs (Color current_side) { // возвращение вектора координат фигур, ставящих шах

    vector<Coordinates> v_coords_assault_on_king_figs = vector<Coordinates>();

    Coordinates king_position = king_position(current_side);
	  for (int i = 0; i<=7; ++i) {
		  for (int k = 0; k<=7; ++k) {
			  if (get_figure(i,k).type() != KING && get_figure(i,k).type() != EMPTY_CELL && get_figure(i,k).colour() != current_side) {
          EatTurn t  = EatTurn( Coordinates(i,k), king_position );
				
				  if (get_figure(i,k).check_eat(&t)) {
						Coordinates assault_on_king_figure = Coordinates(i,k);
						v_coords_assault_on_king_figs.push_back(assault_on_king_figure);
				  }
			  }
		  }
	  }
	  return v_coords_assault_on_king_figs;
  }


  vector<Coordinates> king_possibilities (Color current_side) {
	  vector<Coordinates> vector_king_possibilities;
	  Coordinates center_coord = king_position(current_side);
	  center_row = center_coord.row();
	  center_col = center_coord.column();
	for (int i = center_row - 1; i <= center_row + 1; ++i ) {
		for (int k = center_col - 1; k <= center_col + 1; ++k) {
			if (i != k {
				Coordinates el_vector_k_p = Coordinates(i,k);
				vektor_king_possibilities.push_back(el_vector_k_p);
			}
		}
	}
	return vector_king_possibilities;
  }

  bool check_mate (Color current_side) {
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



    // проверка загораживания
  	if (coords_assault_on_king_figs.size() == 2) {
  		return true;
  	} else {
  		Coordinates coord_assault = coords_assault_on_king_figs[0];
  		EatTurn e_t = EatTurn(coord_assault, king_position(current_side));
  		vector<Coordinates> v_for_check_defense =  get_figure(coord_assault).path(*e_t);
  		for (int i = 0; i<=7; ++i) {
  		  for (int k = 0; k<=7; ++k) {
  				if (get_figure(i,k).type() != EMPTY_CELL && get_figure(i,k).colour() == current_side) {
  					for (int counter = 0; counter < v_for_check_defence.size(); ++counter) {
  						NonEatTurn n_e_t = NonEatTurn(Coordinates(i,k), v_for_check_defence[counter]);
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
  	Coordinates coord_assault = coords_assault_on_king_figs[0];
    for (int i = 0; i<=7; ++i) {
  	  for (int k = 0; k<=7; ++k) {
  			if (get_figure(i,k).type() != EMPTY_CELL && get_figure(i,k).colour() == current_side) {
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

  Figure* choose_figure() {
  	int choice;
  	cout << "Choose the Figure what you want: 1 - Rook, 2 - Knight, 3 - Bishop, 4 - Queen";
  	cin >> choice;
  	if (choice == 1) {
  		return new Rook();
  	}
  	else if (choice == 2) {
  		return new Knight();
  	}
  	else if (choice == 3) {
  		return new Bishop();
  	}
  	else if (choice == 4) {
  		return new Queen();
  	}
  }

  friend class Game;    /* http://www.cplusplus.com/doc/tutorial/Inheritance/ */

};

