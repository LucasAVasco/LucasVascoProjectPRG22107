#ifndef SPACE_SHIP_HPP
#define SPACE_SHIP_HPP

#include "space_ship.hpp"
#include <list>
#include <qgraphicsscene.h>

class Wave {
    static constexpr int SPACING_X = SpaceShip::WIDTH + 10;
    static constexpr int SPACING_Y = SpaceShip::HEIGHT + 10;
    static constexpr int VEL_MODULE = 5;
    static constexpr int DIST_Y = SpaceShip::HEIGHT;

  public:
    Wave(QGraphicsScene *scene, int scene_width, int scene_height,
         int wave_width, uint32_t ships_count)
        : _scene_width(scene_width), _scene_height(scene_height) {
        Movable::LimitedArea area = {
            .begin = {0, 0},
            .end = {_scene_width, _scene_height},
        };

        int offset_x = 0, offset_y = 0;

        for (uint32_t i = ships_count; i > 0; i--) {
            _space_ships.emplace_back(scene, offset_x, offset_y);
            auto &created_space_ship = _space_ships.back();
            created_space_ship.setLimitedArea(area);
            created_space_ship.setYVelocity(VEL_MODULE);

            // Next offsets
            offset_x += SPACING_X;
            if (offset_x > wave_width) {
                offset_x = 0;
                offset_y += SPACING_Y;
            }
        }
    }

    void updatePosition() {
        // Next line
        if (_y < _desired_y) {
            for (auto &&space_ship : _space_ships) {
                space_ship.updateYPosition();
            }
            _y += VEL_MODULE;
            return;
        }

        for (auto &&space_ship : _space_ships) {
            space_ship.updateXPosition();
        }

        // Checks if the wave is colliding left or right and changes the
        // horizontal direction
        int next_dx = 0;

        for (auto &&space_ship : _space_ships) {
            if (space_ship.isCollidingAtLimitAreaRight()) {
                next_dx = -VEL_MODULE;
            }

            if (space_ship.isCollidingAtLimitAreaLeft()) {
                next_dx = VEL_MODULE;
            }
        }

        if (next_dx != 0) { // Is colliding, so changes the horizontal direction
                            // and goes to the next line (vertical position)
            for (auto &&space_ship : _space_ships) {
                space_ship.setXVelocity(next_dx);
            }

            _desired_y += DIST_Y;
        }
    }

    void updateSpritesPosition() const {
        for (auto &&space_ship : _space_ships) {
            space_ship.updateSpritePosition();
        }
    }

    void shot(std::list<std::unique_ptr<Bullet>> &bullets) const {
        for (auto &&space_ship : _space_ships) {
            if (rand() % 2) {
                bullets.push_back(space_ship.shot());
            }
        }
    }

    uint32_t killShotSpaceShips(std::list<std::unique_ptr<Bullet>> &bullets) {
        uint32_t num_killed_enemies = 0;

        _space_ships.remove_if(
            [&bullets, &num_killed_enemies](auto &&space_ship) {
                for (auto &&bullet : bullets) {
                    if (space_ship.isShot(*bullet)) {
                        num_killed_enemies++;
                        bullets.remove(bullet);
                        return true;
                    }
                }

                return false;
            });

        return num_killed_enemies;
    }

    size_t getNumSpaceShips() const { return _space_ships.size(); }

    int getBottom() {
        int bottom = 0;

        for (auto &&space_ship : _space_ships) {
            auto pos = space_ship.getYPosition();

            if (pos > bottom) {
                bottom = pos;
            }
        }

        return bottom + SpaceShip::HEIGHT;
    }

  private:
    void _updateEnemiesPositions() {
        for (auto &&space_ship : _space_ships) {
            space_ship.updatePosition();
        }
    }

    const int _scene_width;
    const int _scene_height;
    int _y = 0;
    int _desired_y = 0;
    std::list<SpaceShip> _space_ships;
};

#endif // end of SPACE_SHIP_HPP
