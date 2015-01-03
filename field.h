#ifndef _CHESS_FIELD_H
#define _CHESS_FIELD_H  1

class Field;

#include "common.h"
#include "figure.h"
#include "coord.h"



class Field {
private:
  vector<vector <FigurePtr> > v_field;
  bool king_can_go_away(Color current_side);

public:
  Abstract_Turn* last_turn;
  Field (Abstract_Turn* last_turn = NULL);
  Field (const vector<vector <FigurePtr> >& new_field);

  void moveFigure(const Coordinates& coord_begin, const Coordinates& coord_end);
  void setFigure(int m_letter, int m_digit, FigurePtr figure);
  void setFigure(const Coordinates& coord, FigurePtr figure);

  Figure& get_figure (int m_letter, int m_digit) const;
  Figure& get_figure (const Coordinates& coord) const;


  Coordinates king_position (Color current_side);

  void draw();

  bool check_check (Color current_side);

  vector<Coordinates> coords_assault_on_king_figs (Color current_side);

  vector<Coordinates> king_possibilities (Color current_side);

  bool check_mate (Color current_side);

  Figure_Type choose_figure();

  void apply(Abstract_Turn* t);

  // friend class Game;    /* http://www.cplusplus.com/doc/tutorial/Inheritance/ */
};

#endif
