#include "Grid.hpp"

#define IX(x, y) ((x) + (y) * (COLUMNS))
#define BRUSH_SIZE 5

Grid::Grid() {}
Grid::~Grid() {}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();

  sf::VertexArray vertices{sf::Quads, ROWS * COLUMNS * 4};
  for (int x = 0; x < COLUMNS; x++) {
    for (int y = 0; y < ROWS; y++) {
      int index = IX(x, y);
      sf::VertexArray quad{sf::Quads, 4};
      sf::Color color = sf::Color(grid[index].getColor());

      quad[0].position = sf::Vector2f(x * SCALE, y * SCALE);
      quad[1].position = sf::Vector2f(x * SCALE + SCALE, y * SCALE);
      quad[2].position = sf::Vector2f(x * SCALE + SCALE, y * SCALE + SCALE);
      quad[3].position = sf::Vector2f(x * SCALE, y * SCALE + SCALE);

      quad[0].color = color;
      quad[1].color = color;
      quad[2].color = color;
      quad[3].color = color;

      vertices.append(quad[0]);
      vertices.append(quad[1]);
      vertices.append(quad[2]);
      vertices.append(quad[3]);
    }
  }
  target.draw(vertices, states);
}

void Grid::add(sf::Vector2i pos) {
  int col = std::clamp(pos.x / SCALE, 0, COLUMNS - 1);
  int row = std::clamp(pos.y / SCALE, 0, ROWS - 1);
  grid[IX(col, row)].fill();
}

void Grid::update() {
  static const auto leftPriority = [this](Cell& cell, int x, int y) {
    if (!cell.fall(grid[IX(x, y + 1)]) && x - 1 > 0)             // Try to fall bellow
      if (!cell.fall(grid[IX(x - 1, y + 1)]) && x + 1 < COLUMNS) // Try to fall bellow on the left side
        cell.fall(grid[IX(x + 1, y + 1)]);                       // Try to fall bellow on the right side
  };

  static const auto rightPriority = [this](Cell& cell, int x, int y) {
    if (!cell.fall(grid[IX(x, y + 1)]) && x + 1 > 0)             // Try to fall bellow
      if (!cell.fall(grid[IX(x + 1, y + 1)]) && x - 1 < COLUMNS) // Try to fall bellow on the right side
        cell.fall(grid[IX(x - 1, y + 1)]);                       // Try to fall bellow on the left side
  };

  for (int x = COLUMNS - 1; x >= 0; x--) {
    for (int y = ROWS - 1; y >= 0; y--) {
      Cell& cell = grid[IX(x, y)];

      if (cell.getColor() && y + 1 < ROWS)
        rand() % 2 ? leftPriority(cell, x, y) : rightPriority(cell, x, y);
    }
  }
}

