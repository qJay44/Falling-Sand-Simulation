class Element {
  uint8_t type;
  sf::Color color;

  public:
    Element(uint8_t type) : type(type) {
      switch (type) {
        case SAND:
          color = {255, 255, 0};
          break;
        case WATER:
          color = {0, 0, 255};
          break;
      }
    }

    const sf::Color& getColor() const {
      return color;
    }

    const uint8_t& getType() const {
      return type;
    }
};

