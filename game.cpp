#include "common.h"
#include "field.cpp"
#include "turn.h"


class Game {
	//проверка изменений
private:
  Color current_side;
  Field field;
  vector <Abstract_Turn*> story;
  int remain_time1;
  int remain_time2;

public:
  Game () {
    current_side = WHITE;
    field = Field();
    remain_time1 = 1800;
    remain_time2 = 1800;
  }

  bool finished () {
    // сделать field.check_mate() и field.stale_mate()  и проверку шаха
    return check_time_finished() || field.check_mate() || field.stale_mate();
  }

  bool check_time_finished() {
    return remain_time1 <= 0 || remain_time2 <= 0;
  }

  void make_turn() {
    string s;
    cout << "Enter your turn";
    cin >> s;
    Abstract_Turn* t = Turn::create_turn(s);
    if (t->check(field)) {
      t->apply(field);
    } // а что если ход некорректный?

    story.push_back(t);

    if (finished()) { // что если ничья? пат / конец времени
      cout << current_side << " has won\n";
      system("pause");
      exit(0);
    }
   // current_side == WHITE ? current_side = BLACK : current_side = WHITE;
   current_side = (current_side == WHITE) ?  BLACK : WHITE;

   //x = condition ? if_true : if_false

  } 

};


// time_t time_start, time_finish;
// time(&time_start);
// ...
// ...
// ...
// time(&time_finish);

// cout << (time_finish - time_start);
// //         v_field[i].push_back(new Empty());
// //       }
