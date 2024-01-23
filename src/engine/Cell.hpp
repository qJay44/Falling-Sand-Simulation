#include "colormap.hpp"

class Cell {
  uint32_t color = 0;

public:
  // The cell contains a sand if the color has a value more than 0x00000000
  const uint32_t& getColor() const {
    return color;
  }

  bool fall(Cell& where) {
    if (!where.getColor()) {
      where.color = color;
      color = 0;

      return true;
    }

    return false;
  }

  void fill() {
    static float i = 0.f;
    color = plasma[int(i) % 256];
    i += 0.2f;
  }
};

