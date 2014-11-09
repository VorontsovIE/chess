// ToDo: сделать так, чтобы время могло кончиться раньше конца хода

#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
#include<time.h>

using std::cin;
using std::cout;
using std::string;
using std::vector;

class Game {
private:
	bool is_white;
	Field field;
	// time_t remain_time1;       /*  http://www.cplusplus.com/forum/beginner/99555/  http://www.cplusplus.com/reference/ctime/  */
	// time_t remain_time2;
  int remain_time1;
  int remain_time2;
	vector <Turn> story;

public:
  Game () {
    is_white = true;
    field = Field();
    remain_time1 = 1800;
    remain_time2 = 1800;
    story = vector<Turn>();
  }
};

class Turn {
  // constuctor (coordinate_1, coordinate_2)
  // constuctor (string)
  // ostream <<
};

class Coordinates {
  // constuctor (int, int) 
  // constuctor (char|string, int)
  // constuctor (string)
  // ostream <<
};



class Field {
private:
  vector<vector <Figure*>> v_field;
public:
  Field () {
    v_field = vector<vector<Figure*>>();
    for (int i = 0; i<=7; ++i) {
      v_field.push_back(vector<Figure*>());
      for (int k = 0; k<=7; ++k) {
        v_field[i].push_back(new Empty());
      }
    }
    v_field[0][1] = new Soldier(true); // утечка памяти
    // вернее так
    setFigure(0,1, new Soldier(true)); // боремся с утечкой памяти
    
    ///.... 
  }

  Field (vector<vector <Figure>> new_field) {
    v_field = new_field;
  }

  Figure& get_figure (int letter, int digit) {
    if (check_frame) {
      return v_field[letter][digit];
    }
    throw std::logic_error ("Not allowed co-ordinates");
  }

  friend class Game;    /* http://www.cplusplus.com/doc/tutorial/Inheritance/ */

};


class Figure {
// цветные фигуры
};


// time_t time_start, time_finish;
// time(&time_start);
// ...
// ...
// ...
// time(&time_finish);

// cout << (time_finish - time_start);





/*
vector<Cell> field;
field[n * i + j]


vector<vector<Cell>> field;
field[i][j];

typedef vector<Cell> row;
vector<row> field;



class Figure {
private:
  bool is_white;
public:
  virtual bool check(Turn t) = 0; //{return false;}
  bool color();
};

class Soldier : public Figure {
  virtual bool check(Turn t) {
    return ...;
  }

};

class Officer : public Figure {
  virtual bool check(Turn t) {
    return ...;
  }
};


class Animal {
  std::string areal;
  double weight;
};
class Vehicle {
  double velocity;
  double weight;
};
class Horse: public Animal, public Vehicle {
  Animal::weight
};

class VehicleAnimal {
  Animal animal;
  Vehicle vehicle;
  ....
};

class Donkey : public VehicleAnimal {
  // Animal animal;
  // Vehicle vehicle;
};

class Horse {
  Animal animal;
  Vehicle vehicle;
  double weight() {
    return animal.weight;
  }
  double velocity() {
    return vehicle.velocity;
  }
};

Figure f; // Error!

Soldier s;
Officer e;

s.check();
e.check();

vector<Figure*> figs;
figs.push_back(new Soldier());
figs.push_back(new Officer());
figs.push_back(new Soldier());

for(int i = 0; i < figs.size(); ++i) {
  if (figs[i]->check()) {
    cout << *fig[i];
  }
}


Field field;
field.setfigure(Coord("a1"), new Ladia(true));
field.setfigure(Coord("a8"), new Ladia(true));
field.setfigure(Coord("h1"), new Ladia(false));
field.setfigure(Coord("h8"), new Ladia(false));

new EmptyCell() { }
new EmptyCell(bool color) { } // бессмыслица какая-то

cell --> empty cell
     --> figure       --> Soldier 
                      --> Officer
                      --> ...


EmptyCell (with unused color)
*/