#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "./bullet.hpp"
#include "movable.hpp"
#include "sprite.hpp"
#include <qgraphicsscene.h>

class SpaceShip : public Movable {
  public:
    static constexpr int WIDTH = 50;
    static constexpr int HEIGHT = 30;

    SpaceShip(QGraphicsScene *scene, int x, int y)
        : Movable(
              scene, _sprite_pixmap,
              Region::Area{.x = x, .y = y, .width = WIDTH, .height = HEIGHT}),
          _scene(scene) {}

    bool isShot(const Bullet &bullet) {
        return bullet.getTarget() == Bullet::Target::ENEMY &&
               bullet.isColliding(*this);
    }

    std::unique_ptr<Bullet> shot() const {
        auto new_bullet = std::make_unique<Bullet>(
            _scene, Bullet::Target::PLAYER, getXPosition() + WIDTH / 2,
            getYPosition());
        new_bullet->setYVelocity(10);
        return std::move(new_bullet);
    }

  private:
    static SpritePixmap _sprite_pixmap;
    QGraphicsScene *_scene;
};

inline SpritePixmap SpaceShip::_sprite_pixmap =
    SpritePixmap(PROJ_ROOT_DIR "./assets/space-ship.png", WIDTH, HEIGHT);

#endif // end of ENEMY_HPP
