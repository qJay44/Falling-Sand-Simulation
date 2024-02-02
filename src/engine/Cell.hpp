#include "../pch.h"
#include "colormap.hpp"

class Cell {

  sf::Vertex* v1 = nullptr;
  sf::Vertex* v2 = nullptr;
  sf::Vertex* v3 = nullptr;
  sf::Vertex* v4 = nullptr;

  void setColor(const sf::Color& col) {
    v1->color = col;
    v2->color = col;
    v3->color = col;
    v4->color = col;
  }

  void clearColor() {
    v1->color = sf::Color(0);
    v2->color = sf::Color(0);
    v3->color = sf::Color(0);
    v4->color = sf::Color(0);
  }

public:
  const bool isFilled() const {
    return v1->color.a; // Contains a sand if an alpha value more than 0
  }

  bool fall(Cell& where) {
    if (!where.isFilled()) {
      where.setColor(v1->color);
      clearColor();

      return true;
    }

    return false;
  }

  void setupVertices(sf::Vertex& a, sf::Vertex& b, sf::Vertex& c, sf::Vertex& d) {
    v1 = &a;
    v2 = &b;
    v3 = &c;
    v4 = &d;
  }

  void fill() {
    constexpr float step = 1.f / (BRUSH_SIZE * 2 * BRUSH_SIZE * 2);
    static bool reversed = false;
    static float i = 0.f;

    if (!isFilled()) {
      setColor(sf::Color(plasma[(int)i]));

      // Go backwards if "i" reached the end and vice versa
      if (reversed) {
        i -= step;
        reversed = !(i <= 0);
      } else {
        i += step;
        reversed = i >= 255;
      }
    }
  }
};

