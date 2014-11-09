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
    if (m_letter < 0 || m_letter > 7 || m_digit < 0 || m_digit > 7) {
      throw std::invalid_argument("Incorrect coordinates");
    }
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
