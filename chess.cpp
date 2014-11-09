// ToDo: сделать так, чтобы время могло кончиться раньше конца хода

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <time.h>
#include <sstream>

#include "coord.cpp"
#include "turn.h"
#include "figure.cpp"
#include "field.cpp"
#include "game.cpp"


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