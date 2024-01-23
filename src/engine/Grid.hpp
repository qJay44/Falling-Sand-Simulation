#include "../pch.h"
#include "Cell.hpp"
#include <array>

class Grid : public sf::Drawable, public sf::Transformable {
  std::array<Cell, ROWS * COLUMNS> grid;

  public:
    Grid();
    ~Grid();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void add(sf::Vector2i pos);
    void update();
};

