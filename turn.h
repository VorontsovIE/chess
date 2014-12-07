#ifndef _CHESS_TURN_H
#define _CHESS_TURN_H  1

class Abstract_Turn;
class Turn;
class NonEatTurn;
class EatTurn;
class Castle;
class En_Passant;
class Pawn_Promotion;

#include "common.h"
#include "coord.h"
#include "field.h"

class Abstract_Turn {
public:
	virtual bool check(const Field& field) = 0;
	virtual void apply(Field& field) = 0;
	virtual vector<Coordinates> path(const Field& field) = 0;
	virtual bool path_free(const Field& field) = 0;
};

class Turn : public Abstract_Turn {

private:
	Coordinates begin, end;

public:
	Turn(Coordinates new_begin, Coordinates new_end);

  static Abstract_Turn* create_turn(string s);

  Coordinates from ();
	
  Coordinates to ();

  int col_diff();

  int row_diff();

	virtual void apply(Field& field);

	virtual vector<Coordinates> path (const Field& field);

	virtual bool path_free(const Field& field);

  friend ostream& operator << (ostream& out, const Turn& turn);
};

class NonEatTurn : public Turn {
public:
	virtual bool check(const Field& field);
  NonEatTurn (Coordinates new_begin, Coordinates new_end) : Turn(new_begin,new_end) { }
};

class EatTurn : public Turn {
public:
	virtual bool check(const Field& field);
  EatTurn (Coordinates new_begin, Coordinates new_end) : Turn(new_begin,new_end) { }
};

class Castle : public Abstract_Turn {

private:
  Color current_side;
  bool long_or_short;

public:
  Castle(Color current_side_new, bool long_or_short_new) { // true - long, false - short;
    current_side = current_side_new;
    long_or_short = long_or_short_new;
  }

  Color get_color() { 
    return current_side;
  }
  bool get_type_castle () { 
    return long_or_short;
  }

private:
  // ToDo: apply, check и две другие ф-ции пока чисто виртуальны; их надо написать
	void apply_kingside_white (Field& field);

	void apply_kingside_black (Field& field);

	void apply_queenside_white (Field& field);

	void apply_queenside_black (Field& field);
};

class En_Passant : public Turn {
	virtual bool check(const Field& field);

	virtual void apply(Field& field);
  En_Passant (Coordinates new_begin, Coordinates new_end) : Turn(new_begin,new_end) { }
};

class Pawn_Promotion : public Turn {
	private: 
  Figure_Type fig_type;

  Pawn_Promotion (Coordinates new_begin, Coordinates new_end, Figure_Type fig_type_new) : Turn(new_begin,new_end) { 
    fig_type = fig_type_new;
  }

  virtual bool check(const Field& field);
  virtual void apply(Field& field);
  Figure_Type get_fig_type() {
    return fig_type;
  }
};

#endif
