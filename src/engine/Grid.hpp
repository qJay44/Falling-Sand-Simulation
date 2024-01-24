#include "../pch.h"
#include "Cell.hpp"
#include <vector>

class Grid : public sf::Drawable, public sf::Transformable {
  std::vector<Cell> grid;
  std::vector<sf::Vertex>vertices;

  public:
    Grid();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void add(sf::Vector2i pos);
    void update();
};

