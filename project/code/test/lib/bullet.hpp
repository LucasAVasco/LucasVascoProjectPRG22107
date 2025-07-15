#ifndef TEST_LIB_BULLET_HPP
#define TEST_LIB_BULLET_HPP

#include "../../src/bullet.hpp"

#include <memory>

namespace test {

inline std::unique_ptr<Bullet> getBullet(QGraphicsScene *scene,
                                         Bullet::Target target, int x, int y) {
    return std::make_unique<Bullet>(scene, target, x, y);
}

} // namespace test

#endif // end of TEST_LIB_BULLET_HPP
