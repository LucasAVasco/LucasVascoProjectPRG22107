#ifndef LASER_CANON_HPP
#define LASER_CANON_HPP

#include "alive.hpp"
#include "bullet.hpp"
#include "project.hpp"
#include "sprite.hpp"
#include <chrono>
#include <qgraphicsscene.h>

class LaserCanon : public Movable, public Alive {
  public:
    static constexpr int WIDTH = 50;
    static constexpr int HEIGHT = 50;

    LaserCanon(QGraphicsScene *scene, int x, int y)
        : Movable(
              scene, _sprite_pixmap,
              Region::Area{.x = x, .y = y, .width = WIDTH, .height = HEIGHT}),
          Alive(3), _scene(scene) {};

    bool isShot(const Bullet &bullet) const {
        if (!isAlive())
            return false;

        return bullet.getTarget() == Bullet::Target::PLAYER &&
               bullet.isColliding(*this);
    }

    std::unique_ptr<Bullet> shot() {
        auto now = std::chrono::steady_clock::now();
        auto now_miliseconds =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                now - _last_bullet_time);
        using namespace std::chrono_literals;

        if (now_miliseconds < 250ms) {
            auto new_bullet = std::unique_ptr<Bullet>(nullptr);
            return new_bullet;
        }

        _last_bullet_time = now;
        auto new_bullet = std::make_unique<Bullet>(
            _scene, Bullet::Target::ENEMY, getXPosition() + WIDTH / 2,
            getYPosition());
        new_bullet->setYVelocity(-10);

        return new_bullet;
    }

    void addScore(uint32_t score) { _score += score; }

    uint32_t getScore() const { return _score; }

  private:
    QGraphicsScene *_scene;
    static SpritePixmap _sprite_pixmap;
    uint32_t _score = 0;
    std::chrono::time_point<std::chrono::steady_clock> _last_bullet_time =
        std::chrono::steady_clock::now();
};

inline SpritePixmap LaserCanon::_sprite_pixmap =
    SpritePixmap(PROJ_ROOT_DIR "./assets/laser-canon.png", WIDTH, HEIGHT);

#endif // LASER_CANON_HPP
