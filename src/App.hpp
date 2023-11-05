#include "engine/Grid.hpp"

class App {
  sf::RenderWindow window;
  sf::Font genericFont;
  Grid grid;

  uint8_t addType = SAND;

  void setupSFML() {
    // Setup main window
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Template text", sf::Style::Close);
    window.setFramerateLimit(75);

    // Font for some test text
    genericFont.loadFromFile("../../src/fonts/Minecraft rus.ttf");
  }

  void setupProgram() {
    srand((unsigned)time(NULL));
  }

  void update() {
    grid.update();
  }

  void draw() {
    window.draw(grid);
  }

  void spawnElement(uint8_t type, sf::Vector2i mouse) {
    grid.addElement(type, mouse);
  }

  public:
    App() {}

    ~App() {}

    void setup() {
      setupSFML();
      setupProgram();
    }

    void run() {
      while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed)
            window.close();

          if (event.type == sf::Event::KeyReleased)
            switch (event.key.code) {
              case sf::Keyboard::Q:
                window.close();
                break;
              case sf::Keyboard::Num1:
                addType = SAND;
                break;
              case sf::Keyboard::Num2:
                addType = WATER;
                break;
              default:
                break;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
          spawnElement(addType, sf::Mouse::getPosition(window));

        update();

        window.clear();

        draw();

        window.display();
      }
    }
};

