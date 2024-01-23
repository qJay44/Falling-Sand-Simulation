#include "engine/Grid.hpp"

class App {
  sf::RenderWindow window;
  sf::Font genericFont;
  Grid grid;

  void setupSFML() {
    // Setup main window
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Falling sand simulation", sf::Style::Close);
    window.setFramerateLimit(75);

    // Font for some test text
    genericFont.loadFromFile("../../src/fonts/Minecraft rus.ttf");
  }

  void setupProgram() {
    srand((unsigned)time(NULL));
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
              default:
                break;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
          grid.add(sf::Mouse::getPosition(window));

        grid.update();

        window.clear();
        window.draw(grid);
        window.display();
      }
    }
};

