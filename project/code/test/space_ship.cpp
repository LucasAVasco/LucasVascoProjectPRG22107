#include "../src/space_ship.hpp"
#include "./lib/app.hpp"
#include "./lib/bullet.hpp"
#include "./lib/scene.hpp"

#include <gtest/gtest.h>

std::unique_ptr<SpaceShip> getEnemy(QGraphicsScene *scene, int x, int y) {
    return std::make_unique<SpaceShip>(scene, x, y);
}

TEST(SpaceShip, isShot) {
    auto app = test::getApplication();
    auto scene = test::getScene();

    auto ship = getEnemy(scene.get(), 1, 2);
    auto bullet = test::getBullet(scene.get(), Bullet::Target::ENEMY, 1, 2);
    EXPECT_TRUE(ship->isShot(*bullet));

    auto bullet_out =
        test::getBullet(scene.get(), Bullet::Target::ENEMY, 1000, 2000);
    EXPECT_FALSE(ship->isShot(*bullet_out));

    auto ship_bullet =
        test::getBullet(scene.get(), Bullet::Target::PLAYER, 1, 2);
    EXPECT_FALSE(ship->isShot(*bullet_out));
}

TEST(SpaceShip, shot) {
    auto app = test::getApplication();
    auto scene = test::getScene();

    // Bullet target
    auto ship = getEnemy(scene.get(), 1, 2);
    auto bullet = ship->shot();
    EXPECT_NE(nullptr, bullet.get());
    EXPECT_EQ(Bullet::Target::PLAYER, bullet->getTarget());
}
