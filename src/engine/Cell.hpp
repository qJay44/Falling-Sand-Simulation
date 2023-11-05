#include "Element.hpp"
#include "myutils.hpp"

class Cell : public sf::RectangleShape {
  Element* content = nullptr;

  public:
    ~Cell() {
      delete content;
    }

    [[nodiscard]]
    bool hasContent() const {
      return content;
    }

    [[nodiscard]]
    const Element* getElement() const {
      return content;
    }

    void update(Element* c) {
      content = c;
      setFillColor(c->getColor());
    }

    void update(Cell& rhs) {
      content = rhs.content;
      setFillColor(content->getColor());

      rhs.content = nullptr;
      rhs.setFillColor(sf::Color::Black);
    }

    void swap(Cell& rhs) {
      Element* el1 = content;
      Element* el2 = rhs.content;

      update(el2);
      rhs.update(el1);
    }
};

