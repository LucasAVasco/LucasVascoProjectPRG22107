#ifndef BUNKER_HPP
#define BUNKER_HPP

#include "./project.hpp"
#include "alive.hpp"
#include "bullet.hpp"
#include "region.hpp"
#include "sprite.hpp"
#include <qgraphicsscene.h>

class Bunker : public Region, public Alive {
  public:
    static constexpr int WIDTH = 100;
    static constexpr int HEIGHT = 50;

    Bunker(QGraphicsScene *scene, int x, int y)
        : Region(
              scene, _sprite_pixmap,
              Region::Area{.x = x, .y = y, .width = WIDTH, .height = HEIGHT}),
          Alive(10) {};

    bool isShot(const Bullet &bullet) const {
        if (!isAlive())
            return false;

        return bullet.isColliding(*this);
    }

  private:
    static SpritePixmap _sprite_pixmap;
};

inline SpritePixmap Bunker::_sprite_pixmap =
    SpritePixmap(PROJ_ROOT_DIR "./assets/bunker.png", WIDTH, HEIGHT);

#endif // end of BUNKER_HPP
