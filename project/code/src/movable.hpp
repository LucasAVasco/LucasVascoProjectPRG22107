#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#include "region.hpp"
#include <algorithm>
#include <optional>

typedef struct {
    int x;
    int y;
} Point;

class Movable : public Region {
  public:
    typedef struct {
        Point begin;
        Point end;
    } LimitedArea;

    Movable(QGraphicsScene *scene, SpritePixmap &sprite_pixmap,
            Region::Area &&area)
        : Region(scene, sprite_pixmap, std::move(area)) {}

    void setLimitedArea(LimitedArea &area) { _limited_area = area; }

    bool isCollidingAtLimitAreaRight() const {
        if (!_limited_area.has_value()) {
            return false;
        }

        return _x + _width == _limited_area.value().end.x;
    }

    bool isCollidingAtLimitAreaLeft() const {
        if (!_limited_area.has_value()) {
            return false;
        }

        return _x == _limited_area.value().begin.x;
    }

    bool isCollidingAtLimitAreaTop() const {
        if (!_limited_area.has_value()) {
            return false;
        }

        return _y == _limited_area.value().begin.y;
    }

    bool isCollidingAtLimitAreaBottom() const {
        if (!_limited_area.has_value()) {
            return false;
        }

        return _y == _limited_area.value().end.y;
    }

    void setXPosition(int x) {
        _x = x;

        if (_limited_area.has_value()) {
            const auto &value = _limited_area.value();
            _x = std::clamp(_x, value.begin.x, value.end.x - _width);
        }
    }

    void setYPosition(int y) {
        _y = y;

        if (_limited_area.has_value()) {
            const auto &value = _limited_area.value();
            _y = std::clamp(_y, value.begin.y, value.end.y - _height);
        }
    }

    void setPosition(int x, int y) {
        setXPosition(x);
        setYPosition(y);
    }

    void setXVelocity(int dx) { _dx = dx; }
    void setYVelocity(int dy) { _dy = dy; }

    void setVelocity(int dx, int dy) {
        this->setXVelocity(dx);
        this->setYVelocity(dy);
    }

    int getXVelocity() const { return _dx; }
    int getYVelocity() const { return _dy; }

    void updateXPosition() { setXPosition(_x + _dx); }
    void updateYPosition() { setYPosition(_y + _dy); }
    void updatePosition() { setPosition(_x + _dx, _y + _dy); }

  private:
    std::optional<LimitedArea> _limited_area;
    int _dx = 0;
    int _dy = 0;
};

#endif // end of MOVABLE_HPP
