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
	virtual bool check(const Field& field);
};

class EatTurn : public Turn {
	virtual bool check(const Field& field);
};

class Castle : public Abstract_Turn {
	void apply_kingside_white (Field& field);

	void apply_kingside_black (Field& field);

	void apply_queenside_white (Field& field);

	void apply_queenside_black (Field& field);
};

class En_Passant : public Turn {
	virtual bool check(const Field& field);

	virtual void apply(Field& field);
};

class Pawn_Promotion : public Turn {
	virtual bool check(const Field& field);
	
	virtual void apply(Field& field);
};

#endif
