#include <stdint.h>

class Cell {
  uint32_t color = 0;

public:
  // The cell contains a sand if color has a value more than 0x00000000
  const uint32_t& getColor() const {
    return color;
  }

  bool fall(Cell& rhs) {
    if (!getColor()) {
      color = rhs.color;
      rhs.color = 0;

      return true;
    }

    return false;
  }

  void add() {
    color = 0xffff00ff;
  }
};

