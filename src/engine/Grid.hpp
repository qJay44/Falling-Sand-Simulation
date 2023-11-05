#include "myutils.hpp"
#include "Cell.hpp"

#define IX(x, y) ((x) + (y) * (COLUMNS))

class Grid : public sf::Drawable, public sf::Transformable {
  std::vector<Cell> grid;

  public:
    Grid() {
      static bool initialized = false;

      if (!initialized) {
        grid.resize(ROWS * COLUMNS);
        grid.reserve(ROWS * COLUMNS);

        for (int x = 0; x < COLUMNS; x++) {
          for (int y = 0; y < ROWS; y++) {
            Cell& cell = grid[IX(x, y)];
            cell.setPosition(sf::Vector2f{sf::Vector2i{x * SCALE, y * SCALE}});
            cell.setSize({SCALE, SCALE});
            cell.setFillColor(sf::Color::Black);
          }
        }
        initialized = true;
      }
    }

    ~Grid() {}

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
      states.transform *= getTransform();

      for (const Cell& cell : grid)
        target.draw(cell, states);
    }

    void addElement(uint8_t type, sf::Vector2i pos) {
      sf::Vector2i n = pos / SCALE;
      n.x = std::clamp(n.x, 0, COLUMNS - 1);
      n.y = std::clamp(n.y, 0, ROWS - 1);
      Cell& cell = grid[IX(n.x, n.y)];

      if (!cell.hasContent())
        cell.update(new Element(type));
    }

    void update() {
      for (int x = COLUMNS - 1; x >= 0; x--) {
        for (int y = ROWS - 1; y >= 0; y--) {
          Cell& cell = grid[IX(x, y)];
          if (cell.hasContent()) {
            switch (cell.getElement()->getType()) {
              case SAND:
                if (y + 1 < ROWS) {
                  Cell& bottom = grid[IX(x, y + 1)];
                  if (bottom.hasContent()) {
                    switch (bottom.getElement()->getType()) {
                      case SAND:
                        // Try to move to the down-left cell
                        if (x - 1 >= 0) {
                          Cell& bottomLeft = grid[IX(x - 1, y + 1)];
                          if (!bottomLeft.hasContent())
                            bottomLeft.update(cell);
                          // Try to move to the down-right cell
                          else if (x + 1 < COLUMNS) {
                            Cell& bottomRight = grid[IX(x + 1, y + 1)];
                            if (!bottomRight.hasContent())
                              bottomRight.update(cell);
                          }
                        }
                        break;
                      case WATER:
                        cell.swap(bottom);
                        break;
                    }
                    // Move to the bottom cell
                  } else bottom.update(cell);
                }
                break;
              case WATER:
                if (y + 1 < ROWS) {
                  Cell& bottom = grid[IX(x, y + 1)];
                  if (!bottom.hasContent()) {
                    bottom.update(cell);
                  // Try to move to the left cell
                  } else if (x - 1 >= 0) {
                      Cell& bottomLeft = grid[IX(x - 1, y)];
                      if (!bottomLeft.hasContent())
                        bottomLeft.update(cell);
                      // Try to move to the right cell
                      else if (x + 1 < COLUMNS) {
                        Cell& bottomRight = grid[IX(x + 1, y)];
                        if (!bottomRight.hasContent())
                          bottomRight.update(cell);
                      }
                  }
              break;
            }
          }
        }
      }
    }
  }
};

