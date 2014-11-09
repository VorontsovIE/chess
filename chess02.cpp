// ToDo: сделать так, чтобы время могло кончиться раньше конца хода

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <time.h>
#include <sstream>
#include "turn.h"


using std::ostream;
using std::cin;
using std::cout;
using std::string;
using std::vector;

// std::to_string
template <typename T> string to_string(T value) {
  //create an output string stream
  std::ostringstream os ;

  //throw the value into the string stream
  os << value ;

  //convert the string stream into a string and return
  return os.str() ;
}

// class Game {
// private:
// 	bool is_white;
// 	Field field;
// 	// time_t remain_time1;       /*  http://www.cplusplus.com/forum/beginner/99555/  http://www.cplusplus.com/reference/ctime/  */
// 	// time_t remain_time2;
//   int remain_time1;
//   int remain_time2;
// 	vector <Turn> story;

// public:
//   Game () {
//     is_white = true;
//     field = Field();
//     remain_time1 = 1800;
//     remain_time2 = 1800;
//     story = vector<Turn>();
//   }
// };


// m_letter: 0..7
// m_digit:  0..7
class Coordinates {
  // constuctor (int, int) 
  // constuctor (char|string, int)
  // constuctor (string)
  // ostream <<
  int m_letter, m_digit;
  // string coord01;
  // string coord01_02;
public:
  Coordinates (int new_letter, int new_digit) : m_letter(new_letter), m_digit(new_digit) {
    // m_letter = new_letter;
    // m_digit = new_digit;
  }

  // Coordinates (string new_coord01, int new_coord2) {
  // coord01 = new_coord01;
  // coord2 = new_coord2;
  // }

  // "e2" --> (4,1)
  Coordinates (string coords) {
    if (coords.length() != 2) {
      throw std::invalid_argument("Incorrect coordinates");
    }

    m_letter = tolower(coords[0]) - 'a';
    m_digit = coords[1] - '1';
    
    if (m_letter < 0 || m_letter > 7 || m_digit < 0 || m_digit > 7) {
      throw std::invalid_argument("Incorrect coordinates");
    }
  }

  int column () const {
    return m_letter;
  }

   int row () const {
    return m_digit;
  }

  bool operator == (const Coordinates& other) const {
    return column() == other.column() && row() == other.row();
  }

  friend ostream& operator << (ostream& out, const Coordinates& c);
};


ostream& operator << (ostream& out, const Coordinates& c) {
   out << (char)(c.m_letter + 'a') << (c.m_digit + 1);
   return out;
}

class Turn {
  // constuctor (coordinate_1, coordinate_2)
  // constuctor (string) /?
  // ostream <<          /? template <typename T> std::string to_string(T value) ?
private:
	Coordinates begin, end;
	// string coord_1_2;
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

  //bool check(const Field& field);
  //void apply(Field& field);

  friend ostream& operator << (ostream& out, const Turn& turn);
};

ostream& operator << (ostream& out, const Turn& turn) {
   out << turn.begin << "-" << turn.end;
   return out;
}

// class Field {
// private:
//   vector<vector <Figure*>> v_field;
// public:
//   Field () {
//     v_field = vector<vector<Figure*>>();
//     for (int i = 0; i<=7; ++i) {
//       v_field.push_back(vector<Figure*>());
//       for (int k = 0; k<=7; ++k) {
//     }
// 	/*
//     v_field[0][1] = new Soldier(true); // утечка памяти
//     // вернее так
//     setFigure(0,1, new Soldier(true)); // боремся с утечкой памяти
//     ///.... 
// 	*/
// 	setFigure(0,0, new Rook(true));
// 	setFigure(0,1, new Pawn(true));
// 	setFigure(0,6, new Pawn(false));
// 	setFigure(0,7, new Rook(false));

// 	setFigure(1,0, new Knight(true));
// 	setFigure(1,1, new Pawn(true));
// 	setFigure(1,6, new Pawn(false));
// 	setFigure(1,7, new Knight(false));

// 	setFigure(2,0, new Bishop(true));
// 	setFigure(2,1, new Pawn(true));
// 	setFigure(2,6, new Pawn(false));
// 	setFigure(2,7, new Bishop(false));

// 	setFigure(3,0, new Queen(true));
// 	setFigure(3,1, new Pawn(true));
// 	setFigure(3,6, new Pawn(false));
// 	setFigure(3,7, new Queen(false));

// 	setFigure(4,0, new King(true));
// 	setFigure(4,1, new Pawn(true));
// 	setFigure(4,6, new Pawn(false));
// 	setFigure(4,7, new King(false));

// 	setFigure(5,0, new Bishop(true));
// 	setFigure(5,1, new Pawn(true));
// 	setFigure(5,6, new Pawn(false));
// 	setFigure(5,7, new Bishop(false));

// 	setFigure(6,0, new Knight(true));
// 	setFigure(6,1, new Pawn(true));
// 	setFigure(6,6, new Pawn(false));
// 	setFigure(6,7, new Knight(false));

// 	setFigure(7,0, new Rook(true));
// 	setFigure(7,1, new Pawn(true));
// 	setFigure(7,6, new Pawn(false));
// 	setFigure(7,7, new Rook(false));
//   }

//   Field (vector<vector <Figure>> new_field) {
//     v_field = new_field;
//   }

//   Figure& get_figure (int m_letter, int m_digit) {
//     if (check_frame) {
//       return v_field[m_letter][m_digit];
//     }
//     throw std::logic_error ("Not allowed co-ordinates");
//   }

//   friend class Game;    /* http://www.cplusplus.com/doc/tutorial/Inheritance/ */

// };



// time_t time_start, time_finish;
// time(&time_start);
// ...
// ...
// ...
// time(&time_finish);

// cout << (time_finish - time_start);
// //         v_field[i].push_back(new Empty());
// //       }





// /*
// vector<Cell> field;
// field[n * i + j]


// vector<vector<Cell>> field;
// field[i][j];

// typedef vector<Cell> row;
// vector<row> field;


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

// Rook ladia(WHITE);

// Soldier f(WHITE);
// f.color()

// Soldier(color):Figure(color) {
//   this.color = color
// }
// class Soldier : public Figure {
//   virtual bool check(Turn* t) {
//     return ...;
//   }

// };

// class Officer : public Figure {
//   virtual bool check(Turn* t) {
//     return ...;
//   }
// };


// class Animal {
//   std::string areal;
//   double weight;
// };
// class Vehicle {
//   double velocity;
//   double weight;
// };
// class Horse: public Animal, public Vehicle {
//   Animal::weight
// };

// class VehicleAnimal {
//   Animal animal;
//   Vehicle vehicle;
//   ....
// };

// class Donkey : public VehicleAnimal {
//   // Animal animal;
//   // Vehicle vehicle;
// };

// class Horse {
//   Animal animal;
//   Vehicle vehicle;
//   double weight() {
//     return animal.weight;
//   }
//   double velocity() {
//     return vehicle.velocity;
//   }
// };

// Figure f; // Error!

// Soldier s;
// Officer e;

// s.check();
// e.check();

// vector<Figure*> figs;
// figs.push_back(new Soldier());
// figs.push_back(new Officer());
// figs.push_back(new Soldier());

// for(int i = 0; i < figs.size(); ++i) {
//   if (figs[i]->check()) {
//     cout << *fig[i];
//   }
// }


// Field field;
// field.setfigure(Coord("a1"), new Ladia(true));
// field.setfigure(Coord("a8"), new Ladia(true));
// field.setfigure(Coord("h1"), new Ladia(false));
// field.setfigure(Coord("h8"), new Ladia(false));

// new EmptyCell() { }
// new EmptyCell(bool color) { } // бессмыслица какая-то

// cell --> empty cell
//      --> figure       --> Soldier 
//                       --> Officer
//                       --> ...


// EmptyCell (with unused color)
// */


int main() {
  cout << Coordinates(1,1) << std::endl;
  cout << Coordinates("e2") << std::endl;
  cout << Turn(Coordinates("e2"), Coordinates("e4")) << "\n";
  // cout << Coordinates("e") << std::endl;
  // cout << Coordinates("e2");
// string str;
//   cin >> str;
//   cout << "Your coord: "<< Coordinates(str) << std::endl;
  Turn t(Coordinates("e2"), Coordinates("e9"));

  // AbstractTurn::createTurn("e3:f4");
  Rook ladia(WHITE);
  cout << ladia.check(t) << std::endl;

  return 0;
}