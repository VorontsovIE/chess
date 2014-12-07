#ifndef _CHESS_FIELD_H
#define _CHESS_FIELD_H  1

class Field;

#include "common.h"
#include "figure.h"
#include "coord.h"

class Field {
private:
  vector<vector <Figure*> > v_field;
public:
  Field ();
  Field (const vector<vector <Figure*> >& new_field);

  void setFigure(int m_letter, int m_digit, Figure* figure);
  void setFigure(const Coordinates& coord, Figure* figure);

  Figure& get_figure (int m_letter, int m_digit);
  Figure& get_figure (const Coordinates& coord);


  Coordinates king_position (Color current_side);

  bool check_check (Color current_side);

  vector<Coordinates> coords_assault_on_king_figs (Color current_side);

  vector<Coordinates> king_possibilities (Color current_side);

  bool check_mate (Color current_side);

  Figure* choose_figure();

  // friend class Game;    /* http://www.cplusplus.com/doc/tutorial/Inheritance/ */
};

#endif
