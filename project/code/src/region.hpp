#ifndef REGION_HPP
#define REGION_HPP

#include "sprite.hpp"
#include <qgraphicsscene.h>

class Region {
  public:
    struct Area {
        int x;
        int y;
        int width;
        int height;
    };

    Region(QGraphicsScene *scene, SpritePixmap &sprite_pixmap, Area &&area)
        : _x(area.x), _y(area.y), _width(area.width), _height(area.height),
          _sprite(sprite_pixmap, scene) {}

    int getXPosition() const { return _x; }
    int getYPosition() const { return _y; }

    bool isInside(const Region &region) const {
        return isInside(region._x, region._y, region._width, region._height);
    }

    bool isInside(int x, int y, int width, int height) const {
        if (_x < x || _y < y)
            return false;

        if (_x + _width > x + width || _y + _height > y + height)
            return false;

        return true;
    }

    bool isColliding(int x, int y, int width, int height) const {
        return !(_x + _width < x ||  // `this` is left of received region
                 _x > x + width ||   // `this` is right of received region
                 _y + _height < y || // `this` is above received region
                 _y > y + height);   // `this` is below received region
    }

    bool isColliding(const Region &region) const {
        return isColliding(region._x, region._y, region._width, region._height);
    }

    void updateSpritePosition() const {
        _sprite.updatePosition(getXPosition(), getYPosition());
    }

  protected:
    int _x;
    int _y;
    int _width;
    int _height;
    Sprite _sprite;
};

#endif // end of REGION_HPP
