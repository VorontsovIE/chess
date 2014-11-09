#ifndef _CHESS_TURN_H
#define _CHESS_TURN_H  1

#include "coord.cpp"

class Abstract_Turn {
	virtual bool check(const Field& field) = 0;
	virtual void apply(Field& field) = 0;
	virtual vector<Coordinates> path(const Field& field) = 0;
	virtual bool path_free(const Field& field) = 0;
	//<<
	// virtual string to_string() = 0;
};

class Turn : public Abstract_Turn {

private:
	Coordinates begin, end;

public:
	Turn(Coordinates new_begin, Coordinates new_end) : begin(new_begin), end(new_end) {	
    if (new_begin == new_end) {
      throw std::invalid_argument("Incorrect coordinates"); 
    }
  }

  Coordinates from () {
    return begin;
  }
	
   Coordinates to () {
    return end;
  }

  int col_diff() {
    return to().column() - from().column();
  }

  int row_diff() {
    return to().row() - from().row();
  }

	virtual void apply(Field& field) {
		field.setFigure(end, field.get_figure(begin));
		field.setFigure(begin, new Empty_cell());
	} 

	virtual vector<Coordinates> path (const Field& field) {
		return field.get_figure(begin).path(this);
		// field.get_figure(begin).path(begin, end)
	}

	virtual bool path_free(const Field& field) {
		vector<Coordinates> path_vector = path(field);
		for (int i = 0; i < path_vector.size(); ++i) {
			if (field.get_figure(path_vector[i]).is_empty() == false) {
				return false;
			}
		}
		return true;
	}

  friend ostream& operator << (ostream& out, const Turn& turn);
};

ostream& operator << (ostream& out, const Turn& turn) {
   out << turn.begin << "-" << turn.end;
   return out;
}

class NonEatTurn : public Turn {
	virtual bool check(const Field& field) {
		return field.get_figure(begin).check_not_eat(this);
	}

	<<
};

class EatTurn : public Turn {
	
	virtual bool check(const Field& field) {
		return field.get_figure(begin).check_eat(this);
	}

	<<
};

class Castle : public Abstract_Turn {

	check

		void apply_kingside_white (Field& field) {
		field.setFigure(0, 6, new King(true)); // Можно не создавать новых, а воспользоваться старыми королем и ладьей
		field.setFigure(0, 4, new Empty_cell());
		field.setFigure(0, 5, new Rook(true));
		field.setFigure(0, 7, new Empty_cell());
	}

	void apply_kingside_black (Field& field) {
		field.setFigure(7, 6, new King(false));
		field.setFigure(7, 4, new Empty_cell());
		field.setFigure(7, 5, new Rook(false));
		field.setFigure(7, 7, new Empty_cell());
	}

	void apply_queenside_white (Field& field) {
		field.setFigure(0, 2, new King(true));
		field.setFigure(0, 4, new Empty_cell());
		field.setFigure(0, 3, new Rook(true));
		field.setFigure(0, 0, new Empty_cell());
	}

	void apply_queenside_black (Field& field) {
		field.setFigure(7, 2, new King(false));
		field.setFigure(7, 4, new Empty_cell());
		field.setFigure(7, 3, new Rook(false));
		field.setFigure(7, 0, new Empty_cell());
	}
	

	<<
};

class En_Passant : public Turn {
	check
	apply
	<<
};

class Pawn_Promotion : public Turn {
	check
	
	virtual void apply(Field& field) {
		field.setFigure(end, field.choose_figure());
		field.setFigure(begin, new Empty_cell());
	}

	<<
};

#endif
