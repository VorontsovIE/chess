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

