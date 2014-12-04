#ifndef _CHESS_COORD_H
#define _CHESS_COORD_H  1

#include "common.h"
// m_letter: 0..7
// m_digit:  0..7
class Coordinates {
  // constuctor (int, int) 
  // constuctor (char|string, int)
  // constuctor (string)
  // ostream <<
  int m_letter, m_digit;

public:
  Coordinates (int new_letter, int new_digit);

  // "e2" --> (4,1)
  explicit Coordinates (string coords);
  int column () const;
  int row () const;
  bool operator == (const Coordinates& other) const;

  friend ostream& operator << (ostream& out, const Coordinates& c);
};

#endif
