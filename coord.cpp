#include "coord.h"

Coordinates::Coordinates (int new_letter, int new_digit) : m_letter(new_letter), m_digit(new_digit) {
  // m_letter = new_letter;
  // m_digit = new_digit;
  if (m_letter < 0 || m_letter > 7 || m_digit < 0 || m_digit > 7) {
    throw std::invalid_argument("Incorrect coordinates: Coordinates(" +std::to_string(new_letter) + "," + std::to_string(new_digit) + ")");
  }
}

// "e2" --> (4,1)
Coordinates::Coordinates (string coords) {
  if (coords.length() != 2) {
    throw std::invalid_argument("Incorrect coordinates: Coordinates(" + coords + ")");
  }

  m_letter = tolower(coords[0]) - 'a';
  m_digit = coords[1] - '1';
  
  if (m_letter < 0 || m_letter > 7 || m_digit < 0 || m_digit > 7) {
    throw std::invalid_argument("Incorrect coordinates: Coordinates(" + coords + ")");
  }
}

int Coordinates::column () const {
  return m_letter;
}

 int Coordinates::row () const {
  return m_digit;
}

bool Coordinates::operator == (const Coordinates& other) const {
  return column() == other.column() && row() == other.row();
}

ostream& operator << (ostream& out, const Coordinates& c) {
   out << (char)(c.m_letter + 'a') << (c.m_digit + 1);
   return out;
}
