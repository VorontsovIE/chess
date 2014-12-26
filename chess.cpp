#include <iostream>
#include "game.cpp"

using namespace std;

int main() {
  Game new_game;
  new_game.draw();
  while (! new_game.finished()) {
    new_game.make_turn();
    new_game.draw();
    // break;
  }
  // cout << new_game.result();

  // system("pause");
  return 0;
}