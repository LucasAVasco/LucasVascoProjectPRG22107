#ifndef BULLET_HPP
#define BULLET_HPP

#include "./movable.hpp"
#include "project.hpp"
#include "sprite.hpp"

class Bullet : public Movable {
  public:
    enum class Target {
        PLAYER,
        ENEMY,
    };

    static constexpr int WIDTH = 10;
    static constexpr int HEIGHT = 30;

    Bullet(QGraphicsScene *scene, Target target, int x, int y)
        : Movable(
              scene, _sprite_pixmap,
              Region::Area{.x = x, .y = y, .width = WIDTH, .height = HEIGHT}),
          _target(target) {
        updateSpritePosition();
    };

    Target getTarget() const { return _target; }

  private:
    const Target _target;
    static SpritePixmap _sprite_pixmap;
};

inline SpritePixmap Bullet::_sprite_pixmap =
    SpritePixmap(PROJ_ROOT_DIR "./assets/bullet.png", WIDTH, HEIGHT);

#endif // end of BULLET_HPP
