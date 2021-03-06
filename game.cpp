#include "common.h"
#include "turn.h"
#include "field.h"
#include "coord.h"
#include <thread>

// Написать Field#draw; Turn.create_turn (проблема: ему скорее всего нужен field чтобы узнать тип хода)
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
    remain_time1 = 10;
    remain_time2 = 10;
    thread time_checker(&Game::run_clock, this);
    time_checker.detach();
  }

  void run_clock() {
    while(true) {
      std::this_thread::sleep_for(std::chrono::seconds(1)); // спит минимум(!) секунду
      update_timer();
    }
  }

  void update_timer() {
    if (current_side == WHITE) {
      remain_time1 -= 1; // нет гарантий что прошла ровно секунда (но не меньше секунды)
    } else {
      remain_time2 -= 1;
    }
    if (remain_time1 <= 0) {
      cout << "White has lost the game\n";
      // cin.ignore(1); // can be concurrent with cin >> turn;
      exit(0);
    }
    if (remain_time2 <= 0) {
      cout << "Black has lost the game\n";
      // cin.ignore(1);
      exit(0);
    }
  }

  bool finished () {
    // сделать field.check_mate() и field.stale_mate()  и проверку шаха
    // return check_time_finished() || field.check_mate(current_side) || field.stale_mate();
    return check_time_finished() || field.check_mate(current_side);
  }

  bool check_time_finished() {
    return remain_time1 <= 0 || remain_time2 <= 0;
  }

  void make_turn() {
    Abstract_Turn* t;
    while (true) {
      string turn_string;
      cout << "Enter your turn ";
      getline(cin, turn_string);
      t = Turn::create_turn(turn_string, field);

      if (t->check(field)) {
        // t->apply(field);
        field.apply(t);
        break;
        // field.draw();
      } // а что если ход некорректный?
      cout << "Turn was wrong\n";
    }
    story.push_back(t);

    update_timer();
    current_side = (current_side == WHITE) ?  BLACK : WHITE;
    if (finished()) { // что если ничья? пат / конец времени
      cout << current_side << " has lost\n";
      // system("pause");
      // exit(0);
    }
   // current_side == WHITE ? current_side = BLACK : current_side = WHITE;

   //x = condition ? if_true : if_false

  } 

  void draw() {
    field.draw();
    cout << ((current_side == WHITE) ?  "Turn: white" : "Turn: black") << "\n";
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
