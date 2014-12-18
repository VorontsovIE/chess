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
  virtual Turn_Type turn_type() = 0;
	virtual bool check(const Field& field) = 0;
  virtual vector<Coordinates> path(const Field& field) = 0;
  virtual bool path_free(const Field& field) = 0;
private:
  virtual void apply(Field& field) = 0;
  friend class Field;
};

class Turn : public Abstract_Turn {
protected:
	Coordinates begin, end;
	Turn(Coordinates new_begin, Coordinates new_end);

public:

  static Abstract_Turn* create_turn(string s);

  Coordinates from ();
	
  Coordinates to ();

  int col_diff();

  int row_diff();

	virtual vector<Coordinates> path (const Field& field);

	virtual bool path_free(const Field& field);

  friend ostream& operator << (ostream& out, const Turn& turn);

protected:
  virtual void apply(Field& field);
  friend class Field;
};

class NonEatTurn : public Turn {
public:
	virtual bool check(const Field& field);
  NonEatTurn (Coordinates new_begin, Coordinates new_end) : Turn(new_begin,new_end) { }
   virtual Turn_Type turn_type() {return NON_EAT_TURN;}
};

class EatTurn : public Turn {
public:
	virtual bool check(const Field& field);
  EatTurn (Coordinates new_begin, Coordinates new_end) : Turn(new_begin,new_end) { }
  virtual Turn_Type turn_type() {return EAT_TURN;}
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

  virtual Turn_Type turn_type() {return CASTLE;}

  Color get_color() { 
    return current_side;
  }
  bool get_type_castle () { 
    return long_or_short;
  }

  // ToDo: apply, check и две другие ф-ции пока чисто виртуальны; их надо написать!
private:
	void apply_kingside_white (Field& field);

	void apply_kingside_black (Field& field);

	void apply_queenside_white (Field& field);

	void apply_queenside_black (Field& field);

protected:
  virtual void apply(Field& field);
  friend class Field;
};

class En_Passant : public Turn {
  bool check_history_pass();
	virtual bool check(const Field& field);

  En_Passant (Coordinates new_begin, Coordinates new_end) : Turn(new_begin,new_end) { }
  virtual Turn_Type turn_type() {return EN_PASSANT;}
protected:
  virtual void apply(Field& field);
  friend class Field;
};

class Pawn_Promotion : public Turn {
	private: 
  Figure_Type fig_type;

public:
  Pawn_Promotion (Coordinates new_begin, Coordinates new_end, Figure_Type fig_type_new) : Turn(new_begin,new_end) { 
    fig_type = fig_type_new;
  }
  virtual Turn_Type turn_type() {return PAWN_PROMOTION;}

  virtual bool check(const Field& field);
  Figure_Type get_fig_type() {
    return fig_type;
  }

  static Figure_Type choose_figure();
protected:
  virtual void apply(Field& field);
  friend class Field;
};

#endif
