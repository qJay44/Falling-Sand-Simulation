#include <cmath>
#include <stdio.h>
#include "Grid.hpp"

#define IX(x, y) ((x) + (y) * (COLUMNS))

Grid::Grid() {
  grid.resize(ROWS * COLUMNS);
  grid.reserve(ROWS * COLUMNS);
  vertices.resize(ROWS * COLUMNS * 4);
  vertices.reserve(ROWS * COLUMNS * 4);

  int i = 0;
  for (int x = 0; x < COLUMNS; x++) {
    for (int y = 0; y < ROWS; y++) {
      int ii = i++ << 2;
      int index = IX(x, y);

      vertices[ii + 0] = {sf::Vector2f(x * SCALE, y * SCALE), sf::Color(0)};
      vertices[ii + 1] = {sf::Vector2f(x * SCALE + SCALE, y * SCALE), sf::Color(0)};
      vertices[ii + 2] = {sf::Vector2f(x * SCALE + SCALE, y * SCALE + SCALE), sf::Color(0)};
      vertices[ii + 3] = {sf::Vector2f(x * SCALE, y * SCALE + SCALE), sf::Color(0)};

      grid[index].setupVertices(vertices[ii], vertices[ii + 1], vertices[ii + 2], vertices[ii + 3]);
    }
  }
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(&vertices[0], vertices.size(), sf::Quads, states);
}

void Grid::add(sf::Vector2i pos) {
  for (int i = -BRUSH_SIZE; i < BRUSH_SIZE; i++) {
    for (int j = -BRUSH_SIZE; j < BRUSH_SIZE; j++) {
      sf::Vector2i v(pos.x - (pos.x + (i * SCALE)), pos.y - (pos.y + (j * SCALE)));
      if (std::sqrt(v.x * v.x + v.y * v.y) < BRUSH_SIZE * SCALE) {
        int col = std::clamp(pos.x / SCALE + i, 0, COLUMNS - 1);
        int row = std::clamp(pos.y / SCALE + j, 0, ROWS - 1);
        grid[IX(col, row)].fill();
      }
    }
  }
}

void Grid::update() {
  static const auto leftPriority = [this](Cell& cell, int x, int y) {
    if (!cell.fall(grid[IX(x, y + 1)]) && x - 1 >= 0)            // Try to fall bellow
      if (!cell.fall(grid[IX(x - 1, y + 1)]) && x + 1 < COLUMNS) // Try to fall bellow on the left side
        cell.fall(grid[IX(x + 1, y + 1)]);                       // Try to fall bellow on the right side
  };

  static const auto rightPriority = [this](Cell& cell, int x, int y) {
    if (!cell.fall(grid[IX(x, y + 1)]) && x + 1 < COLUMNS)  // Try to fall bellow
      if (!cell.fall(grid[IX(x + 1, y + 1)]) && x - 1 >= 0) // Try to fall bellow on the right side
        cell.fall(grid[IX(x - 1, y + 1)]);                  // Try to fall bellow on the left side
  };

  for (int x = COLUMNS - 1; x >= 0; x--) {
    for (int y = ROWS - 1; y >= 0; y--) {
      Cell& cell = grid[IX(x, y)];

      if (cell.isFilled() && y + 1 < ROWS)
        rand() % 2 ? leftPriority(cell, x, y) : rightPriority(cell, x, y);
    }
  }
}

